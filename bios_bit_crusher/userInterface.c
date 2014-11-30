#include "usbstk5515_led.h"
#include "userinterface.h"
#include "bit_crusher.h"

int isPressed = 0;

void InitializeUI() {
	// Initialize Buttons
    *SARCTRL    = 0x3C00;      	// Select AIN3, which is GPAIN1
    *SARCLKCTRL = 0x0031;      	// 100/50 = 2MHz
    *SARPINCTRL = 0x7104;
    *SARGPOCTRL = 0;

    // Initialize LEDs
 	SYS_EXBUSSEL = 0x6000;  	// Enable user LEDs on external bus
    USBSTK5515_ULED_init();
    USBSTK5515_ULED_setall(0xFF);

    // Initialize in resolution state
	USBSTK5515_ULED_on(0);

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
		USBSTK5515_ULED_on(3);
    	isPressed = 1;
    	if (val == SW1) {
    		// Switch 1
    		if (resolution)
    			resolution--;
    	} else {
    		// Switch 2
    		if (resolution < 15)
    			resolution++;
    	}
    } else if (val == NoKey && isPressed) {
		USBSTK5515_ULED_off(3);
		isPressed = 0;
    }
}
