#ifndef __MOTORTASK_H_
#define __MOTORTASK_H_

/*****************************************  Include  ******************************************************/
#include "typedef.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "fsm.h"


/******************************************  Global macro definition  ******************************************/

/******************************************  Global type definition  *******************************************/
#define SYS_STATE			STATE

#define STOP_STATE			0
#define RUN_STATE			1
#define SERVO_OFF_STATE		2
#define SERVO_ON_STATE		3
#define RESET_STATE			4
#define RESET_CHECK_STATE	5

#define SYS_EVENT					EVENT
#define NO_EVENT					0
#define EVENT_STOP_2_SERVO_ON		1
#define EVENT_SERVO_ON_2_RUN		2
#define EVENT_SERVO_ON_2_RST		3
#define EVENT_RUN_2_SERVO_OFF		4
#define EVENT_RST_2_SERVO_OFF		5
#define EVENT_SERVO_OFF_2_STOP		6
#define EVENT_SERVO_OFF_2_RST_CHK	7
#define EVENT_SERVO_ON_2_STOP		8
#define EVENT_SERVO_ON_2_RST_CHK	9



/******************************************  Global variable declaration  **************************************/
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
/******************************************  Global function declaration  **************************************/
void motorTaskF (void const * argument);


#endif









