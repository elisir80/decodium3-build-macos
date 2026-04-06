#include "utils/EchoToolSupport.hpp"

#include "Detector/LegacyDspIoHelpers.hpp"

#include <QCoreApplication>
#include <QString>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <vector>

namespace
{
constexpr int kEchoNz = 4096;

struct EchoSnapshot
{
  int nqual {0};
  float xlevel {0.0f};
  float sigdb {0.0f};
  float db_err {0.0f};
  float dfreq {0.0f};
  float width {0.0f};
  float xdt {0.0f};
  QString rxcall;
  int nsum {0};
  std::array<float, kEchoNz> blue {};
  std::array<float, kEchoNz> red {};
};

bool close_enough (float lhs, float rhs, float abs_tol = 2.0e-2f, float rel_tol = 5.0e-4f)
{
  float const scale = std::max (1.0f, std::max (std::fabs (lhs), std::fabs (rhs)));
  return std::fabs (lhs - rhs) <= abs_tol + rel_tol * scale;
}

EchoSnapshot capture_cpp (std::vector<short> const& wave, QString const& txcall, int navg,
                          bool clear_average)
{
  EchoSnapshot snapshot;
  auto const result = decodium::legacy::avecho_update (wave.data (), 0, 0, 0, 20, navg, 1500.0f,
                                                       10.0f, false, true, txcall,
                                                       clear_average ? 1 : 0, 10.0f, 10.0f);
  auto const& echo_state = decodium::legacy::echo_plot_state ();
  snapshot.nqual = result.nqual;
  snapshot.xlevel = result.xlevel;
  snapshot.sigdb = result.sigdb;
  snapshot.db_err = result.db_err;
  snapshot.dfreq = result.dfreq;
  snapshot.width = result.width;
  snapshot.xdt = result.xdt;
  snapshot.rxcall = result.rxcall;
  snapshot.nsum = echo_state.nsum;
  std::copy_n (echo_state.blue.begin (), kEchoNz, snapshot.blue.begin ());
  std::copy_n (echo_state.red.begin (), kEchoNz, snapshot.red.begin ());
  return snapshot;
}

bool compare_save_echo_params_roundtrip ()
{
  int ndop_total = 1234;
  int ndop_audio = -12;
  int nfrit = 45;
  float f1 = 1512.5f;
  float fspread = 7.5f;
  int tone_spacing = 20;
  int itone[6] {1, 12, 5, 22, 3, 0};
  short header[15] {};

  decodium::legacy::save_echo_params_inplace (ndop_total, ndop_audio, nfrit, f1, fspread,
                                              tone_spacing, itone, header);

  int ndop_total_out = 0;
  int ndop_audio_out = 0;
  int nfrit_out = 0;
  float f1_out = 0.0f;
  float fspread_out = 0.0f;
  int tone_spacing_out = 0;
  int itone_out[6] {};
  decodium::legacy::load_echo_params (header, &ndop_total_out, &ndop_audio_out, &nfrit_out,
                                      &f1_out, &fspread_out, &tone_spacing_out, itone_out);

  return ndop_total_out == ndop_total
      && ndop_audio_out == ndop_audio
      && nfrit_out == nfrit
      && close_enough (f1_out, f1, 1.0e-4f, 1.0e-6f)
      && close_enough (fspread_out, fspread, 1.0e-4f, 1.0e-6f)
      && tone_spacing_out == tone_spacing
      && std::equal (std::begin (itone), std::end (itone), std::begin (itone_out));
}

bool compare_avecho_determinism ()
{
  QString const txcall = QStringLiteral ("K1JT");
  std::vector<short> const wave =
      decodium::echo_tools::make_echo_call_wave (txcall, 1500.0, 0.0, 10.0f, 20, 99.0f);

  std::array<EchoSnapshot, 3> run_a {};
  std::array<EchoSnapshot, 3> run_b {};

  decodium::legacy::clear_echo_plot_state ();
  for (int i = 0; i < 3; ++i)
    {
      run_a[static_cast<std::size_t> (i)] = capture_cpp (wave, txcall, 3, i == 0);
    }

  decodium::legacy::clear_echo_plot_state ();
  for (int i = 0; i < 3; ++i)
    {
      run_b[static_cast<std::size_t> (i)] = capture_cpp (wave, txcall, 3, i == 0);
    }

  for (int run = 0; run < 3; ++run)
    {
      EchoSnapshot const& lhs = run_a[static_cast<std::size_t> (run)];
      EchoSnapshot const& rhs = run_b[static_cast<std::size_t> (run)];
      if (lhs.nqual != rhs.nqual
          || !close_enough (lhs.xlevel, rhs.xlevel)
          || !close_enough (lhs.sigdb, rhs.sigdb)
          || !close_enough (lhs.db_err, rhs.db_err)
          || !close_enough (lhs.dfreq, rhs.dfreq)
          || !close_enough (lhs.width, rhs.width, 1.0e-4f, 1.0e-6f)
          || !close_enough (lhs.xdt, rhs.xdt, 1.0e-4f, 1.0e-6f)
          || lhs.rxcall.trimmed () != rhs.rxcall.trimmed ()
          || lhs.nsum != rhs.nsum)
        {
          return false;
        }
      for (int i = 0; i < kEchoNz; ++i)
        {
          if (!close_enough (lhs.blue[static_cast<std::size_t> (i)],
                             rhs.blue[static_cast<std::size_t> (i)], 2.0e-2f, 2.0e-4f)
              || !close_enough (lhs.red[static_cast<std::size_t> (i)],
                                rhs.red[static_cast<std::size_t> (i)], 2.0e-2f, 2.0e-4f))
            {
              return false;
            }
        }
    }

  return run_a[0].rxcall.trimmed () == txcall;
}
}

int main (int argc, char* argv[])
{
  QCoreApplication app {argc, argv};
  bool ok = compare_save_echo_params_roundtrip () && compare_avecho_determinism ();
  if (!ok)
    {
      std::fprintf (stderr, "legacy_echo_compare failed\n");
      return 1;
    }
  std::printf ("legacy_echo_compare OK\n");
  return 0;
}
