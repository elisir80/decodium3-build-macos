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
#include <tuple>
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

bool nearly_equal (float lhs, float rhs, float abs_tol = 1.0e-4f, float rel_tol = 1.0e-5f)
{
  float const scale = std::max ({1.0f, std::fabs (lhs), std::fabs (rhs)});
  return std::fabs (lhs - rhs) <= abs_tol + rel_tol * scale;
}

bool same_candidates (std::vector<decodium::legacy::Jt65SyncCandidate> const& lhs,
                      std::vector<decodium::legacy::Jt65SyncCandidate> const& rhs)
{
  if (lhs.size () != rhs.size ())
    {
      return false;
    }
  for (std::size_t i = 0; i < lhs.size (); ++i)
    {
      if (!nearly_equal (lhs[i].freq, rhs[i].freq) || !nearly_equal (lhs[i].dt, rhs[i].dt)
          || !nearly_equal (lhs[i].sync, rhs[i].sync) || !nearly_equal (lhs[i].flip, rhs[i].flip))
        {
          return false;
        }
    }
  return true;
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

      auto const spec = decodium::legacy::symspec65_compute (dd.data (), static_cast<int> (dd.size ()));
      if (!spec.ok)
        {
          fail (QStringLiteral ("symspec65_compute returned !ok for %1").arg (wavPath));
        }
      decodium::legacy::jt65_store_symspec_state (spec);

      std::array<std::tuple<int, int, int, int, int, float>, 4> const cases {{
          std::make_tuple (200, 4000, 1000, 0, 0, 2.0f),
          std::make_tuple (200, 4000, 1000, 1, 0, 2.0f),
          std::make_tuple (1200, 1800, 200, 0, 0, 1.0f),
          std::make_tuple (1200, 1800, 200, 0, 1, 1.0f),
      }};

      bool ok = true;
      for (auto const& entry : cases)
        {
          int const nfa = std::get<0> (entry);
          int const nfb = std::get<1> (entry);
          int const ntol = std::get<2> (entry);
          bool const robust = std::get<3> (entry) != 0;
          bool const vhf = std::get<4> (entry) != 0;
          float const thresh0 = std::get<5> (entry);

          decodium::legacy::jt65_set_sync_threshold (thresh0);
          auto const first =
              decodium::legacy::sync65_compute (nfa, nfb, ntol, spec.nqsym, robust, vhf, thresh0);
          auto const second =
              decodium::legacy::sync65_compute (nfa, nfb, ntol, spec.nqsym, robust, vhf, thresh0);

          if (!same_candidates (first, second))
            {
              std::fprintf (stderr,
                            "JT65 sync state compare failed for case nfa=%d nfb=%d ntol=%d robust=%d vhf=%d thresh=%.2f\n",
                            nfa, nfb, ntol, robust ? 1 : 0, vhf ? 1 : 0, thresh0);
              ok = false;
              break;
            }
        }

      if (!ok)
        {
          return 1;
        }

      std::printf ("JT65 sync state compare passed for %s with nqsym=%d\n",
                   wavPath.toLocal8Bit ().constData (), spec.nqsym);
      return 0;
    }
  catch (std::exception const& e)
    {
      std::fprintf (stderr, "jt65_sync_compare failed: %s\n", e.what ());
      return 1;
    }
}
