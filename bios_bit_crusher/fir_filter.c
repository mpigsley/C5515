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

int16_t hpDelayLine[NUM_FILT_TAPS + 2];
int16_t intDelayLine[NUM_INT_TAPS + 2];
int16_t output[DMA_PING_PONG_BUFFER_LENGTH];
#pragma DATA_ALIGN(output, 2);
const int16_t hp_taps[] = {
			54,   -212,    -62,    -27,    -20,    -18,    -18,    -18,    -18,    -19,    -19,    -19,    -19,    -19,    -19,    -19,
		   -19,    -18,    -18,    -18,    -17,    -16,    -16,    -15,    -14,    -13,    -12,    -11,    -10,     -8,     -7,     -6,
			-4,     -2,     -1,      1,      3,      5,      7,      9,     11,     13,     15,     18,     20,     22,     25,     27,
			30,     32,     35,     37,     39,     42,     44,     47,     49,     51,     54,     56,     58,     60,     62,     64,
			66,     67,     69,     70,     71,     72,     73,     74,     75,     75,     75,     75,     75,     75,     74,     73,
			72,     71,     70,     68,     66,     63,     61,     58,     55,     52,     48,     44,     40,     35,     31,     26,
			20,     15,      9,      3,     -4,    -10,    -17,    -24,    -32,    -39,    -47,    -55,    -64,    -72,    -81,    -90,
		   -99,   -109,   -118,   -128,   -137,   -147,   -157,   -167,   -178,   -188,   -198,   -209,   -219,   -230,   -240,   -251,
		  -261,   -271,   -282,   -292,   -302,   -312,   -322,   -332,   -342,   -351,   -360,   -369,   -378,   -387,   -396,   -404,
		  -412,   -419,   -427,   -434,   -441,   -447,   -453,   -459,   -464,   -469,   -474,   -478,   -482,   -486,   -489,   -491,
		  -494,   -496,   -497,   -498,   -499,  32268,   -499,   -498,   -497,   -496,   -494,   -491,   -489,   -486,   -482,   -478,
		  -474,   -469,   -464,   -459,   -453,   -447,   -441,   -434,   -427,   -419,   -412,   -404,   -396,   -387,   -378,   -369,
		  -360,   -351,   -342,   -332,   -322,   -312,   -302,   -292,   -282,   -271,   -261,   -251,   -240,   -230,   -219,   -209,
		  -198,   -188,   -178,   -167,   -157,   -147,   -137,   -128,   -118,   -109,    -99,    -90,    -81,    -72,    -64,    -55,
		   -47,    -39,    -32,    -24,    -17,    -10,     -4,      3,      9,     15,     20,     26,     31,     35,     40,     44,
			48,     52,     55,     58,     61,     63,     66,     68,     70,     71,     72,     73,     74,     75,     75,     75,
			75,     75,     75,     74,     73,     72,     71,     70,     69,     67,     66,     64,     62,     60,     58,     56,
			54,     51,     49,     47,     44,     42,     39,     37,     35,     32,     30,     27,     25,     22,     20,     18,
			15,     13,     11,      9,      7,      5,      3,      1,     -1,     -2,     -4,     -6,     -7,     -8,    -10,    -11,
		   -12,    -13,    -14,    -15,    -16,    -16,    -17,    -18,    -18,    -18,    -19,    -19,    -19,    -19,    -19,    -19,
		   -19,    -19,    -18,    -18,    -18,    -18,    -20,    -27,    -62,   -212,     54
};
const int16_t int_taps[] = {
	 -1317,  -2414,  -3039,  -2964,  -1997,      0,   6030,  12634,  19208,  25134,  29827,  32767,  29827,  25134,  19208,  12634,
	  6030,      0,  -1997,  -2964,  -3039,  -2414,  -1317
};

void InitializeFIR(void) {
	// Initialize Arrays
	memset(hpDelayLine, 0, (NUM_FILT_TAPS + 2) * sizeof(hpDelayLine[0]));
	memset(intDelayLine, 0, (NUM_INT_TAPS + 2) * sizeof(intDelayLine[0]));
	memset(output, 0, DMA_PING_PONG_BUFFER_LENGTH * sizeof(output[0]));
}

int16_t* filter(int16_t* buffer, int16_t type) {
	if (!type) {
		// High Pass
		fir2((DATA *) buffer,
					(DATA *) hp_taps,
					(DATA *) output,
					(DATA *) hpDelayLine,
					DMA_PING_PONG_BUFFER_LENGTH,
					NUM_FILT_TAPS);
	} else {
		// Interpolate
		fir2((DATA *) buffer,
				(DATA *) int_taps,
					(DATA *) output,
					(DATA *) intDelayLine,
					DMA_PING_PONG_BUFFER_LENGTH,
					NUM_INT_TAPS);
	}
	return output;
}

int16_t* filterBuffer(int16_t* buffer) {
	return filter(buffer, 0);
}

int16_t* interpolateBuffer(int16_t* buffer) {
	return filter(buffer, 1);
}
