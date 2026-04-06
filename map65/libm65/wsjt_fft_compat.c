#include <fftw3.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
  FFT_PLAN_MAX = 2100,
  FFT_SCRATCH_LIMIT = 16384
};

typedef struct
{
  int nfft;
  int isign;
  int iform;
  uintptr_t address;
  fftwf_plan plan;
} fft_plan_slot_t;

static fft_plan_slot_t g_fft_plan_slots[FFT_PLAN_MAX];
static int g_fft_plan_count = 0;

static int same_request (fft_plan_slot_t const* slot, fftwf_complex const* data,
                         int nfft, int isign, int iform)
{
  return slot
      && slot->nfft == nfft
      && slot->isign == isign
      && slot->iform == iform
      && slot->address == (uintptr_t) data;
}

static void destroy_all_plans (void)
{
  int i;
  for (i = 0; i < g_fft_plan_count; ++i)
    {
      if (g_fft_plan_slots[i].plan)
        {
          fftwf_destroy_plan (g_fft_plan_slots[i].plan);
          g_fft_plan_slots[i].plan = NULL;
        }
    }
  g_fft_plan_count = 0;
}

static fftwf_plan create_plan (fftwf_complex* data, int nfft, int isign, int iform)
{
  float* real_data = (float*) data;

  if (isign == -1 && iform == 1)
    {
      return fftwf_plan_dft_1d (nfft, data, data, FFTW_FORWARD, FFTW_ESTIMATE);
    }
  if (isign == 1 && iform == 1)
    {
      return fftwf_plan_dft_1d (nfft, data, data, FFTW_BACKWARD, FFTW_ESTIMATE);
    }
  if (isign == -1 && iform == 0)
    {
      return fftwf_plan_dft_r2c_1d (nfft, real_data, data, FFTW_ESTIMATE);
    }
  if (isign == 1 && iform == -1)
    {
      return fftwf_plan_dft_c2r_1d (nfft, data, real_data, FFTW_ESTIMATE);
    }

  fprintf (stderr, "Unsupported request in wsjt_fft_compat: nfft=%d isign=%d iform=%d\n",
           nfft, isign, iform);
  abort ();
}

void wsjt_fft_compat_ (fftwf_complex data[], int* nfft, int* ndim, int* isign, int* iform)
{
  int i;
  int complex_count;
  size_t scratch_bytes;
  fftwf_complex scratch[FFT_SCRATCH_LIMIT];

  (void) ndim;

  if (!nfft)
    {
      return;
    }

  if (*nfft < 0)
    {
      destroy_all_plans ();
      return;
    }

  if (!data || !isign || !iform || *nfft == 0)
    {
      return;
    }

  for (i = 0; i < g_fft_plan_count; ++i)
    {
      if (same_request (&g_fft_plan_slots[i], data, *nfft, *isign, *iform))
        {
          fftwf_execute (g_fft_plan_slots[i].plan);
          return;
        }
    }

  if (g_fft_plan_count >= FFT_PLAN_MAX)
    {
      fprintf (stderr, "Too many FFTW plans requested in wsjt_fft_compat\n");
      abort ();
    }

  complex_count = (*iform == 0) ? (*nfft / 2) : *nfft;
  scratch_bytes = (size_t) complex_count * sizeof (fftwf_complex);
  if (complex_count > 0 && complex_count <= FFT_SCRATCH_LIMIT)
    {
      memcpy (scratch, data, scratch_bytes);
    }

  g_fft_plan_slots[g_fft_plan_count].plan = create_plan (data, *nfft, *isign, *iform);
  g_fft_plan_slots[g_fft_plan_count].nfft = *nfft;
  g_fft_plan_slots[g_fft_plan_count].isign = *isign;
  g_fft_plan_slots[g_fft_plan_count].iform = *iform;
  g_fft_plan_slots[g_fft_plan_count].address = (uintptr_t) data;

  if (complex_count > 0 && complex_count <= FFT_SCRATCH_LIMIT)
    {
      memcpy (data, scratch, scratch_bytes);
    }

  fftwf_execute (g_fft_plan_slots[g_fft_plan_count].plan);
  ++g_fft_plan_count;
}
