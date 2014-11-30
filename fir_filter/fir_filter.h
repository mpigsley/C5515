/*
 * fir_filter.h
 *
 *  Created on: Feb 18, 2014
 *      Author: mpigsley
 */

#ifndef FIR_FILTER_H_
#define FIR_FILTER_H_

void fir( 	int16_t*		curr_input_block,
			const int16_t*	filter_coeffs,
			int16_t*		curr_output_block,
			int16_t*		delay_line,
			uint16_t		num_input_samples,
			uint16_t		num_filt_taps	);

#endif /* FIR_FILTER_H_ */
