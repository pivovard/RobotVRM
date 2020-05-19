#include <msp430.h>

#define     SMCLK_BIT       0x20        /* SMCLK on P5 */
#define     MCLK_BIT        0x10        /*  MCLK on P5 */

void main(void)
{
    volatile unsigned int i;
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    P3SEL |= 0xC0;                            // P3.6,7 = USART1 option select

    //BCSCTL2 |= SELM_2 + SELS;                 // MCLK= SMCLK= XT2 (safe)

    //BCM_Init
    /* DCO(13,4) = 4.096 MHz, SMCLK = DCO:4, ACLK = stop                  */
    DCOCTL = ((0x05 << 5) | 0x0F);      /* DCO = 5, MOD = 16 */
    BCSCTL1 = (XT2OFF | 0x07);          /* RSEL = 7 */
    BCSCTL2 = DIVS_2;                   /* MCLK = DCO:1, SMCLK = DCO:4 */

    _BIS_SR(OSCOFF);                    /* stop XT1 */

    P5SEL |= MCLK_BIT | SMCLK_BIT;      /* MCLK + SMCLK output */
    P5DIR |= MCLK_BIT | SMCLK_BIT;      /* MCLK + SMCLK output */
    //BCM

    ME2 |= UTXE1 + URXE1;                     // Enable USART1 TXD/RXD
    UCTL1 |= CHAR;                            // 8-bit character
    UTCTL1 |= SSEL1;                          // UCLK = SMCLK
    UBR01 = 0x68;                             // 1Mhz/9600 = 104
    UBR11 = 0x00;                             //
    UMCTL1 = 0x2C;                            // modulation
    UCTL1 &= ~SWRST;                          // Initialize USART state machine
    IE2 |= URXIE1;                            // Enable USART1 RX interrupt

    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

//ECHO
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
  TXBUF1 = 0x70;
  TXBUF1 = RXBUF1;                          // RXBUF1 to TXBUF1
}
