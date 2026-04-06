#include "utils/EchoToolSupport.hpp"

#include <QCoreApplication>
#include <QString>

#include <cstdio>

namespace
{
void print_usage ()
{
  std::printf ("Usage:   EchoCallSim callsign f0 fdop fspread ndf nfiles snrdb\n");
  std::printf ("Example: EchoCallSim   K1JT  1500 0.0  10.0    10   10    -15\n");
}
}

int main (int argc, char* argv[])
{
  QCoreApplication app {argc, argv};
  if (argc != 8)
    {
      print_usage ();
      return 0;
    }

  QString const callsign = QString::fromLocal8Bit (argv[1]).left (6);
  double const f0 = QString::fromLocal8Bit (argv[2]).toDouble ();
  double const fdop = QString::fromLocal8Bit (argv[3]).toDouble ();
  float const fspread = QString::fromLocal8Bit (argv[4]).toFloat ();
  int const ndf = QString::fromLocal8Bit (argv[5]).toInt ();
  int const nfiles = QString::fromLocal8Bit (argv[6]).toInt ();
  float const snrdb = QString::fromLocal8Bit (argv[7]).toFloat ();

  std::printf ("   N   f0     fDop fSpread  ndf  SNR   File name\n");
  std::printf ("---------------------------------------------------------------\n");
  for (int ifile = 1; ifile <= nfiles; ++ifile)
    {
      std::vector<short> const samples =
          decodium::echo_tools::make_echo_call_wave (callsign, f0, fdop, fspread, ndf, snrdb);
      QString const path = decodium::echo_tools::timestamped_wave_name (ifile, 6);
      if (!decodium::echo_tools::write_pcm16_mono_wav (path, samples))
        {
          std::fprintf (stderr, "Unable to write %s\n", path.toLocal8Bit ().constData ());
          return 1;
        }
      std::printf ("%4d%7.1f%7.1f%7.1f%5d%7.1f  %s\n",
                   ifile, f0, fdop, fspread, ndf, snrdb, path.toLocal8Bit ().constData ());
    }
  return 0;
}
