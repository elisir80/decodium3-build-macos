#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QLocale>
#include <QTemporaryDir>
#include <QTextStream>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <memory>
#include <vector>

#include "commons.h"
#include "Detector/LegacyDspIoHelpers.hpp"

// Stub required by hspec_update's MSK144 decode path
extern "C" void mskrtd_ (short[], int*, float*, int*, int*, int*, char*, char*, bool*, bool*,
                         double const[], bool*, char*, char* line,
                         size_t, size_t, size_t, size_t)
{
  if (line)
    {
      line[0] = '\0';
    }
}

namespace
{
constexpr int kHspecColumns = 703;
constexpr int kHspecRows = 64;
constexpr int kSampleCount = NTMAX * RX_SAMPLE_RATE;

bool close_enough (float lhs, float rhs, float abs_tol = 1.0e-3f, float rel_tol = 1.0e-4f)
{
  float const scale = std::max (1.0f, std::max (std::fabs (lhs), std::fabs (rhs)));
  return std::fabs (lhs - rhs) <= abs_tol + rel_tol * scale;
}

bool test_refspectrum ()
{
  QTemporaryDir dir;
  if (!dir.isValid ())
    {
      return false;
    }
  QString const path = QDir {dir.path ()}.filePath ("refspec.dat");

  std::vector<short> input (static_cast<std::size_t> (6912 / 2), 0);
  double const pi = 4.0 * std::atan (1.0);
  for (int i = 0; i < static_cast<int> (input.size ()); ++i)
    {
      double const sample = 9000.0 * std::sin (2.0 * pi * 1210.0 * i / 12000.0)
                          + 4500.0 * std::sin (2.0 * pi * 2030.0 * i / 12000.0);
      input[static_cast<std::size_t> (i)] = static_cast<short> (std::lround (sample));
    }

  decodium::legacy::reset_refspectrum_state ();
  decodium::legacy::clear_spectrum_plot_state ();

  bool clear = true;
  bool accumulate = true;
  bool use = false;
  for (int i = 0; i < 4; ++i)
    {
      decodium::legacy::refspectrum_update (input.data (), clear, accumulate, use, path);
      clear = false;
    }

  if (!QFile::exists (path))
    {
      std::fprintf (stderr, "refspectrum: output file not created\n");
      return false;
    }

  auto const& plot_state = decodium::legacy::spectrum_plot_state ();
  bool any_nonzero = false;
  for (int i = 1; i <= 3456; ++i)
    {
      if (plot_state.ref[static_cast<std::size_t> (i)] != 0.0f)
        {
          any_nonzero = true;
          break;
        }
    }
  if (!any_nonzero)
    {
      std::fprintf (stderr, "refspectrum: reference spectrum is all zeros\n");
      return false;
    }

  return true;
}

bool test_symspec ()
{
  decodium::legacy::clear_spectrum_plot_state ();

  std::unique_ptr<dec_data_t> shared {new dec_data_t {}};
  shared->params.ndiskdat = false;

  double const pi = 4.0 * std::atan (1.0);
  for (int i = 0; i < kSampleCount; ++i)
    {
      double const value = 9000.0 * std::sin (2.0 * pi * 1200.0 * i / 12000.0)
                         + 4000.0 * std::sin (2.0 * pi * 1620.0 * i / 12000.0);
      shared->d2[i] = static_cast<short> (std::lround (value));
    }

  int const nsps = 6912;
  int const ingain = 6;
  int const minw = 2;
  float pxdb = 0.0f;
  std::array<float, NSMAX> s {};
  float df3 = 0.0f;
  int ihsym = 0;
  int npts8 = 0;
  float pxdbmax = 0.0f;

  int k = 8192;
  for (int step = 0; step < 10; ++step, k += nsps / 2)
    {
      decodium::legacy::symspec_update (shared.get (), k, nsps, ingain,
                                        true, minw, &pxdb, s.data (),
                                        &df3, &ihsym, &npts8, &pxdbmax);
    }

  if (ihsym <= 0 || df3 <= 0.0f)
    {
      std::fprintf (stderr, "symspec: ihsym=%d df3=%g\n", ihsym, df3);
      return false;
    }

  bool any_nonzero = false;
  int const iz = std::min (NSMAX, static_cast<int> (std::lround (5000.0 / df3)));
  for (int i = 0; i < iz; ++i)
    {
      if (s[static_cast<std::size_t> (i)] != 0.0f)
        {
          any_nonzero = true;
          break;
        }
    }
  if (!any_nonzero)
    {
      std::fprintf (stderr, "symspec: spectrum is all zeros\n");
      return false;
    }

  return true;
}

bool test_hspec ()
{
  std::vector<short> input (static_cast<std::size_t> (30 * 12000), 0);
  double const pi = 4.0 * std::atan (1.0);
  for (size_t i = 0; i < input.size (); ++i)
    {
      double const value = 7000.0 * std::sin (2.0 * pi * 950.0 * i / 12000.0)
                         + 2500.0 * std::sin (2.0 * pi * 1680.0 * i / 12000.0);
      input[i] = static_cast<short> (std::lround (value));
    }

  std::array<float, kHspecColumns> green {};
  std::array<float, kHspecColumns * kHspecRows> spec {};
  int k = 4096;
  int ntrpdepth = 30000;
  int ingain = 3;
  float pxmax = 0.0f;
  float rms = 0.0f;
  int jh = 0;

  decodium::legacy::hspec_update (input.data (), k, ntrpdepth, ingain,
                                   green.data (), spec.data (), &jh, &pxmax, &rms);

  if (jh < 0)
    {
      std::fprintf (stderr, "hspec: jh=%d\n", jh);
      return false;
    }

  return true;
}

}

int main (int argc, char** argv)
{
  QCoreApplication app {argc, argv};
  bool const refspectrum_ok = test_refspectrum ();
  bool const symspec_ok = test_symspec ();
  bool const hspec_ok = test_hspec ();
  std::printf ("refspectrum=%s symspec=%s hspec=%s\n",
               refspectrum_ok ? "ok" : "fail",
               symspec_ok ? "ok" : "fail",
               hspec_ok ? "ok" : "fail");
  if (!(refspectrum_ok && symspec_ok && hspec_ok))
    {
      return 1;
    }

  std::printf ("Legacy spectrum tests passed for refspectrum, symspec and hspec\n");
  return 0;
}
