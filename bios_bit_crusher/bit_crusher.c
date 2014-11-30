#include <std.h>
#include <log.h>
#include <tsk.h>
#include <math.h>

#include "tskcfg.h"
#include "usbstk5515.h"

#include "fir_filter.h"
#include "bit_crusher.h"
#include "dma.h"

int16_t isReceivePong = 0, isTransmitPong = 0, resolution = 15, downsampling = 0;
uint32_t interpolateIndex = 0;
int16_t filteredSigBuff[DMA_PING_PONG_BUFFER_LENGTH];

void AudioTransmitTsk(void) {
	while(1) {
		// Block until HWI Signal
		SEM_pend(&SEM_OutputAudio, SYS_FOREVER);

		// Send Signal to DAC (Write to Output Buffer)
		register int i;
		for (i = 0; i < DMA_PING_PONG_BUFFER_LENGTH; i++)
			g_dmaOutputBuffer[i + (isTransmitPong * DMA_PING_PONG_BUFFER_LENGTH)] = ((int32_t) filteredSigBuff[i]) << 16;
	}
}

void AudioProcessingTsk(void) {
	while(1) {
		// Block until HWI Signal
		SEM_pend(&SEM_AudioProcessor, SYS_FOREVER);

		register int i;
		int16_t tempBuffer[DMA_PING_PONG_BUFFER_LENGTH];

		// Downsample
		for (i = 0; i < DMA_PING_PONG_BUFFER_LENGTH; i++)
			tempBuffer[i] = (int16_t) (g_dmaInputBuffer[i + (isReceivePong * DMA_PING_PONG_BUFFER_LENGTH)] >> 16);

		// Resolution Correction
		for (i = 0; i < DMA_PING_PONG_BUFFER_LENGTH; i++) {
			if (Q_NUM_FORMAT != resolution) {
				int16_t comp = (tempBuffer[i] >> (Q_NUM_FORMAT - resolution - 1)) & 1;
				if (comp)
					tempBuffer[i] += (uint16_t) pow(2, Q_NUM_FORMAT-resolution);
				tempBuffer[i] &= ~(uint16_t) (pow(2, Q_NUM_FORMAT-resolution) - 1);
			}
		}

		// Copy into filtered signal buffer
		memcpy(&filteredSigBuff[0],
				&tempBuffer[0],
				DMA_PING_PONG_BUFFER_LENGTH * sizeof(filteredSigBuff[0]));

	}
}
