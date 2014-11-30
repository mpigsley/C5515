/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  AIC3204 NCO Tone                                                        *
 *      Define a frequency and this will play a sin wave at that            *
 *      specified frequency.                                                *
 *                                                                          *
 * ------------------------------------------------------------------------ */

#include "stdio.h"
#include "stdint.h"
#include "math.h"
#include "usbstk5515.h"
extern Int16 AIC3204_rset( Uint16 regnum, Uint16 regval);
#define XmitL 0x10
#define XmitR 0x20

Int16 aic3204_tone_headphone( )
{
	/* Pre-generated sine wave data, 512 * 16-bit signed samples */
	int16_t sinetable[512] =
	{
	         0,    402,    804,   1206,   1608,   2009,   2411,   2811,
	      3212,   3612,   4011,   4410,   4808,   5205,   5602,   5998,
	      6393,   6787,   7180,   7571,   7962,   8351,   8740,   9127,
	      9512,   9896,  10279,  10660,  11039,  11417,  11793,  12167,
	     12540,  12910,  13279,  13646,  14010,  14373,  14733,  15091,
	     15447,  15800,  16151,  16500,  16846,  17190,  17531,  17869,
	     18205,  18538,  18868,  19195,  19520,  19841,  20160,  20475,
	     20788,  21097,  21403,  21706,  22006,  22302,  22595,  22884,
	     23170,  23453,  23732,  24008,  24279,  24548,  24812,  25073,
	     25330,  25583,  25833,  26078,  26320,  26557,  26791,  27020,
	     27246,  27467,  27684,  27897,  28106,  28311,  28511,  28707,
	     28899,  29086,  29269,  29448,  29622,  29792,  29957,  30118,
	     30274,  30425,  30572,  30715,  30853,  30986,  31114,  31238,
	     31357,  31471,  31581,  31686,  31786,  31881,  31972,  32058,
	     32138,  32214,  32286,  32352,  32413,  32470,  32522,  32568,
	     32610,  32647,  32679,  32706,  32729,  32746,  32758,  32766,
	     32767,  32766,  32758,  32746,  32729,  32706,  32679,  32647,
	     32610,  32568,  32522,  32470,  32413,  32352,  32286,  32214,
	     32138,  32058,  31972,  31881,  31786,  31686,  31581,  31471,
	     31357,  31238,  31114,  30986,  30853,  30715,  30572,  30425,
	     30274,  30118,  29957,  29792,  29622,  29448,  29269,  29086,
	     28899,  28707,  28511,  28311,  28106,  27897,  27684,  27467,
	     27246,  27020,  26791,  26557,  26320,  26078,  25833,  25583,
	     25330,  25073,  24812,  24548,  24279,  24008,  23732,  23453,
	     23170,  22884,  22595,  22302,  22006,  21706,  21403,  21097,
	     20788,  20475,  20160,  19841,  19520,  19195,  18868,  18538,
	     18205,  17869,  17531,  17190,  16846,  16500,  16151,  15800,
	     15447,  15091,  14733,  14373,  14010,  13646,  13279,  12910,
	     12540,  12167,  11793,  11417,  11039,  10660,  10279,   9896,
	      9512,   9127,   8740,   8351,   7962,   7571,   7180,   6787,
	      6393,   5998,   5602,   5205,   4808,   4410,   4011,   3612,
	      3212,   2811,   2411,   2009,   1608,   1206,    804,    402,
	         0,   -402,   -804,  -1206,  -1608,  -2009,  -2411,  -2811,
	     -3212,  -3612,  -4011,  -4410,  -4808,  -5205,  -5602,  -5998,
	     -6393,  -6787,  -7180,  -7571,  -7962,  -8351,  -8740,  -9127,
	     -9512,  -9896, -10279, -10660, -11039, -11417, -11793, -12167,
	    -12540, -12910, -13279, -13646, -14010, -14373, -14733, -15091,
	    -15447, -15800, -16151, -16500, -16846, -17190, -17531, -17869,
	    -18205, -18538, -18868, -19195, -19520, -19841, -20160, -20475,
	    -20788, -21097, -21403, -21706, -22006, -22302, -22595, -22884,
	    -23170, -23453, -23732, -24008, -24279, -24548, -24812, -25073,
	    -25330, -25583, -25833, -26078, -26320, -26557, -26791, -27020,
	    -27246, -27467, -27684, -27897, -28106, -28311, -28511, -28707,
	    -28899, -29086, -29269, -29448, -29622, -29792, -29957, -30118,
	    -30274, -30425, -30572, -30715, -30853, -30986, -31114, -31238,
	    -31357, -31471, -31581, -31686, -31786, -31881, -31972, -32058,
	    -32138, -32214, -32286, -32352, -32413, -32470, -32522, -32568,
	    -32610, -32647, -32679, -32706, -32729, -32746, -32758, -32766,
	    -32768, -32766, -32758, -32746, -32729, -32706, -32679, -32647,
	    -32610, -32568, -32522, -32470, -32413, -32352, -32286, -32214,
	    -32138, -32058, -31972, -31881, -31786, -31686, -31581, -31471,
	    -31357, -31238, -31114, -30986, -30853, -30715, -30572, -30425,
	    -30274, -30118, -29957, -29792, -29622, -29448, -29269, -29086,
	    -28899, -28707, -28511, -28311, -28106, -27897, -27684, -27467,
	    -27246, -27020, -26791, -26557, -26320, -26078, -25833, -25583,
	    -25330, -25073, -24812, -24548, -24279, -24008, -23732, -23453,
	    -23170, -22884, -22595, -22302, -22006, -21706, -21403, -21097,
	    -20788, -20475, -20160, -19841, -19520, -19195, -18868, -18538,
	    -18205, -17869, -17531, -17190, -16846, -16500, -16151, -15800,
	    -15447, -15091, -14733, -14373, -14010, -13646, -13279, -12910,
	    -12540, -12167, -11793, -11417, -11039, -10660, -10279,  -9896,
	     -9512,  -9127,  -8740,  -8351,  -7962,  -7571,  -7180,  -6787,
	     -6393,  -5998,  -5602,  -5205,  -4808,  -4410,  -4011,  -3612,
	     -3212,  -2811,  -2411,  -2009,  -1608,  -1206,   -804,   -402,
	};

    uint16_t index = 0;
    uint32_t delta, pa = 0;
    uint16_t Ftone = 50, Fs = 48000; // Hz

    delta = (pow(2.0,32) * Ftone)/Fs;

    /* Configure AIC3204 */
    AIC3204_rset( 0, 0 );      // Select page 0
    AIC3204_rset( 1, 1 );      // Reset codec
    AIC3204_rset( 0, 1 );      // Select page 1
    AIC3204_rset( 1, 8 );      // Disable crude AVDD generation from DVDD
    AIC3204_rset( 2, 1 );      // Enable Analog Blocks, use LDO power
    AIC3204_rset( 0, 0 );
    /* PLL and Clocks config and Power Up  */
    AIC3204_rset( 27, 0x0d );  // BCLK and WCLK are set as o/p; AIC3204(Master)
    AIC3204_rset( 28, 0x00 );  // Data ofset = 0
    AIC3204_rset( 4, 3 );      // PLL setting: PLLCLK <- MCLK, CODEC_CLKIN <-PLL CLK
    AIC3204_rset( 6, 7 );      // PLL setting: J=7
    AIC3204_rset( 7, 0x06 );   // PLL setting: HI_BYTE(D=1680)
    AIC3204_rset( 8, 0x90 );   // PLL setting: LO_BYTE(D=1680)
    AIC3204_rset( 30, 0x88 );  // For 32 bit clocks per frame in Master mode ONLY
                               // BCLK=DAC_CLK/N =(12288000/8) = 1.536MHz = 32*fs
    AIC3204_rset( 5, 0x91 );   // PLL setting: Power up PLL, P=1 and R=1
    AIC3204_rset( 13, 0 );     // Hi_Byte(DOSR) for DOSR = 128 decimal or 0x0080 DAC oversamppling
    AIC3204_rset( 14, 0x80 );  // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
    AIC3204_rset( 20, 0x80 );  // AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6
    AIC3204_rset( 11, 0x82 );  // Power up NDAC and set NDAC value to 2
    AIC3204_rset( 12, 0x87 );  // Power up MDAC and set MDAC value to 7
    AIC3204_rset( 18, 0x87 );  // Power up NADC and set NADC value to 7
    AIC3204_rset( 19, 0x82 );  // Power up MADC and set MADC value to 2
    /* DAC ROUTING and Power Up */
    AIC3204_rset( 0, 1 );      // Select page 1
    AIC3204_rset( 0x0c, 8 );   // LDAC AFIR routed to HPL
    AIC3204_rset( 0x0d, 8 );   // RDAC AFIR routed to HPR
    AIC3204_rset( 0, 0 );      // Select page 0
    AIC3204_rset( 64, 2 );     // Left vol=right vol
    AIC3204_rset( 65, 0);      // Left DAC gain to 0dB VOL; Right tracks Left
    AIC3204_rset( 63, 0xd4 );  // Power up left,right data paths and set channel
    AIC3204_rset( 0, 1 );      // Select page 1
    AIC3204_rset( 0x10, 0x00 );// Unmute HPL , 0dB gain
    AIC3204_rset( 0x11, 0x00 );// Unmute HPR , 0dB gain
    AIC3204_rset( 9, 0x30 );   // Power up HPL,HPR
    AIC3204_rset( 0, 0 );      // Select page 0
    USBSTK5515_wait( 100 );    // wait
    /* ADC ROUTING and Power Up */
    AIC3204_rset( 0, 1 );      // Select page 1
    AIC3204_rset( 0x34, 0x30 );// STEREO 1 Jack
		                       // IN2_L to LADC_P through 40 kohm
    AIC3204_rset( 0x37, 0x30 );// IN2_R to RADC_P through 40 kohmm
    AIC3204_rset( 0x36, 3 );   // CM_1 (common mode) to LADC_M through 40 kohm
    AIC3204_rset( 0x39, 0xc0 );// CM_1 (common mode) to RADC_M through 40 kohm
    AIC3204_rset( 0x3b, 0 );   // MIC_PGA_L unmute
    AIC3204_rset( 0x3c, 0 );   // MIC_PGA_R unmute
    AIC3204_rset( 0, 0 );      // Select page 0
    AIC3204_rset( 0x51, 0xc0 );// Powerup Left and Right ADC
    AIC3204_rset( 0x52, 0 );   // Unmute Left and Right ADC
    
    AIC3204_rset( 0, 0 );    
    USBSTK5515_wait( 200 );    // Wait
    
    /* I2S settings */
    I2S0_SRGR = 0x0;
    I2S0_CR = 0x8010;    // 16-bit word, slave, enable I2C
    I2S0_ICMR = 0x3f;    // Enable interrupts
    
    /* Play Tone */
    uint32_t i, j = 0;
    uint16_t output[1000];
	for (i = 0; i < 100000; i++) {
		pa = pa + delta;						// Increment the Phase Accumulator
		index = pa >> 23; 						// Index is phase accumulator right-shifted 23 bits
		while((XmitR & I2S0_IR) == 0);        	// Wait for transmit interrupt to be pending
		I2S0_W0_MSW_W = (sinetable[index]) ; 	// 16 bit left channel transmit audio data
		I2S0_W1_MSW_W = (sinetable[index]) ; 	// 16 bit right channel transmit audio data

		if (j < 1000) {
			output[j] = sinetable[index];
			j++;
		}
	}

    /* Disble I2S */
    I2S0_CR = 0x00;
   
    return 0;
}
