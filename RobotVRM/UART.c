/*
 * UART.c
 *
 *  Created on: 19. 5. 2020
 *      Author: pivov
 */

#include "UART.h"

int pos;    //buffer position counter

void UART_Init(){
    volatile unsigned int i;
    pos = 0;

    P3SEL |= 0xC0;                            // P3.6,7 = USART1 option select

    ME2 |= UTXE1 + URXE1;                     // Enable USART1 TXD/RXD
    UCTL1 |= CHAR;                            // 8-bit character
    UTCTL1 |= SSEL1;                          // UCLK = SMCLK
    UBR01 = 0x68;                             // 1Mhz/9600 = 104
    UBR11 = 0x00;                             //
    UMCTL1 = 0x2C;                            // modulation
    UCTL1 &= ~SWRST;                          // Initialize USART state machine
    IE2 |= URXIE1;                            // Enable USART1 RX interrupt

    //__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USART1RX_VECTOR
__interrupt void usart1_rx (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USART1RX_VECTOR))) usart1_rx (void)
#else
#error Compiler not supported!
#endif
{
  while (!(IFG2 & UTXIFG1));                // USART1 TX buffer ready?
  //TXBUF1 = RXBUF1;                          // RXBUF1 to TXBUF1   ECHO

  buffer[pos++] = RXBUF1;
  if(pos == 6) command = RXBUF1;
  if(pos>8) pos = 0;    //reset position counter

  //if(RXBUF1 == 0xAA) pos = 0;
  //if(pos == 5) command = RXBUF1;
  //pos++;

}


