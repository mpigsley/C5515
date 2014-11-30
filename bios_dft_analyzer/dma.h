/*******************************************************************************
****                            I N C L U D E S
*******************************************************************************/
#include "stdint.h"

/*******************************************************************************
****                         D E F I N I T I O N S
*******************************************************************************/
#define DMA_PING_PONG_BUFFER_LENGTH (48)
#define DMA_OUTPUT_BUFFER_LENGTH (DMA_PING_PONG_BUFFER_LENGTH * 2)
#define DMA_INPUT_BUFFER_LENGTH (DMA_PING_PONG_BUFFER_LENGTH * 2)

/*******************************************************************************
****                    G L O B A L   V A R I A B L E S
*******************************************************************************/
extern int32_t g_dmaOutputBuffer[DMA_OUTPUT_BUFFER_LENGTH];
extern int32_t g_dmaInputBuffer[DMA_OUTPUT_BUFFER_LENGTH];

/*******************************************************************************
****               F U N C T I O N   D E C L A R A T I O N S
*******************************************************************************/
extern void DmaInitialize(void);
extern void StartDma(void);
