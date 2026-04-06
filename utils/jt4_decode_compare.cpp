// Compare Fortran legacy_jt_async_decode path vs C++ JT4Decoder for JT4 RX
// Usage: jt4_decode_compare <wavfile> [nsubmode=0] [nfqso=1000] [ndepth=3]
#include <QByteArray>
#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtEndian>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <vector>

#include "Detector/JT4Decoder.hpp"
#include "Detector/LegacyJtDecodeWorker.hpp"
#include "commons.h"
#include "wsjtx_config.h"

extern "C"
{
  void legacy_jt_async_decode_ (int* nmode, float ss[], short id2[], int* npts8, int* nzhsym,
                                 int* nutc, int* nfqso, int* ntol, int* ndepth,
                                 int* nfa, int* nfb, int* nfsplit, int* nsubmode,
                                 int* nclearave, int* minsync, int* minw,
                                 float* emedelay, float* dttol, int* newdat, int* nagain,
                                 int* n2pass, int* nrobust, int* ntrials, int* naggressive,
                                 int* nexp_decode, int* nqsoprogress, int* ljt65apon,
                                 char mycall[], char hiscall[], char hisgrid[], char temp_dir[],
                                 char outlines[], int* nout,
                                 fortran_charlen_t, fortran_charlen_t, fortran_charlen_t,
                                 fortran_charlen_t, fortran_charlen_t);
}

namespace
{

constexpr int kSampleRate = 12000;
constexpr int kAudioMax = NTMAX * kSampleRate;  // 60 * 12000 = 720000
constexpr int kMaxLines = 200;
constexpr int kLineChars = 80;

[[noreturn]] void fail (char const* msg)
{
  throw std::runtime_error {msg};
}

QVector<short> read_wav_mono16 (QString const& fileName)
{
  QFile file {fileName};
  if (!file.open (QIODevice::ReadOnly))
    fail ("cannot open WAV file");

  QByteArray const blob = file.readAll ();
  if (blob.size () < 44)
    fail ("WAV file too short");
  if (blob.mid (0, 4) != "RIFF" || blob.mid (8, 4) != "WAVE")
    fail ("not a RIFF/WAVE file");

  int pos = 12;
  QByteArray dataChunk;
  bool haveFmt = false, haveData = false;
  quint32 sampleRate = 0;
  quint16 channels = 0, bitsPerSample = 0, audioFormat = 0;

  while (pos + 8 <= blob.size ())
    {
      QByteArray const id = blob.mid (pos, 4);
      quint32 const sz =
          qFromLittleEndian<quint32> (reinterpret_cast<uchar const*> (blob.constData () + pos + 4));
      pos += 8;
      if (id == "fmt ")
        {
          auto const* p = reinterpret_cast<uchar const*> (blob.constData () + pos);
          audioFormat = qFromLittleEndian<quint16> (p);
          channels = qFromLittleEndian<quint16> (p + 2);
          sampleRate = qFromLittleEndian<quint32> (p + 4);
          bitsPerSample = qFromLittleEndian<quint16> (p + 14);
          haveFmt = true;
        }
      else if (id == "data")
        {
          dataChunk = blob.mid (pos, static_cast<int> (sz));
          haveData = true;
        }
      pos += static_cast<int> (sz) + (sz & 1);
    }

  if (!haveFmt || !haveData)
    fail ("missing fmt or data chunk");
  if (audioFormat != 1 || channels != 1 || bitsPerSample != 16 || sampleRate != 12000)
    fail ("WAV must be PCM mono 16-bit 12000 Hz");

  int const count = dataChunk.size () / 2;
  QVector<short> samples (count);
  auto const* raw = reinterpret_cast<uchar const*> (dataChunk.constData ());
  for (int i = 0; i < count; ++i)
    samples[i] = static_cast<short> (qFromLittleEndian<qint16> (raw + 2 * i));
  return samples;
}

// Build a DecodeRequest for JT4 with standard parameters
decodium::legacyjt::DecodeRequest make_jt4_request (QVector<short> const& audio,
                                                     int nsubmode, int nfqso, int ndepth)
{
  decodium::legacyjt::DecodeRequest req;
  req.mode = QStringLiteral ("JT4");
  req.audio = audio;
  req.nsubmode = nsubmode;
  req.nfqso = nfqso;
  req.ntol = 20;
  req.nfa = 200;
  req.nfb = 4000;
  req.ndepth = ndepth;
  req.minsync = 0;
  req.minw = 0;
  req.nutc = 0;
  req.newdat = 1;
  req.nclearave = 1;
  req.n2pass = 1;
  req.ntrials = 0;
  req.naggressive = 0;
  req.nexp_decode = 0;
  req.nqsoprogress = 0;
  req.ljt65apon = 0;
  req.mycall = "          ";
  req.hiscall = "          ";
  req.hisgrid = "      ";
  req.tempDir = ".";
  return req;
}

// Call the Fortran legacy_jt_async_decode_ path directly
QStringList fortran_jt4_decode (QVector<short> const& audio, int nsubmode, int nfqso, int ndepth)
{
  constexpr int kSSSize = 184 * NSMAX;

  std::vector<float> ss (static_cast<std::size_t> (kSSSize), 0.0f);
  std::vector<short> id2 (static_cast<std::size_t> (kAudioMax), 0);
  int const copyCount = std::min (audio.size (), kAudioMax);
  std::copy_n (audio.constBegin (), copyCount, id2.begin ());

  char outlines[kMaxLines][kLineChars];
  std::memset (outlines, 0, sizeof outlines);

  int nmode = 4;
  int npts8 = 0;
  int nzhsym = 0;
  int nutc = 0;
  int ntol = 20;
  int nfa = 200;
  int nfb = 4000;
  int nfsplit = 1500;
  int nclearave = 1;
  int minsync = 0;
  int minw = 0;
  float emedelay = 0.0f;
  float dttol = 3.0f;
  int newdat = 1;
  int nagain = 0;
  int n2pass = 1;
  int nrobust = 0;
  int ntrials = 0;
  int naggressive = 0;
  int nexp_decode = 0;
  int nqsoprogress = 0;
  int ljt65apon = 0;
  int nout = 0;

  char mycall[12] = "          ";
  char hiscall[12] = "          ";
  char hisgrid[7] = "      ";
  char tempdir[] = ".";

  legacy_jt_async_decode_ (&nmode, ss.data (), id2.data (), &npts8, &nzhsym,
                            &nutc, &nfqso, &ntol, &ndepth, &nfa, &nfb, &nfsplit,
                            &nsubmode, &nclearave, &minsync, &minw,
                            &emedelay, &dttol, &newdat, &nagain, &n2pass, &nrobust,
                            &ntrials, &naggressive, &nexp_decode, &nqsoprogress,
                            &ljt65apon, mycall, hiscall, hisgrid, tempdir,
                            &outlines[0][0], &nout,
                            static_cast<fortran_charlen_t> (12),
                            static_cast<fortran_charlen_t> (12),
                            static_cast<fortran_charlen_t> (6),
                            static_cast<fortran_charlen_t> (sizeof (tempdir) - 1),
                            static_cast<fortran_charlen_t> (kMaxLines * kLineChars));

  QStringList rows;
  for (int i = 0; i < std::min (nout, kMaxLines); ++i)
    {
      QByteArray row {outlines[i], kLineChars};
      int end = row.size ();
      while (end > 0)
        {
          char const c = row.at (end - 1);
          if (c == '\0' || c == ' ' || c == '\t' || c == '\r' || c == '\n')
            {
              --end;
              continue;
            }
          break;
        }
      if (end > 0)
        rows << QString::fromLatin1 (row.constData (), end);
    }
  return rows;
}

// Strip the SNR token (field 1, 0-based) from a decode line, leaving everything
// else unchanged.  Whitespace-splits on the first 2 spaces.
// E.g. "0000 -18 -0.1 1000 $* FOO" → "0000 -0.1 1000 $* FOO"
QString strip_snr (QString const& line)
{
  // Format: "HHMM SNR DT FREQ FLAGS MESSAGE..."
  // Skip field 1 (SNR) only; preserve fields 0, 2+
  QStringList parts = line.split (QLatin1Char (' '), Qt::KeepEmptyParts);
  if (parts.size () < 3)
    return line;
  parts.removeAt (1);   // remove SNR
  return parts.join (QLatin1Char (' '));
}

}  // namespace

int main (int argc, char** argv)
{
  QCoreApplication app {argc, argv};

  if (argc < 2)
    {
      std::fprintf (stderr, "Usage: jt4_decode_compare <wavfile> [nsubmode=0] [nfqso=1000] [ndepth=3]\n");
      return 1;
    }

  try
    {
      QString const wavFile = QString::fromLocal8Bit (argv[1]);
      int const nsubmode = (argc >= 3) ? std::atoi (argv[2]) : 0;
      int const nfqso = (argc >= 4) ? std::atoi (argv[3]) : 1000;
      int const ndepth = (argc >= 5) ? std::atoi (argv[4]) : 3;

      std::printf ("Reading: %s  submode=%d  nfqso=%d  ndepth=%d\n",
                   qPrintable (wavFile), nsubmode, nfqso, ndepth);

      QVector<short> const audio = read_wav_mono16 (wavFile);
      std::printf ("Loaded %d samples (%.1f s)\n", audio.size (),
                   static_cast<double> (audio.size ()) / kSampleRate);

      // --- Fortran path ---
      std::printf ("\n--- Fortran path (legacy_jt_async_decode_) ---\n");
      QStringList const fort_lines = fortran_jt4_decode (audio, nsubmode, nfqso, ndepth);
      if (fort_lines.isEmpty ())
        std::printf ("  (no output)\n");
      else
        for (QString const& line : fort_lines)
          std::printf ("  F: %s\n", qPrintable (line));

      // --- C++ path ---
      std::printf ("\n--- C++ path (decode_async_jt4) ---\n");
      auto req = make_jt4_request (audio, nsubmode, nfqso, ndepth);
      decodium::jt4::AverageState state;
      QStringList const cpp_lines = decodium::jt4::decode_async_jt4 (req, &state);
      if (cpp_lines.isEmpty ())
        std::printf ("  (no output)\n");
      else
        for (QString const& line : cpp_lines)
          std::printf ("  C: %s\n", qPrintable (line));

      // --- Compare ---
      std::printf ("\n--- Comparison ---\n");
      bool match = true;

      if (fort_lines.size () != cpp_lines.size ())
        {
          std::printf ("MISMATCH: Fortran produced %d lines, C++ produced %d lines\n",
                       fort_lines.size (), cpp_lines.size ());
          match = false;
        }

      int const ncompare = std::min (fort_lines.size (), cpp_lines.size ());
      for (int i = 0; i < ncompare; ++i)
        {
          // Compare without SNR field — minor floating-point differences are expected
          if (strip_snr (fort_lines[i]) != strip_snr (cpp_lines[i]))
            {
              std::printf ("MISMATCH line %d:\n  F: '%s'\n  C: '%s'\n",
                           i, qPrintable (fort_lines[i]), qPrintable (cpp_lines[i]));
              match = false;
            }
        }

      if (match)
        {
          std::printf ("PASS: all %d line(s) match\n", fort_lines.size ());
          return 0;
        }
      else
        {
          std::printf ("FAIL\n");
          return 1;
        }
    }
  catch (std::exception const& e)
    {
      std::fprintf (stderr, "Error: %s\n", e.what ());
      return 1;
    }
}
