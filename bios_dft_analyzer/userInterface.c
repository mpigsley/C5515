#include <std.h>
#include <log.h>
#include <idl.h>
#include <sem.h>

#include "tskcfg.h"
#include "stdint.h"
#include "usbstk5515.h"

#include"usbstk5515_i2c.h"
#include"usbstk5515_gpio.h"
#include "userinterface.h"
#include "audio.h"

Uint8 lcd_lut[] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};

Int16 OSD9616_send( Uint16 comdat, Uint16 data ) {
    Uint8 cmd[2];
    cmd[0] = comdat & 0x00FF;     // Specifies whether data is Command or Data
    cmd[1] = data;                // Command / Data

    return USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 2 );
}

Int16 OSD9616_multiSend( Uint8* data, Uint16 len ) {
    Uint16 x;
    Uint8 cmd[10];
    for(x=0;x<len;x++)               // Command / Data
    {
    	cmd[x] = data[x];
    }
    return USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, len );
}

void InitializeUI() {
	Uint8 cmd[10];    // For multibyte commands

	/* Initialize I2C */
	USBSTK5515_I2C_init( );

	/* Initialize LCD power */
	USBSTK5515_GPIO_setDirection( 12, 1 );  // Output
	USBSTK5515_GPIO_setOutput( 12, 1 );     // Enable 13V

	/* Initialize OSD9616 display */
	OSD9616_send(0x00,0x00); // Set low column address
	OSD9616_send(0x00,0x10); // Set high column address
	OSD9616_send(0x00,0x40); // Set start line address

	cmd[0] = 0x00 & 0x00FF;  // Set contrast control register
	cmd[1] = 0x81;
	cmd[2] = 0x7f;
	USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

	OSD9616_send(0x00,0xa1); // Set segment re-map 95 to 0
	OSD9616_send(0x00,0xa6); // Set normal display

	cmd[0] = 0x00 & 0x00FF;  // Set multiplex ratio(1 to 16)
	cmd[1] = 0xa8;
	cmd[2] = 0x0f;
	USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

	OSD9616_send(0x00,0xd3); // Set display offset
	OSD9616_send(0x00,0x00); // Not offset
	OSD9616_send(0x00,0xd5); // Set display clock divide ratio/oscillator frequency
	OSD9616_send(0x00,0xf0); // Set divide ratio

	cmd[0] = 0x00 & 0x00FF;  // Set pre-charge period
	cmd[1] = 0xd9;
	cmd[2] = 0x22;
	USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

	cmd[0] = 0x00 & 0x00FF;  // Set com pins hardware configuration
	cmd[1] = 0xda;
	cmd[2] = 0x02;
	USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

	OSD9616_send(0x00,0xdb); // Set vcomh
	OSD9616_send(0x00,0x49); // 0.83*vref

	cmd[0] = 0x00 & 0x00FF;  //--set DC-DC enable
	cmd[1] = 0x8d;
	cmd[2] = 0x14;
	USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

	OSD9616_send(0x00,0xaf); // Turn on oled panel

	// Turn off Vertical Scrolling
	cmd[0] = 0x00;
	cmd[1] = 0xa3;  // Set Vertical Scroll Area
	cmd[2] = 16;  // Set No. of rows in top fixed area
	cmd[3] = 0;  // Set No. of rows in scroll area
	OSD9616_multiSend( cmd, 4 );

	// Turn off Horizontal Scrolling
	OSD9616_send(0x00,0x2e);
}

void IDL_DFTtoLCD() {
	int offset = 16, i;
	SEM_pend(&SEM_StartUI, SYS_FOREVER);

	/* Low */
	OSD9616_send(0x00,0x00);   // Set low column address
	OSD9616_send(0x00,0x10);   // Set high column address
	OSD9616_send(0x00,0xb0+1); // Set page for page 1 to page 5
	for (i=0; i < 128; i++) {
		if (i >= offset && i < offset + NUM_BINS) {
			int16_t index = NUM_BINS - i + offset - 1;
			int16_t temp = (int16_t) ((256*((int32_t) dft_bins[index]))/32767);
			if (temp < 8) OSD9616_send(0x40, lcd_lut[temp]);
			else OSD9616_send(0x40,0xFF);
		} else OSD9616_send(0x40,0x00);
	}

	/* High */
	OSD9616_send(0x00,0x00);   // Set low column address
	OSD9616_send(0x00,0x10);   // Set high column address
	OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
	for (i=0; i < 128; i++) {
		if (i >= offset && i < offset + NUM_BINS) {
			int16_t index = NUM_BINS - i + offset - 1;
			int16_t temp = (int16_t) (((256*((int32_t) dft_bins[index]))/32767) - 8);
			if (temp >= 8) OSD9616_send(0x40,0xFF);
			else if (temp >= 0) OSD9616_send(0x40, lcd_lut[temp]);
			else OSD9616_send(0x40,0x00);
		} else OSD9616_send(0x40,0x00);
	}
}
