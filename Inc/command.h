#ifndef __COMMAND_H_
#define __COMMAND_H_

/*****************************************  Include  ******************************************************/
#include "typedef.h"
#include "stm32f1xx_hal.h"
#include "motorTask.h"


/******************************************  Global macro definition  ******************************************/
#define CMD_TOTAL_NUM_M 16

/******************************************  Global type definition  *******************************************/
#if 0
typedef enum
{
	startTurn = 0,
	stopTurn,
	motorRst,
	res,
}command;
#endif

/******************************************  Global variable declaration  **************************************/


/******************************************  Global function declaration  **************************************/
void addCmd2ListF (SYS_STATE cmd);
SYS_STATE getCurrentCmdF (void);


#endif









