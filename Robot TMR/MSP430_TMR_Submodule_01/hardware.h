/* ------------------------------------------------------------------ */
/*                                                                    */
/*                                                                    */
/*                   hardware.h                                       */
/*                                                                    */
/*          Basic LaunchPad hardware definitions                      */
/*                                                                    */
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ 

    Sensors:    left  = sensor_voltage[0] = bit 0 in sensor_x
                mid   = sensor_voltage[1] = bit 1 in sensor_x
                right = sensor_voltage[2] = bit 2 in sensor_x
                
    COUT bits:  bit 0 = right motor
                bit 1 = left motor
                bit 2 = half speed / stop
                
    COUT bits   2 1 0
                | | |
                | | ---- 1 = right motor full, 0 = right motof half/stop
                | -------1 = left motor full, 0 = left motof half/stop
                ---------1 = motor half speed, 0 = motor stop
                
*/                                
    
/* ------ LED ------------------------------------------------------- */

#define     LED_DIR         P1DIR    
#define     LED_OUT         P1OUT    

#define     L_LED_BIT   0x08            /* P1.3 */    
#define     C_LED_BIT   0x10            /* P1.4 */
#define     R_LED_BIT   0x20            /* P1.5 */

#define     R_LED_OFF       LED_OUT |= R_LED_BIT     /* R led ON */
#define     R_LED_ON        LED_OUT &= ~R_LED_BIT    /* R led OFF */
#define     R_LED_TOGGLE    LED_OUT ^= R_LED_BIT     /* R led Toggle */
    
#define     C_LED_OFF       LED_OUT |= C_LED_BIT     /* C led ON */
#define     C_LED_ON        LED_OUT &= ~C_LED_BIT    /* C led OFF */
#define     C_LED_TOGGLE    LED_OUT ^= C_LED_BIT     /* C led Toggle */
    
#define     L_LED_OFF       LED_OUT |= L_LED_BIT     /* L led ON */
#define     L_LED_ON        LED_OUT &= ~L_LED_BIT    /* L led OFF */
#define     L_LED_TOGGLE    LED_OUT ^= L_LED_BIT     /* L led Toggle */
    
#define     LED_OUT         P1OUT    

/* ------ OUT & IN -------------------------------------------------- */

#define     COUT_DIR        P2DIR    
#define     COUT_OUT        P2OUT
#define     CIN_DIR         P2DIR    
#define     CIN_IN          P2IN
#define     CIN_IES         P2IES
#define     CIN_IE          P2IE 
#define     CIN_IFG         P2IFG

#define     COUT_BIT        0x1C    
#define     CIN_BIT         0x20
#define     COUT_MASK       0x1C        
        
/* ------ motor commands -------------------------------------------- */

#define     RIGHT_FULL      0x01    
#define     LEFT_FULL       0x02    
#define     RIGHT_HALF      0x04    
#define     LEFT_HALF       0x04    

/* ------ prototypes ------------------------------------------------ */

void Hardware_Init(void) ;

/* ---------- END --------------------------------------------------- */

