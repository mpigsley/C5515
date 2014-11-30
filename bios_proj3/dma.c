/*******************************************************************************
****                            I N C L U D E S
*******************************************************************************/
#include "tskcfg.h"
#include <std.h>
#include <c55.h>
#include "string.h"
#include "myDefs.h"
#include "usbstk5515.h"
#include "fir_filter.h"
#include "dma.h"
#include "audio.h"

/*******************************************************************************
****                         D E F I N I T I O N S
*******************************************************************************/

#define I2S_TX_LEFT_CHANNEL_ADDRESS (0x2808)
#define I2S_TX_RIGHT_CHANNEL_ADDRESS (0x280C)

#define I2S_RX_LEFT_CHANNEL_ADDRESS (0x2828)
#define I2S_RX_RIGHT_CHANNEL_ADDRESS (0x282C)

/* DMA System Registers */
#define DMAIFR       *(volatile ioport uint16_t*)(0x1C30)
#define DMAIER       *(volatile ioport Uint16*)(0x1C31)
#define DMA0CESR1    *(volatile ioport Uint16*)(0x1C1A)
#define DMA0CESR2    *(volatile ioport Uint16*)(0x1C1B)

/* DMA Controller 0 (DMA0) Registers */
#define DMACH0SSAL   *(volatile ioport Uint16*)(0x0C00)
#define DMACH0SSAU   *(volatile ioport Uint16*)(0x0C01)
#define DMACH0DSAL   *(volatile ioport Uint16*)(0x0C02)
#define DMACH0DSAU   *(volatile ioport Uint16*)(0x0C03)
#define DMACH0TCR1   *(volatile ioport Uint16*)(0x0C04)
#define DMACH0TCR2   *(volatile ioport Uint16*)(0x0C05)

/* DMA Controller 0 (DMA1) Registers */
#define DMACH1SSAL   *(volatile ioport Uint16*)(0x0C20)
#define DMACH1SSAU   *(volatile ioport Uint16*)(0x0C21)
#define DMACH1DSAL   *(volatile ioport Uint16*)(0x0C22)
#define DMACH1DSAU   *(volatile ioport Uint16*)(0x0C23)
#define DMACH1TCR1   *(volatile ioport Uint16*)(0x0C24)
#define DMACH1TCR2   *(volatile ioport Uint16*)(0x0C25)

static uint32_t MemoryAddress(const void * Address);

/*******************************************************************************
****                   S T A T I C   V A R I A B L E S
*******************************************************************************/

/*******************************************************************************
****                    G L O B A L   V A R I A B L E S
*******************************************************************************/
int32_t g_dmaOutputBuffer[DMA_OUTPUT_BUFFER_LENGTH];
int32_t g_dmaInputBuffer[DMA_INPUT_BUFFER_LENGTH];

/*******************************************************************************
****          F U N C T I O N   I M P L E M E N T A T I O N
*******************************************************************************/

void DmaInitialize(void)
{
    /* To initialize the DMA controller follow these steps:
     * 1. Ensure the DMA controller is out of reset by setting the DMA_RST
     *    bit to 0 in the peripheral reset control register (PRCR). PRCR is a
     *    chip configuration register, it is not part of the DMA controller,
     *    see the device data manual for more details.
     * 2. Enable the DMA controller input clock by setting the corresponding
     *    DMAnCG bit to 0 in the peripheral clock gating configuration
     *    registers (PCGCR1 and PCGCR2). PCGCR1 and PCGCR2 are chip
     *    configuration registers, they are not part of the DMA controller,
     *    see the device data manual for more details.
     * 3. Ensure that all DMA channel interrupt flags are cleared by writing
     *    a 1 to the bits of the DMA interrupt flag register (DMAIFR). Also,
     *    ensure all DMA interrupt flags in the CPU interrupt flag registers
     *    (IFR0 and IFR1) are cleared.
     * 4. If using interrupts, enable the desired channel interrupt by
     *    setting the DMAnCHmIE bits of the interrupt enable register
     *    (DMAIER). The CPU interrupt enable bit (INTEN) in the transfer
     *    control register 2 (DMACHmTCR2) must also be set.
     * 5. If using synchronization events, select the event to be used
     *    through the CHmEVT bits of the channel event source registers
     *    (DMAnCESR1 and DMAnCESR2). The synchronization mode bit (SYNCMODE)
     *    of DMACHmTCR2 must also be set, although this should be done only
     *    when the channel is ready to be enabled.
     *
     * 6. Load the source address to the source start address registers
     *    (DMACHmSSAL and DMACHmSSAU). See Section 2.4, Start Address in a
     *    Channel, for more information on calculating the correct source
     *    start address.
     * 7. Load the destination address to the destination start address
     *    registers (DMACHmDSAL and DMACHmDSAU). See Section 2.4, Start
     *    Address in a Channel, for more information on calculating the
     *    correct destination start address.
     * 8. Load the DMA transfer control register 1 (DMACHmTCR1) with the
     *    number of double words to transfer. Note that the number of double
     *    words must be specified in bytes. For example, for a 256 double
     *    word transfer, program this field with 1024 (256 x 4 = 1024).
     * 9. Configure DMACHmTCR2 accordingly. Through this register you can
     *    specify the source and destination addressing modes and burst mode.
     *    You can also enable automatic reload, event synchronization, and
     *    CPU interrupts. Note that you must keep EN = 0 and SYNCMODE = 0
     *    during this step.
     * 10. If the DMA channel is servicing a peripheral, ensure that the
     *     corresponding peripheral is not active and hence not generating
     *     synchronization events.
     * 11. Enable the DMA channel by setting EN = 1 (and SYNCMODE = 1 if
     *     using synchronization events).
     */

    uint32_t address;
    uint16_t length;

    memset(g_dmaInputBuffer, 0, sizeof(g_dmaInputBuffer));
    memset(g_dmaOutputBuffer, 0, sizeof(g_dmaOutputBuffer));

    /* DMA controller out of reset */
    SYS_PRCNTRLR = SYS_PRCNTRLR & (~BIT4);

    /* enable DMA input clock */
    SYS_PCGCR1 = SYS_PCGCR1 & (~BIT3);

    /* ensure all DMA channel isr flags are cleared */
    DMAIFR = 0xFFFF;
    C55_clearIFR0(C55_IFG08);

    /*
     * enable desired channel interrupt:
     * - DMA controller 0 channel 0 interrupt is enabled (I2S0 transmit)
     * - DMA controller 0 channel 1 interrupt is enabled (I2S0 receive)
     * - DMA CPU interrupt enable bit is set
     */
    DMAIER = DMAIER | (BIT1 | BIT0);
    DMACH0TCR2 = DMACH0TCR2 | (BIT13);
    DMACH1TCR2 = DMACH1TCR2 | (BIT13);

    /*
     * DMA synch events
     * - select channel 0 event as I2S tx CH0EVT = 0001b
     * - select channel 1 event as I2S rx CH1EVT = 0010b
     */
    DMA0CESR1 = 0x0201;

    /*
     * Load the source address for channel 0 (tx data in memory).
     * Load the destination address for channel 0 (I2S tx reg)
     */
    address = MemoryAddress(g_dmaOutputBuffer);
    DMACH0SSAL = address;
    DMACH0SSAU = address >> 16;
    address = I2S_TX_RIGHT_CHANNEL_ADDRESS;
    DMACH0DSAL = address;
    DMACH0DSAU = address >> 16;

    /*
     * Load the source address for channel 1 (I2S rx register).
     * Load the destination address for channel 1 (rx data in memory,
     */
    address = I2S_RX_RIGHT_CHANNEL_ADDRESS;
    DMACH1SSAL = address;
    DMACH1SSAU = address >> 16;
    address = MemoryAddress(g_dmaInputBuffer);
    DMACH1DSAL = address;
    DMACH1DSAU = address >> 16;

    /*
     * Tx - Load the DMA xfer control reg with # double words to transfer.
     */
    length = sizeof(g_dmaOutputBuffer);
    DMACH0TCR1 = length * 2;

    /*
     * Rx - Load the DMA xfer control reg with # double words to transfer.
     */
    length = sizeof(g_dmaInputBuffer);
    DMACH1TCR1 = length * 2;

    /*
     * Configure the channel 0 (transmit) TCR2 register
     * - CPU interrupt enable
     * - Automatic reload
     * - Contant dest address
     * - Source Address auto post increment
     * - Enable Ping-Pong DMA transfer mode
     */
    DMACH0TCR2 = (BIT13 | BIT12 | BIT9 | BIT0);

    /*
     * Configure the channel 1 (receive) TCR2 register
     * - CPU interrupt enable
     * - Automatic reload
     * - Destination address auto post increment
     * - Source Address is constant
     * - Enable Ping-Pong DMA transfer mode
     */
    DMACH1TCR2 = (BIT13 | BIT12 | BIT7 | BIT0);

    /*
     * The peripheral must not be active before we start the DMA
     */

}

/****************************************************************************/
void StartDma(void)
{
    /*
     * Enable DMA channel 0 (I2S transmit) by setting EN = 1 and SYCNMODE = 1
     */
    DMACH0TCR2 = DMACH0TCR2 | (BIT15 | BIT2);

    /*
     * Enable DMA channel 1 (I2S receive) by setting EN = 1 and SYCNMODE = 1
     */
    DMACH1TCR2 = DMACH1TCR2 | (BIT15 | BIT2);


    /* enable the interrupt with BIOS call */
    C55_enableIER0(C55_IEN08);

    /*
     * Next we assume the peripheral (I2S0) is going to be enabled
     */
}

/****************************************************************************/
void DmaInterrupt(void) {
    if ((DMAIFR & BIT0) == BIT0) {
        /* IS20 transmit interrupt has fired */
        if (DMACH0TCR2 & BIT1) {
            // The transmit "pong" buffer is empty
        	isTransmitPong = 1;
        	SEM_post(&SEM_OutputAudio);
        }  else {
            // The transmit "ping" buffer is empty
        	isTransmitPong = 0;
        	SEM_post(&SEM_OutputAudio);
        }
        /* This is our interrupt clear the flag by writing a 1 */
        DMAIFR = BIT0;
    }
    if ((DMAIFR & BIT1) == BIT1) {
        /* IS20 receive interrupt has fired */
        if (DMACH1TCR2 & BIT1) {
        	// The receive "pong" buffer is full
        	isReceivePong = 1;
        	SEM_post(&SEM_AudioProcessor);
        } else {
        	// The receive "ping" buffer is full
        	isReceivePong = 0;
        	SEM_post(&SEM_AudioProcessor);
        }
        /* This is our interrupt clear the flag by writing a 1 */
        DMAIFR = BIT1;
    }
}

/****************************************************************************/
static uint32_t MemoryAddress(const void * Address)
{
    static const void * DARAM[] = {(void *)0x0,    (void *)0x7FFF};
    static const void * SARAM[] = {(void *)0x8000, (void *)0x27FFF};
    static const uint32_t DaramOffset = 0x10000;
    static const uint32_t SaramOffset = 0x80000;

    uint32_t DmaAddress;

    if ((Address >= DARAM[0]) && (Address <= DARAM[1]))
    {
        DmaAddress = (uint32_t)Address;
        DmaAddress = (DmaAddress << 1) + DaramOffset;
    }
    else if ((Address >= SARAM[0]) && (Address <= SARAM[1]))
    {
        DmaAddress = (uint32_t)Address;
        DmaAddress = (DmaAddress << 1) + SaramOffset;
    }
    else
    {
        while(1); /* error condition */
    }

    return DmaAddress;
}


