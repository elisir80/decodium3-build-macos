#include <QCoreApplication>

#include <algorithm>
#include <array>
#include <cstdio>
#include <random>
#include <stdexcept>
#include <string>

#include "Detector/LegacyDspIoHelpers.hpp"
#include "Modulator/LegacyJtEncoder.hpp"

namespace
{

[[noreturn]] void fail (std::string const& message)
{
  throw std::runtime_error {message};
}

void fill_symbols (std::array<int, 63>& data, std::mt19937& rng)
{
  std::uniform_int_distribution<int> dist (0, 63);
  for (int& value : data)
    {
      value = dist (rng);
    }
}

void compare_graycode (std::mt19937& rng)
{
  for (int trial = 0; trial < 16; ++trial)
    {
      std::array<int, 63> data {};
      fill_symbols (data, rng);

      std::array<int, 63> encoded = data;
      decodium::legacy::graycode65_inplace (encoded.data (), 63, 1);
      for (std::size_t i = 0; i < encoded.size (); ++i)
        {
          int const expected =
              decodium::legacy_jt::detail::gray_encode (data[static_cast<std::size_t> (i)]);
          if (encoded[i] != expected)
            {
              fail ("graycode65 forward compare failed");
            }
        }

      decodium::legacy::graycode65_inplace (encoded.data (), 63, -1);
      if (encoded != data)
        {
          fail ("graycode65 roundtrip failed");
        }
    }
}

void compare_interleave (std::mt19937& rng)
{
  for (int trial = 0; trial < 16; ++trial)
    {
      std::array<int, 63> data {};
      std::uniform_int_distribution<int> dist (0, 255);
      for (int& value : data)
        {
          value = dist (rng);
        }

      std::array<int, 63> encoded = data;
      decodium::legacy::interleave63_inplace (encoded.data (), 1);

      std::array<int, 63> expected = data;
      decodium::legacy_jt::detail::interleave63 (expected);
      if (encoded != expected)
        {
          fail ("interleave63 forward compare failed");
        }

      decodium::legacy::interleave63_inplace (encoded.data (), -1);
      if (encoded != data)
        {
          fail ("interleave63 roundtrip failed");
        }
    }
}

void compare_demod (std::mt19937& rng)
{
  std::uniform_real_distribution<float> dist (0.0f, 10.0f);
  for (int trial = 0; trial < 8; ++trial)
    {
      std::array<float, 64 * 63> s3 {};
      for (float& value : s3)
        {
          value = dist (rng);
        }

      int const nadd = 1 + (trial % 5);
      float const afac1 = 1.1f + 0.1f * trial;
      auto const first = decodium::legacy::demod64a_compute (s3.data (), nadd, afac1);
      auto const second = decodium::legacy::demod64a_compute (s3.data (), nadd, afac1);

      if (first.mrsym != second.mrsym || first.mrprob != second.mrprob
          || first.mr2sym != second.mr2sym || first.mr2prob != second.mr2prob
          || first.ntest != second.ntest || first.nlow != second.nlow)
        {
          fail ("demod64a determinism compare failed");
        }
    }
}

}  // namespace

int main (int argc, char** argv)
{
  try
    {
      QCoreApplication app {argc, argv};
      std::mt19937 rng {0x65A65A};
      compare_graycode (rng);
      compare_interleave (rng);
      compare_demod (rng);
      std::printf ("JT65 extract primitive compare passed\n");
      return 0;
    }
  catch (std::exception const& e)
    {
      std::fprintf (stderr, "jt65_extract_primitives_compare failed: %s\n", e.what ());
      return 1;
    }
}
