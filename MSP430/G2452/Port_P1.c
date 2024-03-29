/* ------------------------------------------------------------------ */
/*                                                                    */
/*                                                                    */
/*                   Port_P1.c                                        */
/*                                                                    */
/*                Procedures for P1                                   */
/*                                                                    */
/* ------------------------------------------------------------------ */

#include    "includes.h"

/* ------------------------------------------------------------------ */


/* ---------- P1_Set_Osc -------------------------------------------- */

/* Set P1 pin to oscillator mode. Argument defines pin to be set.     */

void P1_Set_Osc(unsigned char osc_bit) {

    P1SEL &= osc_bit;
    P1SEL2 |= osc_bit;
  
}

/* ---------- END -------------------------------------------------- */

