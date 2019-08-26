#ifndef __PWM_H_
#define __PWM_H_

/*****************************************  Include  ******************************************************/
#include "typedef.h"
#include "stm32f1xx_hal.h"

/******************************************  Global macro definition  ******************************************/

/******************************************  Global type definition  *******************************************/

/******************************************  Global variable declaration  **************************************/
extern TIM_HandleTypeDef htim1, htim2;

/******************************************  Global function declaration  **************************************/
void setServoPwmPulseF (U32 pulseValue);
void setCh1PwmPulseF (U32 pulseValue);


#endif









