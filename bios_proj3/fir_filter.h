/*
 * fir_filter.h
 *
 *  Created on: Mar 3, 2014
 *      Author: mpigs_000
 */

#ifndef FIR_FILTER_H_
#define FIR_FILTER_H_

#include "stdint.h"

typedef int16_t DATA;

extern void InitializeFIR(void);
extern int16_t* filterBuffer(int16_t* buffer);
extern int16_t* interpolateBuffer(int16_t* buffer);
extern int fir2(DATA *x, const DATA *h, DATA *r, DATA *dbuffer, int nx, int nh);

#define NUM_FILT_TAPS 331
#define NUM_INT_TAPS 23

#endif /* FIR_FILTER_H_ */
