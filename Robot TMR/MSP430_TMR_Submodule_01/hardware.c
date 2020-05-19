/* ----------------------------------------------------------------- */
/*                                                                   */
/*                                                                   */
/*           hardware.c                                              */
/*                                                                   */
/*                                                                   */
/*                                                                   */
/*                                                                   */
/*                                                                   */
/* ----------------------------------------------------------------- */

/* ---------- includes --------------------------------------------- */

#include    "includes.h"

/* ---------- variables -------------------------------------------- */

extern unsigned char   sync_flag;              /* CIN interrupt flag */

/* ---------- Hardware_Init ---------------------------------------- */

void Hardware_Init(void) {
    
    LED_DIR |= (L_LED_BIT | C_LED_BIT | R_LED_BIT);      /* LED outputs */
    
    R_LED_OFF;
    C_LED_OFF;
    L_LED_OFF;
        
    COUT_DIR |= COUT_BIT;                       /* C bits OUT */
    COUT_OUT &= ~COUT_BIT;                      /* outputs = 0 */
    
    CIN_DIR &= ~CIN_BIT;                        /* C input */
    CIN_IES |= CIN_BIT;                         /* edge H -> L */
    CIN_IFG &= ~CIN_BIT;                        /* clear IFG */
    CIN_IE  |= CIN_BIT;                         /* int. enable */
    
}
    
/* ---------- CIN_isr ---------------------------------------------- */

#pragma vector = PORT2_VECTOR                   /* vector for P2 irq */
interrupt void CIN_isr(void) {
    
    CIN_IFG &= ~CIN_BIT;                        /* clear IFG */
    sync_flag += 1;                             /* set flag */
    
}
    
/* ---------- END -------------------------------------------------- */
