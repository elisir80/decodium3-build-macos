#include "utils/EchoToolSupport.hpp"

#include "Detector/LegacyDspIoHelpers.hpp"

#include <QCoreApplication>
#include <QString>

#include <cstdio>

namespace
{
void print_usage ()
{
  std::printf ("Usage: testEchoCall fname1 [fname2, ...]\n");
}
}

int main (int argc, char* argv[])
{
  QCoreApplication app {argc, argv};
  if (argc < 2)
    {
      print_usage ();
      return 0;
    }

  std::printf ("  UTC     Hour   Level  Doppler  Width     N     Q     DF    SNR   dBerr   Message\n");
  std::printf ("----------------------------------------------------------------------------------\n");

  decodium::legacy::clear_echo_plot_state ();
  int nclearave = 1;
  int const navg = 10;
  int const nauto = 1;

  for (int index = 1; index < argc; ++index)
    {
      QString error;
      std::vector<short> samples =
          decodium::echo_tools::read_pcm16_mono_wav (QString::fromLocal8Bit (argv[index]), &error);
      if (samples.empty ())
        {
          std::fprintf (stderr, "Unable to read %s: %s\n", argv[index], error.toLocal8Bit ().constData ());
          return 1;
        }
      if (static_cast<int> (samples.size ()) < decodium::echo_tools::kEchoTxSamples)
        {
          std::fprintf (stderr, "File %s is too short for Echo analysis\n", argv[index]);
          return 1;
        }

      int ndop_total = 0;
      int ndop_audio = 0;
      int nfrit = 0;
      float f1 = 0.0f;
      float fspread = 0.0f;
      int ndf = 0;
      int tones[6] {};
      decodium::legacy::load_echo_params (samples.data (), &ndop_total, &ndop_audio, &nfrit, &f1,
                                          &fspread, &ndf, tones);

      auto const result = decodium::legacy::avecho_update (
          samples.data (), 0, nfrit, nauto, ndf, navg, f1, fspread, true, false, QString {},
          nclearave, fspread, fspread);

      QString const file_name = QString::fromLocal8Bit (argv[index]);
      int const dot = file_name.lastIndexOf (".wav");
      QString const hhmmss = dot >= 6 ? file_name.mid (dot - 6, 6) : QStringLiteral ("000000");
      int ih = hhmmss.mid (0, 2).toInt ();
      int im = hhmmss.mid (2, 2).toInt ();
      int is = hhmmss.mid (4, 2).toInt ();
      float const hour = ih + im / 60.0f + is / 3600.0f;
      auto const& echo_state = decodium::legacy::echo_plot_state ();
      std::printf ("%s  %7.4f  %5.2f %7d %7.1f %5d %5d %6d %6.1f %7.1f   %-6s\n",
                   hhmmss.toLocal8Bit ().constData (), hour, result.xlevel, ndop_total, fspread,
                   echo_state.nsum, result.nqual, qRound (result.dfreq), result.sigdb,
                   result.db_err, result.rxcall.trimmed ().leftJustified (6, QLatin1Char (' '))
                       .toLocal8Bit ()
                       .constData ());
      nclearave = 0;
    }

  return 0;
}
