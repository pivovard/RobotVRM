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
//  MSP-FET430P140 Demo - I2C, Master Writes/Reads with Slave, Rptd Start
//
//  Description: This example shows the repeated start condition. It talks to
//  the MSP430F169.  It first does two writes, then sends repeated start and
//  does a read, then sets STP.
//  Access ready Interrupt occurs when 2 bytes are sent by master, and the
//  master is switched to Reciever. Another ARDY Interrupt occurs when data
//  is read from I2CDRB and then a stop condition is issued.
//  The received data is in RXData and is checked for validity. If the received
//  data is incorrect, the CPU is trapped and P1.0 LED will stay on.
//  The P1.0 LED will blink if data transfer occurs without any errors.
//
//  This is the Master code.
//  The Slave code is called fet140_i2c_17.c
//  ACLK = n/a, MCLK = SMCLK = I2CCLOCK = DCO ~ 800kHz
//  //* MSP430F15x, MSP430F16x Device Required *//
//
//                                 /|\  /|\
//                  MSP430F169     10k  10k     MSP430F169
//                    slave         |    |        master
//              -----------------|  |    |  -----------------
//             |             P3.1|<-|---+->|P3.1             |
//             |                 |  |      |             P1.0|-->LED
//             |                 |  |      |                 |
//             |             P3.3|<-+----->|P3.3             |
//             |                 |         |                 |
//
//
//  H. Grewal / L. Westlund
//  Texas Instruments Inc.
//  Nov 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//******************************************************************************

#include <msp430.h>

unsigned int xmit,rcv = 0;
char TXData = 0;
char RXData;
char TestData = 0;

int main (void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop Watchdog
  P3SEL |= 0x0A;                            // Select I2C pins
  U0CTL |= I2C+SYNC;                        // Recommended init procedure
  U0CTL &= ~I2CEN;                          // Recommended init procedure
  I2CTCTL |= I2CSSEL1+I2CTRX;               // SMCLK, transmit
  I2CSA = 0x0048;                           // Slave Address
  I2CIE = TXRDYIE+RXRDYIE+ARDYIE;           // Enable TXRDY & RXRDY ISR
  U0CTL |= I2CEN;                           // Enable I2C
  P1DIR |= 0x01;
  P1OUT = 0;
  TACCR0 = 1000;                            // Delay between tranfers
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TASSEL_1;                         // TACLK = ACLK.

  while(1)
  {
    I2CNDAT = 0x03;
    U0CTL |= MST;                           // Master mode
    I2CTCTL |= I2CSTT+I2CTRX;               // Initiate transfer - write to slave
    __bis_SR_register(CPUOFF+GIE);          // Enter LPM0
    P1OUT ^= 0x01;
    if (TestData++ != RXData) break;        // Test received data
    TACTL |= TACLR+MC_1;                    // Up mode
    __bis_SR_register(LPM3_bits);           // Wait for delay
  }
  P1OUT |= 0x01;
  while(1);
}

// Timer_A0 Interrupt Service Routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERA0_VECTOR
__interrupt void ta0_isr(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMERA0_VECTOR))) ta0_isr (void)
#else
#error Compiler not supported!
#endif
{
  TACTL &= ~MC_1;
  LPM3_EXIT;                                // Exit LPM3 on return
}

// Common ISR for I2C Module
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USART0TX_VECTOR
__interrupt void I2C_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USART0TX_VECTOR))) I2C_ISR (void)
#else
#error Compiler not supported!
#endif
{
 switch( I2CIV )
 {
   case  2: break;                          // Arbitration lost
   case  4: break;                          // No Acknowledge
   case  6: break;                          // Own Address
   case  8:
            if (xmit == 0)
            {
             I2CNDAT = 0x01;                // Receive only one byte
             I2CTCTL &= ~I2CTRX;            // Clear transmit bit
             I2CTCTL |= I2CSTT;             // Restart - read from slave
            }
            if (rcv == 1)
            {
             I2CTCTL |= I2CSTP;             // Send stop
             while (I2CBB & I2CDCTL);       // I2C ready?
             rcv = 0;
            __bic_SR_register_on_exit(CPUOFF); // Clear LPM0
            }

            break;                          // Register Access Ready
   case 10:
            RXData = I2CDRB;
            rcv = 1;
            xmit = 1;
            break;                          // Receive Ready
   case 12:                                 // Transmit Ready
            I2CDRB = TXData++;              // Load I2CDRB and increment
            xmit = 0;
            break;
   case 14: break;                          // General Call
   case 16: break;                          // Start Condition
 }
}



