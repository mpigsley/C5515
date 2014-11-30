/*******************************************************************************
****                            I N C L U D E S
*******************************************************************************/
#include "stdint.h"

/*******************************************************************************
****                         D E F I N I T I O N S
*******************************************************************************/
#define TV02_8KSPS_SIZE 24000
#define UPSAMPLED_NUM 6

/*******************************************************************************
****                    G L O B A L   V A R I A B L E S
*******************************************************************************/
extern int16_t isReceivePong;
extern int16_t isTransmitPong;
extern int16_t enableFilter;
extern int16_t isInterpolating;

/*******************************************************************************
****               F U N C T I O N   D E C L A R A T I O N S
*******************************************************************************/
