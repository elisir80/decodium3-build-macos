#include <QCoreApplication>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <random>
#include <stdexcept>

#include "Detector/LegacyDspIoHelpers.hpp"

namespace
{

[[noreturn]] void fail (char const* message)
{
  throw std::runtime_error {message};
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

template <typename T, std::size_t N>
void compare_array_exact (std::array<T, N> const& lhs, T const* rhs, char const* label)
{
  for (std::size_t i = 0; i < N; ++i)
    {
      if (lhs[i] != rhs[i])
        {
          std::fprintf (stderr, "%s mismatch at %zu: lhs=%d rhs=%d\n", label, i,
                        static_cast<int> (lhs[i]), static_cast<int> (rhs[i]));
          fail (label);
        }
    }
}

template <std::size_t N>
void compare_array_float (std::array<float, N> const& lhs, float const* rhs, char const* label,
                          double tolerance)
{
  for (std::size_t i = 0; i < N; ++i)
    {
      if (std::fabs (static_cast<double> (lhs[i] - rhs[i])) > tolerance)
        {
          std::fprintf (stderr, "%s mismatch at %zu: lhs=%g rhs=%g\n", label, i,
                        static_cast<double> (lhs[i]), static_cast<double> (rhs[i]));
          fail (label);
        }
    }
}

void run_case (std::mt19937& rng, int trial)
{
  std::uniform_real_distribution<float> dist (0.05f, 10.0f);
  std::array<float, 64 * 63> s3 {};
  for (float& value : s3)
    {
      value = dist (rng);
    }

  int const nadd = 1 + (trial % 8);
  int const mode65 = 1;
  int const ntrials = 80 + trial;
  int const naggressive = (trial % 3 == 0) ? 10 : 0;
  int const ndepth = (trial % 4 == 0) ? 32 : 1;
  int const nflip = (trial % 2 == 0) ? 1 : -1;
  int const nQSOProgress = trial % 6;
  bool const ljt65apon = (trial % 2) == 0;

  QByteArray const mycall = fixed_field (QByteArray ("K1ABC       ", 12), 12);
  QByteArray const hiscall = fixed_field (QByteArray ("W9XYZ       ", 12), 12);
  QByteArray const hisgrid = fixed_field (QByteArray ("EN34  ", 6), 6);

  auto const direct = decodium::legacy::extract_compute (s3.data (), nadd, mode65, ntrials,
                                                         naggressive, ndepth, nflip, mycall,
                                                         hiscall, hisgrid, nQSOProgress,
                                                         ljt65apon);
  auto const shared = decodium::legacy::jt65_shared_state ();

  compare_array_exact (direct.mrs, shared.mrs, "mrs");
  compare_array_exact (direct.mrs2, shared.mrs2, "mrs2");
  compare_array_exact (direct.correct, shared.correct, "correct");
  compare_array_float (direct.s3a, shared.s3a, "s3a", 1.0e-6);
  compare_array_exact (direct.param, shared.param, "param");
}

}  // namespace

int main (int argc, char** argv)
{
  try
    {
      QCoreApplication app {argc, argv};
      std::mt19937 rng {0x65E123u};
      decodium::legacy::jt65_initialize_tables ();
      for (int trial = 0; trial < 12; ++trial)
        {
          run_case (rng, trial);
        }
      std::printf ("JT65 extract state compare passed\n");
      return 0;
    }
  catch (std::exception const& e)
    {
      std::fprintf (stderr, "jt65_extract_compare failed: %s\n", e.what ());
      return 1;
    }
}
