#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QVector>
#include <QtEndian>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <stdexcept>
#include <vector>

#include "Detector/LegacyDspIoHelpers.hpp"

namespace
{

constexpr int kJt65Nsz = 3413;
constexpr int kJt65MaxQsym = 552;
constexpr int kJt65ExpectedSamples = 52 * 12000;

[[noreturn]] void fail (QString const& message)
{
  throw std::runtime_error {message.toStdString ()};
}

QString env_string (char const* name, QString const& fallback)
{
  if (char const* raw = std::getenv (name))
    {
      return QString::fromLocal8Bit (raw);
    }
  return fallback;
}

QVector<short> read_wav_mono16 (QString const& fileName)
{
  QFile file {fileName};
  if (!file.open (QIODevice::ReadOnly))
    {
      fail (QStringLiteral ("cannot open WAV file \"%1\": %2").arg (fileName, file.errorString ()));
    }

  QByteArray const blob = file.readAll ();
  if (blob.size () < 12 || blob.mid (0, 4) != "RIFF" || blob.mid (8, 4) != "WAVE")
    {
      fail (QStringLiteral ("WAV file \"%1\" is not RIFF/WAVE").arg (fileName));
    }

  bool have_fmt = false;
  bool have_data = false;
  quint16 audioFormat = 0;
  quint16 channels = 0;
  quint32 sampleRate = 0;
  quint16 bitsPerSample = 0;
  QByteArray dataChunk;

  int pos = 12;
  while (pos + 8 <= blob.size ())
    {
      QByteArray const chunkId = blob.mid (pos, 4);
      quint32 const chunkSize = qFromLittleEndian<quint32> (
          reinterpret_cast<uchar const*> (blob.constData () + pos + 4));
      pos += 8;
      if (pos + static_cast<int> (chunkSize) > blob.size ())
        {
          fail (QStringLiteral ("WAV file \"%1\" has a truncated chunk").arg (fileName));
        }

      if (chunkId == "fmt ")
        {
          auto const* fmt = reinterpret_cast<uchar const*> (blob.constData () + pos);
          audioFormat = qFromLittleEndian<quint16> (fmt);
          channels = qFromLittleEndian<quint16> (fmt + 2);
          sampleRate = qFromLittleEndian<quint32> (fmt + 4);
          bitsPerSample = qFromLittleEndian<quint16> (fmt + 14);
          have_fmt = true;
        }
      else if (chunkId == "data")
        {
          dataChunk = blob.mid (pos, static_cast<int> (chunkSize));
          have_data = true;
        }

      pos += static_cast<int> ((chunkSize + 1u) & ~1u);
    }

  if (!have_fmt || !have_data || audioFormat != 1u || channels != 1u || sampleRate != 12000u
      || bitsPerSample != 16u)
    {
      fail (QStringLiteral ("WAV file \"%1\" must be PCM mono 16-bit 12000 Hz").arg (fileName));
    }

  QVector<short> samples (dataChunk.size () / 2);
  auto const* raw = reinterpret_cast<uchar const*> (dataChunk.constData ());
  for (int i = 0; i < samples.size (); ++i)
    {
      samples[i] = static_cast<short> (qFromLittleEndian<qint16> (raw + 2 * i));
    }
  return samples;
}

std::size_t ss_index (int qsym_1based, int freq_1based)
{
  return static_cast<std::size_t> (qsym_1based - 1)
         + static_cast<std::size_t> (kJt65MaxQsym) * static_cast<std::size_t> (freq_1based - 1);
}

bool nearly_equal (float lhs, float rhs, float abs_tol = 1.0e-3f, float rel_tol = 1.0e-5f)
{
  float const scale = std::max ({1.0f, std::fabs (lhs), std::fabs (rhs)});
  return std::fabs (lhs - rhs) <= abs_tol + rel_tol * scale;
}

}  // namespace

int main (int argc, char** argv)
{
  try
    {
      QCoreApplication app {argc, argv};
      QString const wavPath = env_string ("JT65_WAV", QStringLiteral ("build/JT65.wav"));
      QVector<short> audio = read_wav_mono16 (wavPath);
      if (audio.size () > kJt65ExpectedSamples)
        {
          audio.resize (kJt65ExpectedSamples);
        }

      std::vector<float> dd (static_cast<std::size_t> (audio.size ()), 0.0f);
      for (int i = 0; i < audio.size (); ++i)
        {
          dd[static_cast<std::size_t> (i)] = static_cast<float> (audio.at (i));
        }

      auto const spec = decodium::legacy::symspec65_compute (dd.data (), static_cast<int> (dd.size ()));
      if (!spec.ok)
        {
          std::fprintf (stderr, "JT65 symspec state compare failed for %s: symspec65_compute returned !ok\n",
                        wavPath.toLocal8Bit ().constData ());
          return 1;
        }

      decodium::legacy::jt65_store_symspec_state (spec);
      auto const shared = decodium::legacy::jt65_shared_state ();

      bool ok = true;
      float max_ref_diff = 0.0f;
      int max_ref_idx = -1;
      float max_ss_diff = 0.0f;
      int max_ss_qsym = -1;
      int max_ss_freq = -1;

      for (int i = 0; i < kJt65Nsz; ++i)
        {
          float const lhs = spec.ref[static_cast<std::size_t> (i)];
          float const rhs = shared.refspec_ref[static_cast<std::size_t> (i)];
          float const diff = std::fabs (lhs - rhs);
          if (diff > max_ref_diff)
            {
              max_ref_diff = diff;
              max_ref_idx = i;
            }
          if (!nearly_equal (lhs, rhs))
            {
              ok = false;
            }
        }

      for (int i = 1; i <= kJt65Nsz; ++i)
        {
          for (int j = 1; j <= spec.nqsym; ++j)
            {
              std::size_t const index = ss_index (j, i);
              float const lhs = spec.ss[index];
              float const rhs = shared.sync_ss[index];
              float const diff = std::fabs (lhs - rhs);
              if (diff > max_ss_diff)
                {
                  max_ss_diff = diff;
                  max_ss_qsym = j;
                  max_ss_freq = i;
                }
              if (!nearly_equal (lhs, rhs))
                {
                  ok = false;
                }
            }
        }

      if (!ok)
        {
          std::fprintf (stderr,
                        "JT65 symspec state compare failed for %s\n"
                        "  nqsym=%d max_ref_diff=%.9g@%d max_ss_diff=%.9g@(%d,%d) dfref=%.9g\n",
                        wavPath.toLocal8Bit ().constData (), spec.nqsym, max_ref_diff,
                        max_ref_idx, max_ss_diff, max_ss_qsym, max_ss_freq, shared.refspec_dfref);
          return 1;
        }

      std::printf ("JT65 symspec state compare passed for %s with nqsym=%d\n",
                   wavPath.toLocal8Bit ().constData (), spec.nqsym);
      return 0;
    }
  catch (std::exception const& e)
    {
      std::fprintf (stderr, "jt65_symspec_compare failed: %s\n", e.what ());
      return 1;
    }
}
