/*
 * DOCCalibrate.c
 *
 *  Created on: 2/06/2017
 *      Author: james
 */

#include "DCOCalibrate.h"


void DCOCalibrate(unsigned int data, bool isStable)
{
    unsigned int Compare = 0;
	unsigned int Oldcapture = 0;
    unsigned char Old_BCSCTL1;
    unsigned int Old_TACCTL0;
    unsigned int Old_TACTL;

    unsigned int delay = 0xFFFF;
    if (!isStable) while(delay--);

    Old_BCSCTL1 = BCSCTL1;				// make a backup
    Old_TACCTL0 = TACCTL0;				// make a backup
    Old_TACTL = TACTL;					// make a backup

    BCSCTL1 |= DIVA_3;                  // ACLK = LFXT1CLK/8
    TACCTL0 = CM_1 + CCIS_1 + CAP; 		// CAP, ACLK
    TACTL = TASSEL_2 + MC_2 + TACLR;    // SMCLK, cont-mode, clear

    while (1) {
        while (!(CCIFG & TACCTL0));     // Wait until capture occured
        TACCTL0 &= ~CCIFG;              // Capture occured, clear flag
        Compare = TACCR0;               // Get current captured SMCLK
        Compare = Compare - Oldcapture; // SMCLK difference
        Oldcapture = TACCR0;            // Save current captured SMCLK

        if (data == Compare){
            break;          			// If equal, leave "while(1)"
        }
        else if (data < Compare) {
            DCOCTL--;                   // DCO is too fast, slow it down
            if (DCOCTL == 0xFF)         // Did DCO roll under?
                if (BCSCTL1 & 0x0f)
                    BCSCTL1--;          // Select lower RSEL
        }
        else {
            DCOCTL++;                   // DCO is too slow, speed it up
            if (DCOCTL == 0x00)         // Did DCO roll over?
                if ((BCSCTL1 & 0x0f) != 0x0f)
                    BCSCTL1++;          // Sel higher RSEL
        }
    }
    TACCTL0 = Old_TACCTL0;              		// restore register
    TACTL = Old_TACTL;                  		// restore register
    BCSCTL1 = BCSCTL1 | (Old_BCSCTL1 & 0xF0);   // restore register
}
