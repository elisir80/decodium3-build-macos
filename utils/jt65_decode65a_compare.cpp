#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QVector>
#include <QtEndian>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <stdexcept>
#include <vector>

#include "Detector/LegacyDspIoHelpers.hpp"

namespace
{

constexpr int kExpectedSamples = 52 * 12000;

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

QByteArray fixed_field (QByteArray value, int width)
{
  value = value.left (width);
  if (value.size () < width)
    {
      value.append (QByteArray (width - value.size (), ' '));
    }
  return value;
}

bool nearly_equal (float lhs, float rhs, float abs_tol = 1.0e-5f, float rel_tol = 1.0e-5f)
{
  float const scale = std::max ({1.0f, std::fabs (lhs), std::fabs (rhs)});
  return std::fabs (lhs - rhs) <= abs_tol + rel_tol * scale;
}

bool same_result (decodium::legacy::Jt65Decode65aResult const& lhs,
                  decodium::legacy::Jt65Decode65aResult const& rhs)
{
  bool ok = nearly_equal (lhs.sync2, rhs.sync2) && nearly_equal (lhs.dt, rhs.dt)
            && lhs.nft == rhs.nft && lhs.nspecial == rhs.nspecial
            && nearly_equal (lhs.qual, rhs.qual) && lhs.nhist == rhs.nhist
            && lhs.nsmo == rhs.nsmo && fixed_field (lhs.decoded, 22) == fixed_field (rhs.decoded, 22);
  for (int i = 0; ok && i < 5; ++i)
    {
      ok = nearly_equal (lhs.a[static_cast<std::size_t> (i)], rhs.a[static_cast<std::size_t> (i)]);
    }
  return ok;
}

}  // namespace

int main (int argc, char** argv)
{
  try
    {
      QCoreApplication app {argc, argv};
      QString const wavPath = env_string ("JT65_WAV", QStringLiteral ("build/JT65.wav"));
      QVector<short> audio = read_wav_mono16 (wavPath);
      if (audio.size () > kExpectedSamples)
        {
          audio.resize (kExpectedSamples);
        }

      std::vector<float> dd (static_cast<std::size_t> (audio.size ()), 0.0f);
      for (int i = 0; i < audio.size (); ++i)
        {
          dd[static_cast<std::size_t> (i)] = static_cast<float> (audio.at (i));
        }

      decodium::legacy::jt65_initialize_tables ();
      auto const spec = decodium::legacy::symspec65_compute (dd.data (), static_cast<int> (dd.size ()));
      if (!spec.ok)
        {
          fail (QStringLiteral ("symspec65_compute returned !ok for %1").arg (wavPath));
        }
      decodium::legacy::jt65_store_symspec_state (spec);
      decodium::legacy::jt65_set_sync_threshold (2.0f);

      auto const candidates = decodium::legacy::sync65_compute (200, 4000, 1000, spec.nqsym, false,
                                                                false, 2.0f);
      if (candidates.empty ())
        {
          fail (QStringLiteral ("no JT65 candidate found in %1").arg (wavPath));
        }
      auto const best = *std::max_element (
          candidates.begin (), candidates.end (),
          [] (decodium::legacy::Jt65SyncCandidate const& lhs,
              decodium::legacy::Jt65SyncCandidate const& rhs) { return lhs.sync < rhs.sync; });

      QByteArray mycall (12, ' ');
      QByteArray hiscall (12, ' ');
      QByteArray hisgrid (6, ' ');
      auto const first = decodium::legacy::decode65a_compute (
          dd.data (), static_cast<int> (dd.size ()), 1, 0, best.freq, 1, 1, 1000, 0, 0, 1000,
          mycall, hiscall, hisgrid, 0, false, false, best.dt);
      auto const second = decodium::legacy::decode65a_compute (
          dd.data (), static_cast<int> (dd.size ()), 1, 0, best.freq, 1, 1, 1000, 0, 0, 1000,
          mycall, hiscall, hisgrid, 0, false, false, best.dt);

      if (!same_result (first, second))
        {
          std::fprintf (stderr, "JT65 decode65a state compare failed for %s\n",
                        wavPath.toLocal8Bit ().constData ());
          return 1;
        }

      if (decodium::legacy::jt65_decode_smoothing () != second.nsmo)
        {
          std::fprintf (stderr, "JT65 decode65a smoothing mismatch for %s: state=%d result=%d\n",
                        wavPath.toLocal8Bit ().constData (), decodium::legacy::jt65_decode_smoothing (),
                        second.nsmo);
          return 1;
        }

      std::printf ("JT65 decode65a state compare passed for %s at %.2f Hz dt %.3f\n",
                   wavPath.toLocal8Bit ().constData (), best.freq, best.dt);
      return 0;
    }
  catch (std::exception const& e)
    {
      std::fprintf (stderr, "jt65_decode65a_compare failed: %s\n", e.what ());
      return 1;
    }
}
