#include <std.h>
#include <log.h>
#include <tsk.h>
#include <sem.h>

#include <string.h>
#include <tskcfg.h>
#include <stdlib.h>
#include <stdio.h>
#include "dsplib.h"

#include "usbstk5515.h"
#include "audio.h"
#include "dma.h"

int16_t isReceivePong = 0, isTransmitPong = 0;
int16_t fft_buffer[FFT_SIZE];
int16_t dft_bins[NUM_BINS];
int16_t buff_index = 0;

void InitializeAudio() {
	memset(fft_buffer, 0, (FFT_SIZE) * sizeof(fft_buffer[0]));
	memset(dft_bins, 0, (NUM_BINS) * sizeof(dft_bins[0]));
}

int16_t abs(int16_t a) {
	if (a < 0) return -a;
	else return a;
}

int16_t alpha_beta_mag(int16_t re, int16_t im) {
	float alpha = 1, beta = 0.25;
	re = abs(re);
	im = abs(im);
	if (re > im)
		return (int16_t) (alpha * re + beta * im);
	else
		return (int16_t) (alpha * re + beta * im);
}

void PerformFFTTsk() {
	while(1) {
		SEM_pend(&SEM_FFTProcessor, SYS_FOREVER);
		rfft((DATA *) fft_buffer, FFT_SIZE, SCALE);

		register int i;
		for (i = 0; i < NUM_BINS; i++) {
			int16_t re = fft_buffer[i*2];
			int16_t im = fft_buffer[i*2+1];
			dft_bins[i] = alpha_beta_mag(re, im);
		}

		SEM_post(&SEM_StartUI);
	}
}

void AudioTransmitTsk(void) {
	while(1) {
		// Block until HWI Signal
		SEM_pend(&SEM_OutputAudio, SYS_FOREVER);

		// Send Input to Output - Passthrough
		register int i;
		for (i = 0; i < DMA_PING_PONG_BUFFER_LENGTH; i++)
			g_dmaOutputBuffer[i + (isTransmitPong * DMA_PING_PONG_BUFFER_LENGTH)] = g_dmaInputBuffer[i + (isReceivePong * DMA_PING_PONG_BUFFER_LENGTH)];
	}
}

void AudioProcessingTsk(void) {
	while(1) {
		// Block until HWI Signal
		SEM_pend(&SEM_AudioProcessor, SYS_FOREVER);

		// Take input and store into buffer
		register int i;
		for (i = 0; i < DMA_PING_PONG_BUFFER_LENGTH; i++) {
			if ((buff_index * DMA_PING_PONG_BUFFER_LENGTH) + i < FFT_SIZE)
				fft_buffer[(buff_index * DMA_PING_PONG_BUFFER_LENGTH) + i] = (int16_t) (g_dmaInputBuffer[i + (isReceivePong * DMA_PING_PONG_BUFFER_LENGTH)] >> 16);
			else {
				SEM_post(&SEM_FFTProcessor);
				break;
			}
		}

		buff_index++;
		if (buff_index * DMA_PING_PONG_BUFFER_LENGTH > FFT_SIZE)
			buff_index = 0;
	}
}
