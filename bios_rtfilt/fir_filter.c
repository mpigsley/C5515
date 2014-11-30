/*******************************************************************************
****                            I N C L U D E S
*******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <std.h>
#include <log.h>
#include <tsk.h>
#include <c55.h>

#include "tskcfg.h"
#include "stdint.h"
#include "usbstk5515.h"

#include "fir_filter.h"
#include "i2s.h"
#include "aic3204.h"
#include "dma.h"

int16_t delayLine[NUM_FILT_TAPS + 2];
int16_t output[DMA_PING_PONG_BUFFER_LENGTH];
#pragma DATA_ALIGN(output, 2);
const int16_t taps[] = {
       -19,     -5,     -6,     -6,     -7,     -8,     -8,     -9,    -10,    -10,    -11,    -11,    -12,    -13,    -13,    -14,
       -14,    -14,    -14,    -15,    -15,    -15,    -14,    -14,    -14,    -13,    -12,    -11,    -10,     -9,     -8,     -6,
        -5,     -3,     -1,      2,      4,      7,      9,     12,     15,     18,     22,     25,     29,     32,     36,     40,
        43,     47,     51,     55,     58,     62,     65,     69,     72,     75,     77,     80,     82,     84,     86,     87,
        88,     89,     89,     89,     88,     87,     86,     84,     81,     78,     75,     71,     66,     61,     56,     50,
        44,     37,     30,     23,     15,      7,     -2,    -10,    -19,    -28,    -37,    -46,    -56,    -65,    -74,    -82,
       -91,    -99,   -107,   -115,   -122,   -128,   -134,   -139,   -144,   -147,   -150,   -152,   -153,   -154,   -153,   -151,
      -148,   -143,   -138,   -131,   -124,   -115,   -104,    -93,    -80,    -66,    -51,    -35,    -18,      1,     21,     41,
        63,     86,    109,    134,    159,    184,    211,    238,    265,    293,    320,    348,    376,    404,    432,    460,
       487,    514,    540,    566,    591,    615,    638,    660,    681,    700,    719,    736,    752,    766,    779,    790,
       799,    807,    813,    818,    820,    821,    820,    818,    813,    807,    799,    790,    779,    766,    752,    736,
       719,    700,    681,    660,    638,    615,    591,    566,    540,    514,    487,    460,    432,    404,    376,    348,
       320,    293,    265,    238,    211,    184,    159,    134,    109,     86,     63,     41,     21,      1,    -18,    -35,
       -51,    -66,    -80,    -93,   -104,   -115,   -124,   -131,   -138,   -143,   -148,   -151,   -153,   -154,   -153,   -152,
      -150,   -147,   -144,   -139,   -134,   -128,   -122,   -115,   -107,    -99,    -91,    -82,    -74,    -65,    -56,    -46,
       -37,    -28,    -19,    -10,     -2,      7,     15,     23,     30,     37,     44,     50,     56,     61,     66,     71,
        75,     78,     81,     84,     86,     87,     88,     89,     89,     89,     88,     87,     86,     84,     82,     80,
        77,     75,     72,     69,     65,     62,     58,     55,     51,     47,     43,     40,     36,     32,     29,     25,
        22,     18,     15,     12,      9,      7,      4,      2,     -1,     -3,     -5,     -6,     -8,     -9,    -10,    -11,
       -12,    -13,    -14,    -14,    -14,    -15,    -15,    -15,    -14,    -14,    -14,    -14,    -13,    -13,    -12,    -11,
       -11,    -10,    -10,     -9,     -8,     -8,     -7,     -6,     -6,     -5,    -19
};

void InitializeFIR(void) {
	// Initialize Arrays
	memset(delayLine, 0, (NUM_FILT_TAPS + 2) * sizeof(delayLine[0]));
	memset(output, 0, DMA_PING_PONG_BUFFER_LENGTH * sizeof(output[0]));
}

int16_t* filterBuffer(int16_t* buffer) {
	// Filter
	fir2((DATA *) buffer,
			(DATA *) taps,
			(DATA *) output,
			(DATA *) delayLine,
			DMA_PING_PONG_BUFFER_LENGTH,
			NUM_FILT_TAPS);

	// Set the filteredSig as output
	return output;
}