#ifndef __PIN_H_
#define __PIN_H_

/*****************************************  Include  ******************************************************/
#include "typedef.h"
#include "stm32f1xx_hal.h"


/******************************************  Global macro definition  ******************************************/


/******************************************  Global type definition  *******************************************/


/******************************************  Global variable declaration  **************************************/
extern TIM_HandleTypeDef htim1;
extern FlagStatus stopCheckFlag, resetCheckFlag;
/******************************************  Global function declaration  **************************************/
void motorRunF (void);
void motorBackRunF (void);
void motorStopF (void);
void buzzerOpenF (void);
void buzzerCloseF (void);
void testLedOpenF (void);
void testLedCloseF (void);
stateE isResetPinCheckedF (void);
stateE isStopPinCheckedF (void);
void testLed1ToggleF (void);
void switchOnF (void);
void switchOffF (void);
void servoPwrOnF (void);




#endif









