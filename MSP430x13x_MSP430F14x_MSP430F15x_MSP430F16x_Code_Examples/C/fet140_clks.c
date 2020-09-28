/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 * 
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP-FET430P140 Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK
//
//  Description: Output buffered MCLK, SMCLK and ACLK.
//  ACLK = LFXT1 = 32768, MCLK = DCO Max, SMCLK = XT2
//  //* XTAL's REQUIRED - NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
//
//                MSP430F149
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32k
//         --|RST          XOUT|-
//           |                 |
//           |            XT2IN|-
//           |                 | XTAL (455k - 8Mhz)
//           |RST        XT2OUT|-
//           |                 |
//           |             P5.4|-->MCLK = DCO Max
//           |             P5.5|-->SMCLK = XT2
//           |             P5.6|-->ACLK = 32kHz
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW +WDTHOLD;                  // Stop Watchdog Timer
  DCOCTL = DCO0 + DCO1 + DCO2;              // Max DCO
  BCSCTL1 = RSEL0 + RSEL1 + RSEL2;          // XT2on, max RSEL
  BCSCTL2 |= SELS;                          // SMCLK = XT2
  P5DIR |= 0x70;                            // P5.6,5,4 outputs
  P5SEL |= 0x70;                            // P5.6,5,5 options

  while(1)
  {
  }
}

