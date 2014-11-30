/*
 * Example DSP BIOS project created for ELEC 498
 */
#include <std.h>
#include <c55.h>

#include "tskcfg.h"
#include "userInterface.h"
#include "audio.h"
#include "i2s.h"
#include "aic3204.h"
#include "dma.h"

/*
 *  ======== main ========
 */
void main() {
    /*
     * Entry point.  After exit DSP BIOS scheduler starts
     */
    InitializeUI();
    InitializeAudio();

    /*
     * Configure the DMA0 channel 0 for I2S0 tx processing
     */
    DmaInitialize();
    StartDma();

    /*
     * Configure the AIC3204 CODEC chip
     */
    ConfigureAic3204();

    /*
     * Configure I2S0 port for transmit
     */
    EnableI2sPort();
}
