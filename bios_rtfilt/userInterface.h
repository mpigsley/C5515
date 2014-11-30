/*
 * userInterface.h
 *
 *  Created on: Mar 8, 2014
 *      Author: mpigs_000
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

/* ------------------------------------------------------------------------ *
 *  Register Definitions                                                    *
 * ------------------------------------------------------------------------ */
#define SARCTRL      ((ioport volatile unsigned*)0x7012)
#define SARDATA      ((ioport volatile unsigned*)0x7014)
#define SARCLKCTRL   ((ioport volatile unsigned*)0x7016)
#define SARPINCTRL   ((ioport volatile unsigned*)0x7018)
#define SARGPOCTRL   ((ioport volatile unsigned*)0x701A)

#define SW1   0x2A8  // Switch 1 value
#define SW2   0x1FC  // Switch 2 value
#define SW12  0x195  // Switch 1 + 2 value
#define NoKey 0x3FE

/* ------------------------------------------------------------------------ *
 * External Prototypes                                                      *
 * ------------------------------------------------------------------------ */
extern void InitializeUI();
extern void IDLButtonMonitor();

#endif /* USERINTERFACE_H_ */
