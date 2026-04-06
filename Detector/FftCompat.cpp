#include "Detector/FftCompat.hpp"

namespace decodium
{
namespace fft_compat
{

void forward_real (std::vector<std::complex<float>>& buffer, int nfft)
{
  legacy_fft_execute (buffer.data (), nfft, -1, 0);
}

void inverse_real (std::vector<std::complex<float>>& buffer, int nfft)
{
  legacy_fft_execute (buffer.data (), nfft, 1, -1);
}

void forward_real_buffer (float* buffer, int nfft)
{
  legacy_fft_execute (reinterpret_cast<std::complex<float>*> (buffer), nfft, -1, 0);
}

void inverse_real_buffer (float* buffer, int nfft)
{
  legacy_fft_execute (reinterpret_cast<std::complex<float>*> (buffer), nfft, 1, -1);
}

void forward_complex (std::complex<float>* buffer, int nfft)
{
  legacy_fft_execute (buffer, nfft, -1, 1);
}

void inverse_complex (std::complex<float>* buffer, int nfft)
{
  legacy_fft_execute (buffer, nfft, 1, 1);
}

void transform_complex (std::complex<float>* buffer, int nfft, int isign)
{
  legacy_fft_execute (buffer, nfft, isign, 1);
}

void cleanup ()
{
  legacy_fft_cleanup ();
}

}
}
