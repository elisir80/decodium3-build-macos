#include "Detector/FftCompat.hpp"
#include "qmap/commons.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

namespace
{
constexpr int kQmapNsmax {60 * 96000};
constexpr int kQmapNfft {32768};
constexpr int kQmapFftbigSize {5376000};
constexpr int kQmapCacbSize {2 * kQmapFftbigSize};
constexpr int kTimf2Maxfft {1024};
constexpr int kTimf2MaxSignals {100};

using Complex = std::complex<float>;

std::string trim_fortran_string (char const* data, int len)
{
  if (!data || len <= 0)
    {
      return {};
    }

  std::string value {data, data + len};
  while (!value.empty () && (value.back () == ' ' || value.back () == '\0'))
    {
      value.pop_back ();
    }
  return value;
}

template <std::size_t N>
void copy_fixed_string (char const* src, int len, std::array<char, N>* dest)
{
  if (!dest)
    {
      return;
    }

  dest->fill (' ');
  if (!src || len <= 0)
    {
      return;
    }

  std::size_t const count = std::min<std::size_t> (static_cast<std::size_t> (len), N);
  std::memcpy (dest->data (), src, count);
}

struct Timf2State
{
  bool initialized {false};
  int last_k {99999999};
  int nh {0};
  int kstep {kTimf2Maxfft};
  float fac {1.0f / kTimf2Maxfft};
  float slimit {1.0e30f};
  std::array<float, kTimf2Maxfft> window {};
  std::array<Complex, kTimf2Maxfft / 2> overlap_strong {};
  std::array<Complex, kTimf2Maxfft / 2> overlap_weak {};
};

struct SymspecState
{
  bool initialized {false};
  float rms {999.0f};
  int last_k {99999999};
  int k1 {0};
  double ts {0.0};
  std::array<float, kQmapNfft> window {};
  Timf2State timf2 {};
};

Timf2State& timf2_state ()
{
  static Timf2State state;
  return state;
}

SymspecState& symspec_state ()
{
  static SymspecState state;
  return state;
}

void timf2_process (int k, int nfft, int nwindow, int nb, float peaklimit,
                    Complex const* cx0, Complex* cx1, float* slimit,
                    unsigned char* lstrong, float* px, int* nzap)
{
  if (!cx0 || !cx1 || !slimit || !lstrong || !px || !nzap || nfft <= 0 || nfft > kTimf2Maxfft)
    {
      return;
    }

  auto& state = timf2_state ();
  if (!state.initialized)
    {
      float const pi = 4.0f * std::atan (1.0f);
      for (int i = 0; i < nfft; ++i)
        {
          state.window[static_cast<std::size_t> (i)] =
              std::pow (std::sin (static_cast<float> (i) * pi / static_cast<float> (nfft)), 2.0f);
        }
      state.nh = nfft / 2;
      state.kstep = (nwindow == 2) ? state.nh : nfft;
      state.fac = 1.0f / static_cast<float> (nfft);
      state.slimit = 1.0e30f;
      state.initialized = true;
    }

  if (k < state.last_k)
    {
      std::fill (state.overlap_strong.begin (), state.overlap_strong.end (), Complex {});
      std::fill (state.overlap_weak.begin (), state.overlap_weak.end (), Complex {});
    }
  state.last_k = k;

  std::array<Complex, kTimf2Maxfft> cx {};
  std::array<Complex, kTimf2Maxfft> cxt {};
  std::array<Complex, kTimf2Maxfft> strong {};
  std::array<Complex, kTimf2Maxfft> weak {};
  std::array<float, kTimf2Maxfft> power {};
  std::array<int, kTimf2MaxSignals> ia {};
  std::array<int, kTimf2MaxSignals> ib {};

  std::copy_n (cx0, nfft, cx.begin ());
  if (nwindow == 2)
    {
      for (int i = 0; i < nfft; ++i)
        {
          cx[static_cast<std::size_t> (i)] *= state.window[static_cast<std::size_t> (i)];
        }
    }

  decodium::fft_compat::transform_complex (cx.data (), nfft, 1);
  std::copy_n (cx.begin (), nfft, cxt.begin ());

  float ave = 0.0f;
  for (int i = 0; i < nfft; ++i)
    {
      float const p = std::norm (cxt[static_cast<std::size_t> (i)]);
      power[static_cast<std::size_t> (i)] = p;
      ave += p;
    }
  ave /= static_cast<float> (nfft);

  for (int i = 0; i < nfft; ++i)
    {
      lstrong[i] = power[static_cast<std::size_t> (i)] > 10.0f * ave ? 1u : 0u;
    }

  int nsigs = 0;
  bool lprev = false;
  int constexpr iwid = 1;
  for (int i = 0; i < nfft; ++i)
    {
      bool const is_strong = lstrong[i] != 0;
      if (is_strong && !lprev)
        {
          if (nsigs < kTimf2MaxSignals)
            {
              ia[static_cast<std::size_t> (nsigs)] = std::max (0, i - iwid);
              ib[static_cast<std::size_t> (nsigs)] = -99;
              ++nsigs;
            }
        }
      if (!is_strong && lprev && nsigs > 0)
        {
          ib[static_cast<std::size_t> (nsigs - 1)] = std::min (nfft - 1, i - 1 + iwid);
        }
      lprev = is_strong;
    }
  if (nsigs > 0 && ib[static_cast<std::size_t> (nsigs - 1)] == -99)
    {
      ib[static_cast<std::size_t> (nsigs - 1)] =
          std::min (nfft - 1, ia[static_cast<std::size_t> (nsigs - 1)] + 2 * iwid);
    }

  for (int sig = 0; sig < nsigs; ++sig)
    {
      for (int i = ia[static_cast<std::size_t> (sig)]; i <= ib[static_cast<std::size_t> (sig)]; ++i)
        {
          lstrong[i] = 1u;
        }
    }

  for (int i = 0; i < nfft; ++i)
    {
      if (lstrong[i] != 0)
        {
          strong[static_cast<std::size_t> (i)] = state.fac * cxt[static_cast<std::size_t> (i)];
          weak[static_cast<std::size_t> (i)] = Complex {};
        }
      else
        {
          weak[static_cast<std::size_t> (i)] = state.fac * cxt[static_cast<std::size_t> (i)];
          strong[static_cast<std::size_t> (i)] = Complex {};
        }
    }

  decodium::fft_compat::transform_complex (weak.data (), nfft, -1);
  decodium::fft_compat::transform_complex (strong.data (), nfft, -1);

  if (nwindow == 2)
    {
      for (int i = 0; i < state.nh; ++i)
        {
          weak[static_cast<std::size_t> (i)] += state.overlap_weak[static_cast<std::size_t> (i)];
          state.overlap_weak[static_cast<std::size_t> (i)] = weak[static_cast<std::size_t> (i + state.nh)];
          strong[static_cast<std::size_t> (i)] += state.overlap_strong[static_cast<std::size_t> (i)];
          state.overlap_strong[static_cast<std::size_t> (i)] = strong[static_cast<std::size_t> (i + state.nh)];
        }
    }

  if (nb != 0)
    {
      for (int i = 0; i < state.kstep; ++i)
        {
          if (std::abs (weak[static_cast<std::size_t> (i)]) > peaklimit)
            {
              weak[static_cast<std::size_t> (i)] = Complex {};
              ++(*nzap);
            }
        }
    }

  for (int i = 0; i < state.kstep; ++i)
    {
      *px += std::norm (weak[static_cast<std::size_t> (i)]);
      cx1[i] = weak[static_cast<std::size_t> (i)] + strong[static_cast<std::size_t> (i)];
    }
  *slimit = state.slimit;
}

} // namespace

std::complex<float> cacb_[kQmapCacbSize] {};

extern "C"
{

void ftninit_ ()
{
  std::ofstream {"all_qmap.txt", std::ios::app};
  std::ofstream {"red.dat", std::ios::app};
}

void fftbig_ (float dd[], int* nmax)
{
  if (!nmax)
    {
      return;
    }
  if (*nmax < 0)
    {
      decodium::fft_compat::cleanup ();
      return;
    }
  if (!dd || *nmax <= 0)
    {
      return;
    }

  int const nz = std::min (*nmax, kQmapFftbigSize);
  for (int i = 0; i < nz; ++i)
    {
      std::size_t const base = 2u * static_cast<std::size_t> (i);
      cacb_[static_cast<std::size_t> (i)] = Complex {dd[base], dd[base + 1]};
    }
  std::fill (cacb_ + nz, cacb_ + kQmapFftbigSize, Complex {});
  decodium::fft_compat::transform_complex (cacb_, kQmapFftbigSize, 1);
}

void recvpkt_ (int* nsam, unsigned short* /*nblock2*/, signed char* userx_no,
               int* k, double buf4[], double buf8[], int* ndb)
{
  if (!nsam || !userx_no || !k || !ndb)
    {
      return;
    }

  int const userx = static_cast<int> (*userx_no);
  float const gain = std::pow (10.0f, 0.05f * static_cast<float> (*ndb));
  auto store_sample = [&] (float i_value, float q_value) {
    if (*k >= kQmapNsmax)
      {
        return;
      }
    ++(*k);
    std::size_t const base = 2u * static_cast<std::size_t> (*k - 1);
    datcom_.d4[base] = i_value * gain;
    datcom_.d4[base + 1] = q_value * gain;
  };

  if (*nsam == -1)
    {
      if (userx == -1 && buf8)
        {
          for (int i = 0; i < 174; ++i)
            {
              float yd[2] {};
              std::memcpy (yd, &buf8[i], sizeof (yd));
              store_sample (yd[0], yd[1]);
            }
        }
      else if (userx == 1 && buf4)
        {
          float const* raw = reinterpret_cast<float const*> (buf4);
          for (int i = 0; i < 348; ++i)
            {
              std::int16_t kd[2] {};
              std::memcpy (kd, &raw[i], sizeof (kd));
              store_sample (static_cast<float> (kd[0]), static_cast<float> (kd[1]));
            }
        }
      return;
    }

  if (userx == 1 && buf4)
    {
      float const* raw = reinterpret_cast<float const*> (buf4);
      for (int i = 0; i < *nsam; ++i)
        {
          std::int16_t kd[2] {};
          std::memcpy (kd, &raw[i], sizeof (kd));
          store_sample (static_cast<float> (kd[0]), static_cast<float> (kd[1]));
          store_sample (static_cast<float> (kd[0]), static_cast<float> (kd[1]));
        }
    }
}

void zaptx_ (float d4[], int* k0, int* k)
{
  if (!d4 || !k0 || !k || *k <= *k0)
    {
      return;
    }

  int const start = std::max (0, *k0);
  int const stop = std::min (*k, kQmapNsmax);
  if (stop <= start)
    {
      return;
    }

  std::fill_n (d4 + 2u * static_cast<std::size_t> (start),
               2u * static_cast<std::size_t> (stop - start), 0.0f);
}

void read_qm_ (char const* fname, int* iret, int len)
{
  if (!iret)
    {
      return;
    }

  std::string const path = trim_fortran_string (fname, len);
  std::ifstream in {path, std::ios::binary};
  if (!in)
    {
      *iret = -1;
      return;
    }

  std::array<char, 24> prog_id {};
  std::array<char, 12> mycall {};
  std::array<char, 6> mygrid {};
  double fcenter = 0.0;
  int nutc = 0;
  int ntx30a = 0;
  int ntx30b = 0;
  int ndop00 = 0;
  int ndop58 = 0;
  int ia = 0;
  int ib = 0;
  float fac0 = 0.0f;
  std::array<int, 15> nxtra {};

  auto failed = [&] () {
    *iret = -2;
    return;
  };

  in.read (prog_id.data (), static_cast<std::streamsize> (prog_id.size ()));
  in.read (mycall.data (), static_cast<std::streamsize> (mycall.size ()));
  in.read (mygrid.data (), static_cast<std::streamsize> (mygrid.size ()));
  in.read (reinterpret_cast<char*> (&fcenter), sizeof (fcenter));
  in.read (reinterpret_cast<char*> (&nutc), sizeof (nutc));
  in.read (reinterpret_cast<char*> (&ntx30a), sizeof (ntx30a));
  in.read (reinterpret_cast<char*> (&ntx30b), sizeof (ntx30b));
  in.read (reinterpret_cast<char*> (&ndop00), sizeof (ndop00));
  in.read (reinterpret_cast<char*> (&ndop58), sizeof (ndop58));
  in.read (reinterpret_cast<char*> (&ia), sizeof (ia));
  in.read (reinterpret_cast<char*> (&ib), sizeof (ib));
  in.read (reinterpret_cast<char*> (&fac0), sizeof (fac0));
  in.read (reinterpret_cast<char*> (nxtra.data ()), sizeof (nxtra));
  if (!in)
    {
      failed ();
      return;
    }

  *iret = 3;
  if (ib == kQmapNsmax / 2)
    {
      *iret = 1;
    }
  if (ia == kQmapNsmax / 2 + 1)
    {
      *iret = 2;
    }

  float fac = 1.0f;
  if (fac0 > 0.0f)
    {
      fac = 1.0f / fac0;
    }

  if (ia < 1 || ib < ia || ib > kQmapNsmax)
    {
      failed ();
      return;
    }

  std::vector<std::int8_t> id1 (2u * static_cast<std::size_t> (ib - ia + 1), 0);
  in.read (reinterpret_cast<char*> (id1.data ()),
           static_cast<std::streamsize> (id1.size ()));
  if (!in)
    {
      failed ();
      return;
    }

  std::fill (std::begin (datcom_.d4), std::end (datcom_.d4), 0.0f);
  for (int sample = ia - 1; sample < ib; ++sample)
    {
      std::size_t const src = 2u * static_cast<std::size_t> (sample - (ia - 1));
      std::size_t const dst = 2u * static_cast<std::size_t> (sample);
      datcom_.d4[dst] = fac * static_cast<float> (id1[src]);
      datcom_.d4[dst + 1] = fac * static_cast<float> (id1[src + 1]);
    }

  datcom_.fcenter = fcenter;
  datcom_.nutc = nutc;
  datcom_.ntx30a = ntx30a;
  datcom_.ntx30b = ntx30b;
  datcom_.ndop00 = ndop00;
  datcom_.ndop58 = ndop58;
}

void save_qm_ (char const* fname, char const* revision, char const* mycall, char const* mygrid,
               float dd[], int* ntx30a, int* ntx30b, double* fcenter, int* nutc,
               int* ndop00, int* ndop58, int len1, int len2, int len3, int len4)
{
  if (!fname || !dd || !ntx30a || !ntx30b || !fcenter || !nutc || !ndop00 || !ndop58)
    {
      return;
    }

  int ia = 1;
  int ib = kQmapNsmax;
  if (*ntx30a > 5)
    {
      ia = kQmapNsmax / 2 + 1;
    }
  if (*ntx30b > 5)
    {
      ib = kQmapNsmax / 2;
    }

  double sq = 0.0;
  for (int sample = ia - 1; sample < ib; ++sample)
    {
      std::size_t const base = 2u * static_cast<std::size_t> (sample);
      float const x = dd[base];
      float const y = dd[base + 1];
      sq += x * x + y * y;
    }
  int const nsum = 2 * (ib - ia + 1);
  float const rms = nsum > 0 ? std::sqrt (static_cast<float> (sq / nsum)) : 1.0f;
  float const fac0 = rms > 0.0f ? 10.0f / rms : 0.0f;

  std::vector<std::int8_t> id1 (2u * static_cast<std::size_t> (kQmapNsmax), 0);
  for (int sample = ia - 1; sample < ib; ++sample)
    {
      std::size_t const base = 2u * static_cast<std::size_t> (sample);
      float x = fac0 * dd[base];
      float y = fac0 * dd[base + 1];
      if (std::fabs (x) > 127.0f)
        {
          x = 0.0f;
        }
      if (std::fabs (y) > 127.0f)
        {
          y = 0.0f;
        }
      id1[base] = static_cast<std::int8_t> (std::lround (x));
      id1[base + 1] = static_cast<std::int8_t> (std::lround (y));
    }

  std::ofstream out {trim_fortran_string (fname, len1), std::ios::binary};
  if (!out)
    {
      return;
    }

  std::array<char, 24> revision24 {};
  std::array<char, 12> mycall12 {};
  std::array<char, 6> mygrid6 {};
  std::array<int, 15> nxtra {};
  copy_fixed_string (revision, len2, &revision24);
  copy_fixed_string (mycall, len3, &mycall12);
  copy_fixed_string (mygrid, len4, &mygrid6);

  out.write (revision24.data (), static_cast<std::streamsize> (revision24.size ()));
  out.write (mycall12.data (), static_cast<std::streamsize> (mycall12.size ()));
  out.write (mygrid6.data (), static_cast<std::streamsize> (mygrid6.size ()));
  out.write (reinterpret_cast<char const*> (fcenter), sizeof (*fcenter));
  out.write (reinterpret_cast<char const*> (nutc), sizeof (*nutc));
  out.write (reinterpret_cast<char const*> (ntx30a), sizeof (*ntx30a));
  out.write (reinterpret_cast<char const*> (ntx30b), sizeof (*ntx30b));
  out.write (reinterpret_cast<char const*> (ndop00), sizeof (*ndop00));
  out.write (reinterpret_cast<char const*> (ndop58), sizeof (*ndop58));
  out.write (reinterpret_cast<char const*> (&ia), sizeof (ia));
  out.write (reinterpret_cast<char const*> (&ib), sizeof (ib));
  out.write (reinterpret_cast<char const*> (&fac0), sizeof (fac0));
  out.write (reinterpret_cast<char const*> (nxtra.data ()), sizeof (nxtra));
  out.write (reinterpret_cast<char const*> (id1.data () + 2u * static_cast<std::size_t> (ia - 1)),
             static_cast<std::streamsize> (2u * static_cast<std::size_t> (ib - ia + 1)));
}

void symspec_ (int* k, int* ndiskdat, int* nb, int* nbslider, int* /*nfsample*/,
               float* pxdb, float ssz5a[], int* nkhz, int* ihsym,
               int* nzap, float* slimit, unsigned char lstrong[])
{
  if (!k || !ndiskdat || !nb || !nbslider || !pxdb || !ssz5a || !nkhz || !ihsym || !nzap || !slimit
      || !lstrong)
    {
      return;
    }

  auto& state = symspec_state ();
  if (!state.initialized)
    {
      std::fill (state.window.begin (), state.window.end (), 0.7f);
      state.initialized = true;
    }

  double const hsym = 0.15 * 96000.0;
  int const npts = static_cast<int> (2.0 * hsym);
  if (*k > 5751000)
    {
      return;
    }
  if (*k < npts)
    {
      *ihsym = 0;
      return;
    }

  if (*k < state.last_k)
    {
      state.ts = 1.0 - hsym;
      std::fill (std::begin (datcom_.ss), std::end (datcom_.ss), 0.0f);
      std::fill (std::begin (datcom_.savg), std::end (datcom_.savg), 0.0f);
      *ihsym = 0;
      state.k1 = 0;
      if (*ndiskdat == 0)
        {
          std::fill (datcom_.d4 + 2u * static_cast<std::size_t> (*k),
                     datcom_.d4 + 2u * static_cast<std::size_t> (kQmapNsmax), 0.0f);
        }
    }
  state.last_k = *k;

  *nzap = 0;
  float const sigmas = 1.5f * std::pow (10.0f, 0.01f * static_cast<float> (*nbslider)) + 0.7f;
  float const peaklimit = sigmas * std::max (10.0f, state.rms);
  float px = 0.0f;

  int const nwindow = 2;
  int const nfft2 = 1024;
  int kstep = nfft2;
  if (nwindow != 0)
    {
      kstep = nfft2 / 2;
    }
  int const nblks = (*k - state.k1) / kstep;

  std::array<Complex, 1024> cx0 {};
  std::array<Complex, 1024> cx1 {};
  for (int nblk = 0; nblk < nblks; ++nblk)
    {
      int const j = state.k1;
      for (int i = 0; i < nfft2; ++i)
        {
          std::size_t const base = 2u * static_cast<std::size_t> (j + i);
          cx0[static_cast<std::size_t> (i)] = Complex {datcom_.d4[base], datcom_.d4[base + 1]};
        }

      timf2_process (*k, nfft2, nwindow, *nb, peaklimit,
                     cx0.data (), cx1.data (), slimit, lstrong, &px, nzap);

      for (int i = 0; i < kstep; ++i)
        {
          std::size_t const base = 2u * static_cast<std::size_t> (j + i);
          datcom_.d4[base] = cx1[static_cast<std::size_t> (i)].real ();
          datcom_.d4[base + 1] = cx1[static_cast<std::size_t> (i)].imag ();
        }
      state.k1 += kstep;
    }

  state.ts += hsym;
  int const ja = static_cast<int> (state.ts);
  int const jb = ja + npts - 1;
  std::vector<Complex> cx (kQmapNfft, Complex {});
  constexpr float fac = 0.0002f;
  for (int j = ja, i = 0; j <= jb; ++j, ++i)
    {
      std::size_t const base = 2u * static_cast<std::size_t> (j - 1);
      cx[static_cast<std::size_t> (i)] =
          fac * Complex {datcom_.d4[base], datcom_.d4[base + 1]};
    }

  if ((*nzap / 178) < 50 && (*ndiskdat == 0 || *ihsym < 280))
    {
      int nsum = nblks * kstep - *nzap;
      if (nsum <= 0)
        {
          nsum = 1;
        }
      float const rmsx = std::sqrt (px / static_cast<float> (nsum));
      state.rms = rmsx;
      *pxdb = 0.0f;
      if (rmsx > 1.0f)
        {
          *pxdb = 20.0f * std::log10 (rmsx);
        }
      if (*pxdb > 60.0f)
        {
          *pxdb = 60.0f;
        }
    }
  else
    {
      *pxdb = 0.0f;
    }

  for (int i = 0; i < kQmapNfft; ++i)
    {
      cx[static_cast<std::size_t> (i)] *= state.window[static_cast<std::size_t> (i)];
    }
  decodium::fft_compat::transform_complex (cx.data (), kQmapNfft, 1);

  int const n = std::min (400, *ihsym + 1);
  for (int i = 0; i < kQmapNfft; ++i)
    {
      float const sx = std::norm (cx[static_cast<std::size_t> (i)]);
      datcom_.ss[static_cast<std::size_t> (n - 1) + 400u * static_cast<std::size_t> (i)] = sx;
      datcom_.savg[static_cast<std::size_t> (i)] += sx;
      ssz5a[i] = sx;
    }
  *ihsym = *ihsym + 1;

  *nkhz = static_cast<int> (std::lround (1000.0 * (datcom_.fcenter - std::floor (datcom_.fcenter))));
  if (datcom_.fcenter == 0.0)
    {
      *nkhz = 125;
    }
}

} // extern "C"
