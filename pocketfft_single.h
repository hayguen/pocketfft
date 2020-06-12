/*
 * This file is part of pocketfft.
 * Licensed under a 3-clause BSD style license - see LICENSE.md
 */

/*! \file pocketfft.h
 *  Public interface of the pocketfft library
 *
 *  Copyright (C) 2008-2018 Max-Planck-Society
 *  \author Martin Reinecke
 */

#ifndef POCKETFFT_SINGLE_H
#define POCKETFFT_SINGLE_H

#include <stdlib.h>

struct cffts_plan_i;
typedef struct cffts_plan_i * cffts_plan;
cffts_plan make_cffts_plan (size_t length);
void destroy_cffts_plan (cffts_plan plan);
int cffts_backward(cffts_plan plan, float c[], float fct);
int cffts_forward(cffts_plan plan, float c[], float fct);
size_t cffts_length(cffts_plan plan);

struct rffts_plan_i;
typedef struct rffts_plan_i * rffts_plan;
rffts_plan make_rffts_plan (size_t length);
void destroy_rffts_plan (rffts_plan plan);
int rffts_backward(rffts_plan plan, float c[], float fct);
int rffts_forward(rffts_plan plan, float c[], float fct);
size_t rffts_length(rffts_plan plan);

#endif
