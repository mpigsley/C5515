#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "fir_filter.h"

void fir( 	int16_t*		curr_input_block,
			const int16_t*	filter_coeffs,
			int16_t*		curr_output_block,
			int16_t*		delay_line,
			uint16_t		num_input_samples,
			uint16_t		num_filt_taps	) {

	// Init all output samples to 0
    memset(curr_output_block, 0, num_input_samples);

    // Init counter variables
	register int16_t i, j;

	// Compute the Output
	for (i = 0; i < num_input_samples; i++) {
		int16_t counter = i;
		for (j = 0; j < num_filt_taps; j++) {
			if (counter >= 0) {
				int32_t temp = (uint32_t) filter_coeffs[j] * (uint32_t)curr_input_block[counter];
				curr_output_block[i] += temp >> 15;
			} else {
				int32_t temp = (uint32_t) filter_coeffs[j] * (uint32_t)delay_line[num_filt_taps -1 + counter];
				curr_output_block[i] += temp >> 15;
			}

			counter = counter - 1;
		}
	}

	// Set the next delay_line
	for (i = 0; i < num_input_samples; i++) {
		// Move current delay line samples down
		if (num_filt_taps - num_input_samples - i >= 0)
			delay_line[num_filt_taps - num_input_samples - i] = delay_line[num_filt_taps - 1 - i];
		// Current input is put into delay line
		delay_line[num_filt_taps - 1 - i] = curr_input_block[num_input_samples - i];
	}
}
