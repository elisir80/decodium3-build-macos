#include "utils/EchoToolSupport.hpp"

#include <QCoreApplication>
#include <QString>

#include <cmath>
#include <cstdio>

namespace
{
void print_usage ()
{
  std::printf ("Usage 1:  echosim   f0   fdop fspread nfiles snr\n");
  std::printf ("Example:  echosim  1500   0.0   4.0     10   -22\n");
  std::printf ("Usage 2:  echosim level_1 level_2 nfiles\n");
  std::printf ("Example:  echosim   30.0    40.0   100\n");
}
}

int main (int argc, char* argv[])
{
  QCoreApplication app {argc, argv};
  if (argc != 4 && argc != 6)
    {
      print_usage ();
      return 0;
    }

  double f0 = QString::fromLocal8Bit (argv[1]).toDouble ();
  double fdop = QString::fromLocal8Bit (argv[2]).toDouble ();
  float fspread = QString::fromLocal8Bit (argv[3]).toFloat ();
  int nfiles = 0;
  float snrdb = 0.0f;
  float level_1 = 0.0f;
  float level_2 = 0.0f;
  bool const signal_mode = argc == 6;
  if (signal_mode)
    {
      nfiles = QString::fromLocal8Bit (argv[4]).toInt ();
      snrdb = QString::fromLocal8Bit (argv[5]).toFloat ();
    }
  else
    {
      level_1 = static_cast<float> (f0);
      level_2 = static_cast<float> (fdop);
      nfiles = static_cast<int> (fspread);
      snrdb = 0.0f;
    }

  std::printf ("   N   f0     fDop fSpread   SNR  File name\n");
  std::printf ("---------------------------------------------------\n");
  for (int ifile = 1; ifile <= nfiles; ++ifile)
    {
      float gain_linear = 100.0f;
      if (!signal_mode)
        {
          gain_linear = std::pow (10.0f, 0.05f * (((ifile - 1) / 10) % 2 == 1 ? level_2 : level_1));
        }
      std::vector<short> const samples =
          decodium::echo_tools::make_echo_measure_wave (f0, fdop, fspread, snrdb, gain_linear);
      QString const path = decodium::echo_tools::timestamped_wave_name (ifile, 3);
      if (!decodium::echo_tools::write_pcm16_mono_wav (path, samples))
        {
          std::fprintf (stderr, "Unable to write %s\n", path.toLocal8Bit ().constData ());
          return 1;
        }
      std::printf ("%4d%7.1f%7.1f%7.1f%7.1f  %s\n",
                   ifile, f0, fdop, fspread, snrdb, path.toLocal8Bit ().constData ());
    }
  return 0;
}
