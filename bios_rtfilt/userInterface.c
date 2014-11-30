#include "userinterface.h"
#include "dma.h"

int isPressed = 0;

void InitializeUI() {
	// Initialize Buttons
    *SARCTRL    = 0x3C00;      // Select AIN3, which is GPAIN1
    *SARCLKCTRL = 0x0031;      // 100/50 = 2MHz
    *SARPINCTRL = 0x7104;
    *SARGPOCTRL = 0;
    return;
}

void IDLButtonMonitor() {
	*SARCTRL = 0xB800;
    uint16_t val = *SARDATA;
    if ((val < SW1 + 12) && (val > SW1 - 12))
        val = SW1;
    else if ((val < SW2 + 12) && (val > SW2 - 12))
        val = SW2;
    else
    	val = NoKey;

    if (val != NoKey && !isPressed) {
    	isPressed = 1;
    	if (val == SW1) {
    		// Switch 1
    		if (volumeControl < 32000)
    			volumeControl += 2000;
    	} else {
    		// Switch 2
    		if (volumeControl > 0)
    			volumeControl -= 2000;
    	}
    } else if (val == NoKey && isPressed)
    	isPressed = 0;
}
