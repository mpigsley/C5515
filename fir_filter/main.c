#include <usbstk5515.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "data.h"
#include "fir_filter.h"

int16_t delay_line[NUM_FILT_TAPS-1];
int16_t curr_input_block[BLOCK_SIZE];
int16_t output[SIG_LENGTH+NUM_FILT_TAPS-1];
int16_t curr_out_block[BLOCK_SIZE];

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  main( )                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void main( void ) {
    USBSTK5515_init( ); // Initialize Target

    register int i, j;

    // Initialize delay_line
    memset(delay_line, 0, NUM_FILT_TAPS-1);
    memset(output, 0, SIG_LENGTH+NUM_FILT_TAPS-1);

    // Loop through total blocks
    for (i = 0; i < SIG_LENGTH/BLOCK_SIZE; i++) {
    	// Setup input block
    	for (j = 0; j < BLOCK_SIZE; j++)
    		curr_input_block[j] = sig[i*BLOCK_SIZE + j];

    	// Call FIR filter
    	fir(curr_input_block, taps, curr_out_block, delay_line, BLOCK_SIZE, NUM_FILT_TAPS);

    	// Add current output block to output
    	for (j = 0; j < BLOCK_SIZE; j++)
    		output[i*BLOCK_SIZE + j] = curr_out_block[j];
    }

}
