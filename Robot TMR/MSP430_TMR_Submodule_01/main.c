/* ----------------------------------------------------------------- */
/*                                                                   */
/*                                                                   */
/*           Touch_01.c                                              */
/*                                                                   */
/*      Experiments with LaunchPad touch module                      */
/*                                                                   */
/*                                                                   */
/*                                                                   */
/* ----------------------------------------------------------------- */

/* ---------- includes --------------------------------------------- */

#include    "includes.h"

/* ---------- variables -------------------------------------------- */

unsigned short  touch_value;
unsigned char   timer_tick;
unsigned char   sec1_tick;
unsigned char   sync_flag;              /* CIN interrupt flag */

unsigned char   init_counter;
unsigned short  touch_limit;
unsigned short  touch_limit2;
unsigned short  touch_accu;
unsigned char   touch_flag;

unsigned char   sensor;
unsigned char   sensor_x;
unsigned char   cout_x;
unsigned short  sensor_voltage[3];
unsigned char   destroy_mask;

const unsigned char sensor_mask[] = {0x01, 0x02, 0x04};

extern unsigned short  wdt_counter;

/* ---------- BCM_Init --------------------------------------------- */

void main(void) { 

    BCM_Init();                         /* stop WDT & init clock module */
    Hardware_Init();                    /* init hw */
    WDT_Set_Timer();
    P2_Set_Osc(0x01);                   /* set P2.0 to Osc mode */

    timer_tick = 0;
    init_counter = 0;
    touch_accu = 0;
    sensor_x = 0;
    
                
    _enable_interrupts();
        
    while(1) {
        
        if(timer_tick != 0) {
            timer_tick -= 1;
            
            touch_value = TMR0_A3_Count_Osc();          /* read & restart TA0 */
            
            if(init_counter < 10) {                     /* wait first 10 cycles */
                init_counter += 1;
            }                
            
            if((init_counter < 18) && (init_counter >= 10)) { /* 8 calibration measurements, 0 = first start */
                init_counter += 1;
                touch_accu += (touch_value >> 3);       /* suma value/8 */
            }
            
            if(init_counter == 18) {                     /* calibration finish */
                touch_limit = touch_accu - (touch_accu >> 2);   /* limit = 3/4  accu */
                touch_limit2 = touch_accu - (touch_accu >> 3);  /* limit2 = 7/8  accu */
                init_counter += 1;
            }
            
            if(init_counter > 18) {                      /* normal operation */
                if(touch_value <= touch_limit2) {        /* weak touch */
                    touch_flag = TOUCH_WEAK;
                }
                else {
                    touch_flag = 0;
                }
                
                if(touch_value <= touch_limit) {        /* strong touch */
                    touch_flag |= TOUCH_STRONG;
                }
            }

        }
        
        if(sec1_tick != 0) {
            sec1_tick -= 1;
            
            if((touch_flag & TOUCH_WEAK) != 0) {          /* modify command if touch */
                destroy_mask = (destroy_mask << 1) & 0x07;
                if(destroy_mask == 0) {
                    destroy_mask = (wdt_counter & 0x0007);
                }
            }
            else {
                destroy_mask = 0;
            }
        }        
        
        if(sync_flag != 0) {            /* send next command to master module */
            sync_flag -= 1;
            ADC10_Start_Scan((unsigned short)sensor_voltage);
            for(sensor = 0; sensor < 3; sensor++) {
                if(sensor_voltage[sensor] > REF_HI) {   /* HI = black line */
                    sensor_x |= sensor_mask[sensor];
                }
                if(sensor_voltage[sensor] < REF_LO) {   /* LO = white background */
                    sensor_x &= ~(sensor_mask[sensor]);
                }
            }
                
            R_LED_OFF;                      /* clear LEDs */
            C_LED_OFF;
            L_LED_OFF;

            sensor_x = sensor_x ^ destroy_mask;             /* modify if touch */
                        
            switch(sensor_x) {
                case 0x00:                                      /* all white */
                            cout_x = 0x00;                      /* all stop */
                            break;
                case 0x02:                                      /* mid black */
                            cout_x = RIGHT_FULL | LEFT_FULL;    /* all full */
                            C_LED_ON;
                            break;
                case 0x06:                                      /* mid + right black */
                            cout_x = RIGHT_HALF | LEFT_FULL;    /* turn slow right */
                            R_LED_ON;
                            C_LED_ON;
                            break;
                case 0x03:                                      /* mid + left black */
                            cout_x = RIGHT_FULL | LEFT_HALF;    /* turn slow left */
                            L_LED_ON;
                            C_LED_ON;
                            break;
                case 0x04:                                      /* right black */
                            cout_x = LEFT_FULL;                 /* turn right */
                            R_LED_ON;
                            break;
                case 0x01:                                      /* left black */
                            cout_x = RIGHT_FULL;                /* turn left */
                            L_LED_ON;
                            break;
                case 0x05:                                      /* left + right black */
                            cout_x = RIGHT_FULL | LEFT_FULL;    /* forward */
                            C_LED_ON;
                            break;
                case 0x07:                                      /* all black */
                            cout_x = RIGHT_FULL | LEFT_FULL;    /* forward */
                            C_LED_ON;
                            break;
                default:                                        /* ??? */
                            cout_x = 0x00;                      /* stop */
                            sensor_x = 0x00;                    /* repair value */
                            break;
                            
            }

//            cout_x = cout_x ^ destroy_mask;     /* if touched modify command */
                                                 
            cout_x = cout_x << 2;               /* adjust bit positions to P2OUT */
            COUT_OUT &= ~COUT_MASK;             /* clear COUT bits */
            COUT_OUT |= (cout_x & COUT_MASK);   /* set new value */
                    
        }
        
    }   /* end while(1) */

}

/* ---------- END -------------------------------------------------- */
