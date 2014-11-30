/*******************************************************************************
****                            I N C L U D E S
*******************************************************************************/
#include <std.h>
#include <log.h>
#include <tsk.h>
#include <c55.h>

#include "tskcfg.h"

#include "stdint.h"
#include "usbstk5515.h"

#include "i2s.h"
#include "aic3204.h"
#include "dma.h"

/*******************************************************************************
****                         D E F I N I T I O N S
*******************************************************************************/


/*******************************************************************************
****                   S T A T I C   V A R I A B L E S
*******************************************************************************/
static const int16_t LUT[512] =
{
         0,    402,    804,   1206,   1608,   2009,   2411,   2811,   3212,   3612,   4011,   4410,   4808,   5205,   5602,   5998,
      6393,   6787,   7180,   7571,   7962,   8351,   8740,   9127,   9512,   9896,  10279,  10660,  11039,  11417,  11793,  12167,
     12540,  12910,  13279,  13646,  14010,  14373,  14733,  15091,  15447,  15800,  16151,  16500,  16846,  17190,  17531,  17869,
     18205,  18538,  18868,  19195,  19520,  19841,  20160,  20475,  20788,  21097,  21403,  21706,  22006,  22302,  22595,  22884,
     23170,  23453,  23732,  24008,  24279,  24548,  24812,  25073,  25330,  25583,  25833,  26078,  26320,  26557,  26791,  27020,
     27246,  27467,  27684,  27897,  28106,  28311,  28511,  28707,  28899,  29086,  29269,  29448,  29622,  29792,  29957,  30118,
     30274,  30425,  30572,  30715,  30853,  30986,  31114,  31238,  31357,  31471,  31581,  31686,  31786,  31881,  31972,  32058,
     32138,  32214,  32286,  32352,  32413,  32470,  32522,  32568,  32610,  32647,  32679,  32706,  32729,  32746,  32758,  32766,
     32767,  32766,  32758,  32746,  32729,  32706,  32679,  32647,  32610,  32568,  32522,  32470,  32413,  32352,  32286,  32214,
     32138,  32058,  31972,  31881,  31786,  31686,  31581,  31471,  31357,  31238,  31114,  30986,  30853,  30715,  30572,  30425,
     30274,  30118,  29957,  29792,  29622,  29448,  29269,  29086,  28899,  28707,  28511,  28311,  28106,  27897,  27684,  27467,
     27246,  27020,  26791,  26557,  26320,  26078,  25833,  25583,  25330,  25073,  24812,  24548,  24279,  24008,  23732,  23453,
     23170,  22884,  22595,  22302,  22006,  21706,  21403,  21097,  20788,  20475,  20160,  19841,  19520,  19195,  18868,  18538,
     18205,  17869,  17531,  17190,  16846,  16500,  16151,  15800,  15447,  15091,  14733,  14373,  14010,  13646,  13279,  12910,
     12540,  12167,  11793,  11417,  11039,  10660,  10279,   9896,   9512,   9127,   8740,   8351,   7962,   7571,   7180,   6787,
      6393,   5998,   5602,   5205,   4808,   4410,   4011,   3612,   3212,   2811,   2411,   2009,   1608,   1206,    804,    402,
         0,   -402,   -804,  -1206,  -1608,  -2009,  -2411,  -2811,  -3212,  -3612,  -4011,  -4410,  -4808,  -5205,  -5602,  -5998,
     -6393,  -6787,  -7180,  -7571,  -7962,  -8351,  -8740,  -9127,  -9512,  -9896, -10279, -10660, -11039, -11417, -11793, -12167,
    -12540, -12910, -13279, -13646, -14010, -14373, -14733, -15091, -15447, -15800, -16151, -16500, -16846, -17190, -17531, -17869,
    -18205, -18538, -18868, -19195, -19520, -19841, -20160, -20475, -20788, -21097, -21403, -21706, -22006, -22302, -22595, -22884,
    -23170, -23453, -23732, -24008, -24279, -24548, -24812, -25073, -25330, -25583, -25833, -26078, -26320, -26557, -26791, -27020,
    -27246, -27467, -27684, -27897, -28106, -28311, -28511, -28707, -28899, -29086, -29269, -29448, -29622, -29792, -29957, -30118,
    -30274, -30425, -30572, -30715, -30853, -30986, -31114, -31238, -31357, -31471, -31581, -31686, -31786, -31881, -31972, -32058,
    -32138, -32214, -32286, -32352, -32413, -32470, -32522, -32568, -32610, -32647, -32679, -32706, -32729, -32746, -32758, -32766,
    -32768, -32766, -32758, -32746, -32729, -32706, -32679, -32647, -32610, -32568, -32522, -32470, -32413, -32352, -32286, -32214,
    -32138, -32058, -31972, -31881, -31786, -31686, -31581, -31471, -31357, -31238, -31114, -30986, -30853, -30715, -30572, -30425,
    -30274, -30118, -29957, -29792, -29622, -29448, -29269, -29086, -28899, -28707, -28511, -28311, -28106, -27897, -27684, -27467,
    -27246, -27020, -26791, -26557, -26320, -26078, -25833, -25583, -25330, -25073, -24812, -24548, -24279, -24008, -23732, -23453,
    -23170, -22884, -22595, -22302, -22006, -21706, -21403, -21097, -20788, -20475, -20160, -19841, -19520, -19195, -18868, -18538,
    -18205, -17869, -17531, -17190, -16846, -16500, -16151, -15800, -15447, -15091, -14733, -14373, -14010, -13646, -13279, -12910,
    -12540, -12167, -11793, -11417, -11039, -10660, -10279,  -9896,  -9512,  -9127,  -8740,  -8351,  -7962,  -7571,  -7180,  -6787,
     -6393,  -5998,  -5602,  -5205,  -4808,  -4410,  -4011,  -3612,  -3212,  -2811,  -2411,  -2009,  -1608,  -1206,   -804,   -402,
};

/*******************************************************************************
****                    G L O B A L   V A R I A B L E S
*******************************************************************************/
uint32_t m_phaseAccumulator;
uint32_t m_delta;
uint40_t m_toneFreqInHz;
uint40_t m_sampleFreqInHz;
uint32_t m_index;

/*******************************************************************************
****          F U N C T I O N   I M P L E M E N T A T I O N
*******************************************************************************/

Void InitializeNco(void)
{
    /*
     * Init NCO global variables
     */
    m_toneFreqInHz = 1000;
    m_sampleFreqInHz = 48000;
    m_phaseAccumulator = 0;
    m_index = 0;

    // 2^M * ft/fs
    m_delta = (uint32_t)((((uint40_t)0x100000000) / m_sampleFreqInHz) * m_toneFreqInHz);
}

/****************************************************************************/
void FillTxPingBuffer(int32_t* buffer)
{
    /*
     * SWI called by DMA HWI indicating the ping buffer has emptied.  We
     * Can now copy new samples into the ping buffer
     */
    int i;
    int32_t sample;

    for (i = 0; i < DMA_PING_PONG_BUFFER_LENGTH; i++)
    {
        sample = LUT[m_index];
        buffer[i] = sample << 16;

        // increment phase accumulator and update m_index for next sample
        m_phaseAccumulator = m_phaseAccumulator + m_delta;
        m_index = (m_phaseAccumulator >> 23) & 0x1FF;
    }
}

/****************************************************************************/
void FillTxPongBuffer(int32_t* buffer)
{
    /*
     * SWI called by DMA HWI indicating the pong buffer has emptied.  We
     * Can now copy new samples into the pong buffer
     */
    int i;
    int32_t sample;

    for (i = 0; i < DMA_PING_PONG_BUFFER_LENGTH; i++)
    {
        sample = LUT[m_index];
        buffer[i] = sample << 16;

        // increment phase accumulator and update m_index for next sample
        m_phaseAccumulator = m_phaseAccumulator + m_delta;
        m_index = (m_phaseAccumulator >> 23) & 0x1FF;
    }
}
