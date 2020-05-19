/*
 * commands.c
 *
 *  Created on: 19. 5. 2020
 *      Author: pivov
 */

#include "commands.h"

void forward(){
    L_MOT_FORWARD;
    R_MOT_FORWARD;
    L_MOT_FULL;
    R_MOT_FULL;
}

void back(){
    L_MOT_BACK;
    R_MOT_BACK;
    L_MOT_FULL;
    R_MOT_FULL;
}

void stop(){
    L_MOT_BREAK;
    R_MOT_BREAK;
}

void right(){
    L_MOT_FORWARD;
    R_MOT_BACK;
    L_MOT_FULL;
    R_MOT_FULL;
}

void left(){
    L_MOT_BACK;
    R_MOT_FORWARD;
    L_MOT_FULL;
    R_MOT_FULL;
}

void follow(){
    P3OUT |= 0x10;
    Get_Config_Switch();            /* read TMR configuration */
    Get_Submodule_CMD();            /* read data from submodules */
    Evaluate_Active_Submodules();   /* evaluate which submod. are active */
    Exec_Submodule_CMD();           /* execute CMD */
    P3OUT &= ~0x10;
}

void dance(int d_count){
    switch(d_count){
        case 0:
        case 1:
        case 4:
        case 5:
            forward();
            break;
        case 2:
        case 3:
            back();
            break;

        default:
            right();
            break;
        }
}

