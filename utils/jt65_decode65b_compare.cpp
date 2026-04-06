#include <QByteArray>
#include <QCoreApplication>

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

bool same_result (decodium::legacy::Jt65Decode65bResult const& lhs,
                  decodium::legacy::Jt65Decode65bResult const& rhs)
{
  return lhs.nft == rhs.nft && lhs.nhist == rhs.nhist
         && std::fabs (static_cast<double> (lhs.qual - rhs.qual)) <= 1.0e-6
         && fixed_field (lhs.decoded, 22) == fixed_field (rhs.decoded, 22);
}

void run_case (std::mt19937& rng, int trial)
{
  std::uniform_real_distribution<float> dist (-5.0f, 25.0f);
  std::array<float, 66 * 126> s2 {};
  for (float& value : s2)
    {
      value = dist (rng);
    }

  int const nflip = (trial % 2 == 0) ? 1 : -1;
  int const nadd = 1 + (trial % 6);
  int const mode65 = 1;
  int const ntrials = 80 + trial;
  int const naggressive = (trial % 3 == 0) ? 10 : 0;
  int const ndepth = (trial % 4 == 0) ? 32 : 1;
  int const nQSOProgress = trial % 6;
  bool const ljt65apon = (trial % 2 == 0);
  QByteArray const mycall = fixed_field ("K1ABC       ", 12);
  QByteArray const hiscall = fixed_field ("W9XYZ       ", 12);
  QByteArray const hisgrid = fixed_field ("EN34  ", 6);

  auto const first = decodium::legacy::decode65b_compute (
      s2.data (), nflip, nadd, mode65, ntrials, naggressive, ndepth, mycall, hiscall, hisgrid,
      nQSOProgress, ljt65apon);
  auto const second = decodium::legacy::decode65b_compute (
      s2.data (), nflip, nadd, mode65, ntrials, naggressive, ndepth, mycall, hiscall, hisgrid,
      nQSOProgress, ljt65apon);

  if (!same_result (first, second))
    {
      std::fprintf (stderr,
                    "decode65b state mismatch trial=%d first(nft=%d qual=%g nhist=%d decoded='%.*s') "
                    "second(nft=%d qual=%g nhist=%d decoded='%.*s')\n",
                    trial, first.nft, static_cast<double> (first.qual), first.nhist,
                    first.decoded.size (), first.decoded.constData (), second.nft,
                    static_cast<double> (second.qual), second.nhist, second.decoded.size (),
                    second.decoded.constData ());
      fail ("decode65b");
    }
}

}  // namespace

int main (int argc, char** argv)
{
  try
    {
      QCoreApplication app {argc, argv};
      decodium::legacy::jt65_initialize_tables ();
      std::mt19937 rng {0x65BEEF};
      for (int trial = 0; trial < 16; ++trial)
        {
          run_case (rng, trial);
        }
      std::printf ("JT65 decode65b state compare passed\n");
      return 0;
    }
  catch (std::exception const& e)
    {
      std::fprintf (stderr, "jt65_decode65b_compare failed: %s\n", e.what ());
      return 1;
    }
}
