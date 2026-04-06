#include "utils/EchoToolSupport.hpp"

#include "Detector/LegacyDspIoHelpers.hpp"

#include <QByteArray>
#include <QFile>
#include <QtEndian>

#include <algorithm>
#include <cmath>
#include <complex>
#include <cstring>
#include <random>

#include <fftw3.h>

namespace
{
void put_u16 (QByteArray& blob, int offset, quint16 value)
{
  qToLittleEndian<quint16> (value, reinterpret_cast<uchar*> (blob.data () + offset));
}

void put_u32 (QByteArray& blob, int offset, quint32 value)
{
  qToLittleEndian<quint32> (value, reinterpret_cast<uchar*> (blob.data () + offset));
}

QByteArray make_wav_blob (std::vector<short> const& samples)
{
  int const data_size = static_cast<int> (samples.size () * sizeof (short));
  QByteArray blob (44 + data_size, '\0');
  std::copy_n ("RIFF", 4, blob.data ());
  put_u32 (blob, 4, static_cast<quint32> (36 + data_size));
  std::copy_n ("WAVE", 4, blob.data () + 8);
  std::copy_n ("fmt ", 4, blob.data () + 12);
  put_u32 (blob, 16, 16u);
  put_u16 (blob, 20, 1u);
  put_u16 (blob, 22, 1u);
  put_u32 (blob, 24, static_cast<quint32> (decodium::echo_tools::kEchoSampleRate));
  put_u32 (blob, 28, static_cast<quint32> (decodium::echo_tools::kEchoSampleRate * sizeof (short)));
  put_u16 (blob, 32, sizeof (short));
  put_u16 (blob, 34, 16u);
  std::copy_n ("data", 4, blob.data () + 36);
  put_u32 (blob, 40, static_cast<quint32> (data_size));

  char* output = blob.data () + 44;
  for (std::size_t i = 0; i < samples.size (); ++i)
    {
      qToLittleEndian<qint16> (
          static_cast<qint16> (samples[i]),
          reinterpret_cast<uchar*> (output + static_cast<int> (i * sizeof (qint16))));
    }
  return blob;
}

float gaussian_noise ()
{
  static thread_local std::mt19937 rng {0x4553484Fu};
  static thread_local std::normal_distribution<float> dist {0.0f, 1.0f};
  return dist (rng);
}

double uniform_01 ()
{
  static thread_local std::mt19937 rng {0x4c4f5245u};
  static thread_local std::uniform_real_distribution<double> dist {0.0, 1.0};
  return dist (rng);
}
}

namespace decodium
{
namespace echo_tools
{

std::array<int, 6> generate_echo_call_tones (QString const& callsign)
{
  std::array<int, 6> tones {};
  QByteArray const latin = callsign.left (6).toLatin1 ();
  for (int i = 0; i < latin.size () && i < 6; ++i)
    {
      int const ch = static_cast<unsigned char> (latin.at (i));
      if (ch >= '0' && ch <= '9')
        {
          tones[static_cast<std::size_t> (i)] = ch - 47;
        }
      else if (ch >= 'A' && ch <= 'Z')
        {
          tones[static_cast<std::size_t> (i)] = ch - 54;
        }
      else if (ch >= 'a' && ch <= 'z')
        {
          tones[static_cast<std::size_t> (i)] = ch - 86;
        }
    }
  return tones;
}

void apply_lorentz_fading (std::vector<std::complex<float>>& cdat, float fspread)
{
  if (fspread <= 0.0f || cdat.empty ())
    {
      return;
    }

  int const nfft = static_cast<int> (cdat.size ());
  int const nh = nfft / 2;
  float const df = static_cast<float> (kEchoSampleRate) / static_cast<float> (nfft);
  float const b = 6.0f;
  std::vector<std::complex<float>> cspread (static_cast<std::size_t> (nfft), std::complex<float> {});
  cspread[0] = std::complex<float> {1.0f, 0.0f};
  if (nh < nfft)
    {
      cspread[static_cast<std::size_t> (nh)] = std::complex<float> {};
    }

  for (int i = 1; i <= nh; ++i)
    {
      float const f = i * df;
      float const x = b * f / fspread;
      float a = 0.0f;
      std::complex<float> z1 {};
      std::complex<float> z2 {};
      if (x < 3.0f)
        {
          a = std::sqrt (1.111f / (1.0f + x * x) - 0.1f);
          float const phi1 = static_cast<float> (2.0 * M_PI * uniform_01 ());
          float const phi2 = static_cast<float> (2.0 * M_PI * uniform_01 ());
          z1 = {a * std::cos (phi1), a * std::sin (phi1)};
          z2 = {a * std::cos (phi2), a * std::sin (phi2)};
        }
      cspread[static_cast<std::size_t> (i)] = z1;
      if (i < nfft)
        {
          cspread[static_cast<std::size_t> (nfft - i)] = z2;
        }
    }

  fftwf_plan plan = fftwf_plan_dft_1d (
      nfft, reinterpret_cast<fftwf_complex*> (cspread.data ()),
      reinterpret_cast<fftwf_complex*> (cspread.data ()), FFTW_BACKWARD, FFTW_ESTIMATE);
  if (!plan)
    {
      return;
    }
  fftwf_execute (plan);
  fftwf_destroy_plan (plan);

  double sum = 0.0;
  for (int i = 0; i < nfft; ++i)
    {
      sum += std::norm (cspread[static_cast<std::size_t> (i)]);
    }
  if (sum <= 0.0)
    {
      return;
    }

  float const fac = std::sqrt (static_cast<float> (nfft / sum));
  for (int i = 0; i < nfft; ++i)
    {
      cspread[static_cast<std::size_t> (i)] *= fac;
      cdat[static_cast<std::size_t> (i)] *= cspread[static_cast<std::size_t> (i)];
    }
}

std::vector<short> make_echo_call_wave (QString const& callsign, double f0, double fdop,
                                        float fspread, int ndf, float snrdb)
{
  std::vector<short> samples (static_cast<std::size_t> (kEchoFileSamples), 0);
  std::array<int, 6> const tones = generate_echo_call_tones (callsign);
  std::vector<std::complex<float>> cdat (static_cast<std::size_t> (kEchoTxSamples));

  double const dt = 1.0 / static_cast<double> (kEchoSampleRate);
  double phi = 0.0;
  float const bandwidth_ratio = 2500.0f / 6000.0f;
  float const sig = snrdb > 90.0f ? 1.0f
                                  : std::sqrt (2.0f * bandwidth_ratio)
                                        * std::pow (10.0f, 0.05f * snrdb);

  int k = 0;
  for (int symbol = 0; symbol < 6; ++symbol)
    {
      double const freq = f0 + fdop + tones[static_cast<std::size_t> (symbol)] * ndf;
      double const dphi = 2.0 * M_PI * freq * dt;
      for (int i = 0; i < kEchoNsps; ++i)
        {
          phi += dphi;
          if (phi > 2.0 * M_PI)
            {
              phi -= 2.0 * M_PI;
            }
          cdat[static_cast<std::size_t> (k++)] =
              sig * std::complex<float> {static_cast<float> (std::cos (phi)),
                                         static_cast<float> (std::sin (phi))};
        }
    }

  apply_lorentz_fading (cdat, fspread);

  float const scale = snrdb > 90.0f ? 32767.0f : 100.0f;
  for (int i = 0; i < kEchoTxSamples; ++i)
    {
      float value = cdat[static_cast<std::size_t> (i)].imag ();
      if (snrdb < 90.0f)
        {
          value += gaussian_noise ();
        }
      samples[static_cast<std::size_t> (i)] = static_cast<short> (std::lround (scale * value));
    }

  std::array<int, 6> tone_copy = tones;
  decodium::legacy::save_echo_params_inplace (
      qRound (fdop), 0, 0, static_cast<float> (f0 + fdop), fspread, ndf, tone_copy.data (),
      samples.data ());
  return samples;
}

std::vector<short> make_echo_measure_wave (double f0, double fdop, float fspread,
                                           float snrdb, float gain_linear)
{
  constexpr int kWaveSamples = 27648;
  std::vector<short> samples (static_cast<std::size_t> (kEchoFileSamples), 0);
  std::vector<std::complex<float>> cdat (static_cast<std::size_t> (kWaveSamples));
  std::vector<float> wave (static_cast<std::size_t> (kEchoFileSamples), 0.0f);

  if (snrdb < 90.0f)
    {
      for (float& sample : wave)
        {
          sample = gaussian_noise ();
        }
    }

  double const dt = 1.0 / static_cast<double> (kEchoSampleRate);
  double phi = 0.0;
  float const bandwidth_ratio = 2500.0f / (kEchoSampleRate / 2.0f);
  float const sig = snrdb > 90.0f
                        ? 1.0f
                        : std::sqrt (2.0f * bandwidth_ratio) * std::pow (10.0f, 0.05f * snrdb);
  double const dphi = 2.0 * M_PI * (f0 + fdop) * dt;
  for (int i = 0; i < kWaveSamples; ++i)
    {
      phi += dphi;
      if (phi > 2.0 * M_PI)
        {
          phi -= 2.0 * M_PI;
        }
      cdat[static_cast<std::size_t> (i)] =
          sig * std::complex<float> {static_cast<float> (std::cos (phi)),
                                     static_cast<float> (std::sin (phi))};
    }
  apply_lorentz_fading (cdat, fspread);
  for (int i = 0; i < kWaveSamples; ++i)
    {
      wave[static_cast<std::size_t> (i)] += cdat[static_cast<std::size_t> (i)].imag ();
    }

  if (snrdb < 90.0f)
    {
      for (float& sample : wave)
        {
          sample *= gain_linear;
        }
    }
  else
    {
      float peak = 0.0f;
      for (float sample : wave)
        {
          peak = std::max (peak, std::fabs (sample));
        }
      float const fac = peak > 0.0f ? 32766.9f / peak : 0.0f;
      for (float& sample : wave)
        {
          sample *= fac;
        }
    }

  for (int i = 0; i < kEchoFileSamples; ++i)
    {
      samples[static_cast<std::size_t> (i)] = static_cast<short> (std::lround (wave[static_cast<std::size_t> (i)]));
    }

  int const zero_tones[6] {0, 0, 0, 0, 0, 0};
  decodium::legacy::save_echo_params_inplace (
      qRound (fdop), 0, 0, static_cast<float> (f0 + fdop), fspread, 0, zero_tones, samples.data ());
  return samples;
}

QString timestamped_wave_name (int ifile, int seconds_per_file)
{
  int const elapsed = (ifile - 1) * seconds_per_file;
  int const hours = elapsed / 3600;
  int const minutes = (elapsed - 3600 * hours) / 60;
  int const seconds = elapsed % 60;
  return QStringLiteral ("000000_%1%2%3.wav")
      .arg (hours, 2, 10, QLatin1Char ('0'))
      .arg (minutes, 2, 10, QLatin1Char ('0'))
      .arg (seconds, 2, 10, QLatin1Char ('0'));
}

bool write_pcm16_mono_wav (QString const& path, std::vector<short> const& samples)
{
  QFile file {path};
  if (!file.open (QIODevice::WriteOnly))
    {
      return false;
    }
  QByteArray const blob = make_wav_blob (samples);
  return file.write (blob) == blob.size ();
}

std::vector<short> read_pcm16_mono_wav (QString const& path, QString* error_out)
{
  QFile file {path};
  if (!file.open (QIODevice::ReadOnly))
    {
      if (error_out)
        {
          *error_out = file.errorString ();
        }
      return {};
    }

  QByteArray const blob = file.readAll ();
  if (blob.size () < 12 || blob.mid (0, 4) != "RIFF" || blob.mid (8, 4) != "WAVE")
    {
      if (error_out)
        {
          *error_out = QStringLiteral ("not a RIFF/WAVE file");
        }
      return {};
    }

  bool have_fmt = false;
  bool have_data = false;
  quint16 audio_format = 0;
  quint16 channels = 0;
  quint32 sample_rate = 0;
  quint16 bits_per_sample = 0;
  QByteArray data_chunk;

  int pos = 12;
  while (pos + 8 <= blob.size ())
    {
      QByteArray const chunk_id = blob.mid (pos, 4);
      quint32 const chunk_size = qFromLittleEndian<quint32> (
          reinterpret_cast<uchar const*> (blob.constData () + pos + 4));
      pos += 8;
      if (pos + static_cast<int> (chunk_size) > blob.size ())
        {
          if (error_out)
            {
              *error_out = QStringLiteral ("truncated WAV chunk");
            }
          return {};
        }

      if (chunk_id == "fmt ")
        {
          auto const* fmt = reinterpret_cast<uchar const*> (blob.constData () + pos);
          audio_format = qFromLittleEndian<quint16> (fmt);
          channels = qFromLittleEndian<quint16> (fmt + 2);
          sample_rate = qFromLittleEndian<quint32> (fmt + 4);
          bits_per_sample = qFromLittleEndian<quint16> (fmt + 14);
          have_fmt = true;
        }
      else if (chunk_id == "data")
        {
          data_chunk = blob.mid (pos, static_cast<int> (chunk_size));
          have_data = true;
        }
      pos += static_cast<int> ((chunk_size + 1u) & ~1u);
    }

  if (!have_fmt || !have_data || audio_format != 1u || channels != 1u
      || sample_rate != static_cast<quint32> (kEchoSampleRate) || bits_per_sample != 16u)
    {
      if (error_out)
        {
          *error_out = QStringLiteral ("WAV must be mono PCM 16-bit 12000 Hz");
        }
      return {};
    }

  std::vector<short> samples (static_cast<std::size_t> (data_chunk.size () / 2));
  auto const* raw = reinterpret_cast<uchar const*> (data_chunk.constData ());
  for (int i = 0; i < static_cast<int> (samples.size ()); ++i)
    {
      samples[static_cast<std::size_t> (i)] =
          static_cast<short> (qFromLittleEndian<qint16> (raw + 2 * i));
    }
  return samples;
}

}
}
