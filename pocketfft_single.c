/*
 * This file is part of pocketfft.
 * Licensed under a 3-clause BSD style license - see LICENSE.md
 */

#include "pocketfft_single.h"

#define floatT  float
#define fmaT    fmaf

#define cfft_plan_i        cffts_plan_i
#define cfft_plan          cffts_plan
#define make_cfft_plan     make_cffts_plan
#define destroy_cfft_plan  destroy_cffts_plan
#define cfft_backward      cffts_backward
#define cfft_forward       cffts_forward
#define cfft_length        cffts_length

#define rfft_plan_i        rffts_plan_i
#define rfft_plan          rffts_plan
#define make_rfft_plan     make_rffts_plan
#define destroy_rfft_plan  destroy_rffts_plan
#define rfft_backward      rffts_backward
#define rfft_forward       rffts_forward
#define rfft_length        rffts_length

#include "pocketfft.c"

