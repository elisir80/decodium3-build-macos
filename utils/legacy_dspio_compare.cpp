#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLocale>
#include <QTemporaryDir>
#include <QTextStream>

#include <array>
#include <cmath>
#include <cstdio>
#include <vector>

#include "Detector/LegacyDspIoHelpers.hpp"

namespace
{

bool test_wav12_case (short bits)
{
  constexpr int kNz12 = 60 * 12000;
  constexpr int kInputSamples = 1024;
  std::vector<short> data (static_cast<size_t> (kNz12), 0);
  int npts = kInputSamples;
  short sample_bits = bits;

  if (bits == 8)
    {
      unsigned char* bytes = reinterpret_cast<unsigned char*> (data.data ());
      for (int i = 0; i < kInputSamples; ++i)
        {
          bytes[i] = static_cast<unsigned char> ((37 * i + 53) & 0xFF);
        }
    }
  else
    {
      for (int i = 0; i < kInputSamples; ++i)
        {
          data[static_cast<size_t> (i)] =
              static_cast<short> (std::lround (14000.0 * std::sin (0.013 * i)));
        }
    }

  decodium::legacy::wav12_inplace (data.data (), &npts, sample_bits);

  int const expected_npts = static_cast<int> (kInputSamples * 12000.0 / 11025.0);
  if (std::abs (npts - expected_npts) > 2)
    {
      std::fprintf (stderr, "wav12 bits=%d: expected npts~%d got %d\n",
                    bits, expected_npts, npts);
      return false;
    }

  return true;
}

bool test_freqcal ()
{
  constexpr int kNz = 30 * 12000;
  constexpr int kNfft = 55296;
  std::vector<short> samples (static_cast<size_t> (kNz), 0);
  double const frequency = 1523.75;
  double const fs = 12000.0;
  double const pi = 4.0 * std::atan (1.0);
  for (int i = 0; i < kNfft; ++i)
    {
      samples[static_cast<size_t> (i)] =
          static_cast<short> (std::lround (12000.0 * std::sin (2.0 * pi * frequency * i / fs)));
    }

  int const k = kNfft;
  int const nkhz = 14084;
  int const noffset = 1500;
  int const ntol = 80;
  QString const line = decodium::legacy::freqcal_line (samples.data (), k, nkhz, noffset, ntol);

  if (line.isEmpty ())
    {
      std::fprintf (stderr, "freqcal: empty result\n");
      return false;
    }

  return true;
}

bool write_sample_fmt_all (QString const& dir_path)
{
  QFile file {QDir {dir_path}.filePath ("fmt.all")};
  if (!file.open (QIODevice::WriteOnly | QIODevice::Text))
    {
      return false;
    }

  QTextStream out {&file};
  out.setLocale (QLocale::c ());
  out << "12:00:00 14074  1  1500  1498.7  -1.3  35.0  28.0\n";
  out << "12:00:10 14074  1  1500  1499.1  -0.9  35.2  27.0\n";
  out << "12:01:00 21074  1  1500  1502.5   2.5  33.0  24.0\n";
  out << "12:01:10 21074  1  1500  1502.1   2.1  33.4  25.0\n";
  out << "12:02:00 28074  1  1500  1505.8   5.8  30.0  21.0\n";
  out << "12:02:10 28074  1  1500  1506.0   6.0  29.8  20.0\n";
  return true;
}

bool test_calibrate ()
{
  QTemporaryDir dir;
  if (!dir.isValid () || !write_sample_fmt_all (dir.path ()))
    {
      return false;
    }

  auto const solution = decodium::legacy::calibrate_freqcal_directory (dir.path ());

  if (solution.irc != 0 || solution.iz != 3)
    {
      std::fprintf (stderr, "calibrate: unexpected irc=%d iz=%d\n", solution.irc, solution.iz);
      return false;
    }

  if (!QFileInfo::exists (QDir {dir.path ()}.filePath ("fcal2.out")))
    {
      std::fprintf (stderr, "calibrate: output file missing\n");
      return false;
    }

  return true;
}

}

int main (int argc, char** argv)
{
  QCoreApplication app {argc, argv};

  if (!test_wav12_case (8)
      || !test_wav12_case (16)
      || !test_freqcal ()
      || !test_calibrate ())
    {
      return 1;
    }

  std::printf ("Legacy DSP/IO tests passed for wav12, freqcal and calibrate\n");
  return 0;
}
