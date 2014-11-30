/*
 * fir_filter.c
 *
 *  Created on: Feb 18, 2014
 *      Author: mpigsley
 */

#include "stdio.h"
#include "stdint.h"
#include "fir_filter.h"

void fir( 	int16_t*		input,
			const int16_t*	filter_coeffs,
			int16_t*		output,
			int16_t*		delay_line,
			uint16_t		num_input_samples,
			uint16_t		num_filt_taps	) {

	printf("in fir\n");

}
