#ifndef __SIGNAL_H_
#define __SIGNAL_H_

/*****************************************  Include  ******************************************************/
#include "typedef.h"
#include "stm32f1xx_hal.h"
#include "command.h"
#include "motorTask.h"


/******************************************  Global macro definition  ******************************************/
#define SIGNAL_NUM_M 2

/******************************************  Global type definition  *******************************************/
typedef enum
{
	IDLE = 0,
	VALID,
	ERR,
}signalState;

typedef struct
{
	U16 GPIO_Pin;
	U32 pulseWidth;
	U32 pulseMaxValidValue;
	U32 pulseMinValidValue;
	U32 pulseMaxIdleValue;
	U32 pulseMinIdleValue;
	U32 keepTimer;
	U32 outTime;
	U8 errCnt;
	SYS_STATE cmdE;
	signalState signalStatusE;
	signalState curStatusE;
	signalState lastStatusE;
	TIM_HandleTypeDef* htim;
}signal;


/******************************************  Global variable declaration  **************************************/
extern TIM_HandleTypeDef htim1;

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern signal signalListT [SIGNAL_NUM_M];
/******************************************  Global function declaration  **************************************/
stateE isMotorRunCtrF (void);
stateE isResetCtrF (void);
void signalFilterHandleF (void);


#endif









