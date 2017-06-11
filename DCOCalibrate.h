/*
 * DOCCalibrate.h
 *
 *  Created on: 2/06/2017
 *      Author: james
 */

#ifndef SRC_DCOCALIBRATE_H_
#define SRC_DCOCALIBRATE_H_

#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

//DOC calibration constants
#define DCO_CAL_500KHZ				(122)		// 122 * 4096 = 499.7KHz
#define DCO_CAL_1MHZ				(244)		// 244 * 4096 = 0.999MHz
#define DCO_CAL_2MHZ				(488)		// 488 * 4096 = 1.999MHz
#define DCO_CAL_8MHZ				(1953)	// 1953 * 4096 = 7.999MHz
#define DCO_CAL_12MHZ				(2930)	// 2930 * 4096 = 12.001MHz

#define DCO_CAL_1843KHZ				(450)		// 450 * 4096 = 1.843200MHz, good for using uart

/*
 *  calibrate the DCO in msp430 with a watch crystal.
 *  A watch crystal must be connected. This will use
 *  TimerA in capture mode. And this function will
 *  reset TimerA.
 *
 *  ref: http://www.ti.com/lit/an/slaa336a/slaa336a.pdf
 *
 *  @param: data - one of the pre-define value above
 *  @param: isStable - when false, the function will
 *  		wait for the 32k crystal to be stablized
 *  		first before calibartion.
 *
 */

void DCOCalibrate(unsigned int data, bool isStable);	// calibrate DOC


#endif /* SRC_DCOCALIBRATE_H_ */
