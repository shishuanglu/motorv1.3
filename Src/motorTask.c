
/*****************************************  Include  ******************************************************/
#include "motorTask.h"
#include "signal.h"
#include "pin.h"
#include "main.h"
#include "command.h"
#include "servo.h"
#include "pwm.h"

/******************************************  Private type definition  *******************************************/


/******************************************  Private macro definition  ******************************************/
#define TIMEOUT_50MS_M 		50
#define TIMEOUT_200MS_M 	200
#define TIMEOUT_500MS_M 	500
#define TIMEOUT_560MS_M 	560
#define TIMEOUT_600MS_M 	600
#define TIMEOUT_620MS_M     620
#define TIMEOUT_800MS_M 	800
#define TIMEOUT_1S_M 		1000 
#define TIMEOUT_1500MS_M 	1500 
#define TIMEOUT_2S_M 		2000 
#define TIMEOUT_3S_M 		3000 
#define TIMEOUT_4S_M 		4000 
#define TIMEOUT_5S_M 		5000 

#define MOTOR_RUN_TIME		TIMEOUT_500MS_M
#define SERVO_OFF_TIME		TIMEOUT_50MS_M	

#define MOTOR_MAX_STATE_NUM		6
/******************************************  Private function declaration  **************************************/
static void vStopHandleF (void);
static void vRunHandleF (void);
static void vServoOffHandleF (void);
static void vServoOnHandleF (void);
static void vResetHandleF (void);
static void vRstChkHandleF (void);

/******************************************  Private variable definition  ***************************************/
U32 stopTick = 0, stopDiffTick = 0, runStartTick = 0, runDiffTick = 0;
U8 switchOffFlag = 0;

static STATE_EVENT_TABLE_T move2StopTable[1] = {
	{STOP_STATE, 	vStopHandleF}
};

static STATE_EVENT_TABLE_T move2RunTable[1] = {
	{RUN_STATE, 	vRunHandleF}
};

static STATE_EVENT_TABLE_T move2ServoOffTable[1] = {
	{SERVO_OFF_STATE, 	vServoOffHandleF}
};


static STATE_EVENT_TABLE_T move2ServoOnTable[1] = {
	{SERVO_ON_STATE, 	vServoOnHandleF}
};

static STATE_EVENT_TABLE_T move2RstTable[1] = {
	{RESET_STATE, 	vResetHandleF}
};


static STATE_EVENT_TABLE_T move2RstChkTable[1] = {
	{RESET_CHECK_STATE, 	vRstChkHandleF}
};



/*状态动作表*/
static ACT_TABLE_T	motorStopActTable[2] = {
	{EVENT_STOP_2_SERVO_ON, 		move2ServoOnTable},
	{NO_EVENT, 						move2StopTable},
};

static ACT_TABLE_T	motorRunActTable[2] = {
	{EVENT_RUN_2_SERVO_OFF, 	move2ServoOffTable},
	{NO_EVENT, 					move2RunTable},
};

static ACT_TABLE_T	motorServoOffActTable[3] = {
	{EVENT_SERVO_OFF_2_STOP, 		move2StopTable},
	{EVENT_SERVO_OFF_2_RST_CHK, 	move2RstChkTable},	
	{NO_EVENT, 						move2ServoOffTable},
};

static ACT_TABLE_T	motorServoOnActTable[3] = {
	{EVENT_SERVO_ON_2_RUN, 	move2RunTable},
	{EVENT_SERVO_ON_2_RST, 	move2RstTable},
	{NO_EVENT, 				move2ServoOnTable},
};

static ACT_TABLE_T	motorResetActTable[2] = {
	{EVENT_RST_2_SERVO_OFF, 	move2ServoOffTable},
	{NO_EVENT, 					move2RstTable},
};

static ACT_TABLE_T	motorResetChkActTable[1] = {
	{NO_EVENT, 					move2StopTable},
};



/*状态表*/
STATE_TABLE_T motorStateTable[MOTOR_MAX_STATE_NUM] = {
	{STOP_STATE, 		motorStopActTable},
	{RUN_STATE, 		motorRunActTable},
	{SERVO_OFF_STATE, 	motorServoOffActTable},
	{SERVO_ON_STATE, 	motorServoOnActTable},
	{RESET_STATE, 		motorResetActTable},
	{RESET_CHECK_STATE, motorResetChkActTable},
};

FSM_T motorFSM;
SYS_EVENT sysEvent;


bool servoTimerEnableFlag = 0, runEnableFlag = 0, resetEnableFlag = 0, servoEnableFlag = 0;
U32	 servoTime = 0, diffServoTime = 0;

/******************************************  Global variable definition  ****************************************/

/******************************************  Function definition  ***********************************************/

static void vStopHandleF (void)
{
	motorStopF ();
	runEnableFlag = 0;
	servoEnableFlag = 1;
	servoTimerEnableFlag = 1;
	printf("%s()\n",__FUNCTION__);
	
}
static void vRunHandleF (void)
{
	if (1 == servoTimerEnableFlag)
	{
		servoTimerEnableFlag = 0;
		servoTime = HAL_GetTick();
	}
	motorRunF ();
	printf("%s()\n",__FUNCTION__);
}

static void vServoOffHandleF (void)
{
	if (0 == servoEnableFlag)
	{
		servoEnableFlag = 1;
		servoCloseF ();
	}
	printf("%s()\n",__FUNCTION__);
}

static void vServoOnHandleF (void)
{
	if (1 == servoEnableFlag)
	{
		servoEnableFlag = 0;
		servoOpenF ();
	}
	
	if (1 == servoTimerEnableFlag)
	{
		servoTimerEnableFlag = 0;
		servoTime = HAL_GetTick();
	}
	printf("%s()\n",__FUNCTION__);

/*
	diffServoTime = HAL_GetTick() - servoTime;

	if (diffServoTime >= MOTOR_RUN_TIME)
	{
		servoTimerEnableFlag = 1;
	}
	*/
}

static void vResetHandleF (void)
{
	if (1 == servoTimerEnableFlag)
	{
		servoTimerEnableFlag = 0;
		servoTime = HAL_GetTick();
	}
	motorBackRunF ();
	printf("%s()\n",__FUNCTION__);
}

static void vRstChkHandleF (void)
{
	motorStopF ();
	resetEnableFlag = 0;
	printf("%s()\n",__FUNCTION__);
}




EVENT iGetEventF (void)
{
	EVENT event = 0xff;
	SYS_STATE state;

	/*select event of current state according to  event priority*/
	switch (motorFSM.curState)
	{
		case STOP_STATE:
			
			if (1 == resetEnableFlag)
			{
				osDelay(500);
				if (TRUE == isResetPinCheckedF())
				{
					resetEnableFlag = 0;
					event = NO_EVENT;
				}
				else
				{
					event = EVENT_STOP_2_SERVO_ON;
				}
				break;
			}

			state = getCurrentCmdF ();
			
			if (RUN_STATE == state)
			{
				runEnableFlag = 1;
				event = EVENT_STOP_2_SERVO_ON;
			}
			else if ((RESET_STATE == state) && (TRUE != isResetPinCheckedF()))
			{
				resetEnableFlag = 1;
				event = EVENT_STOP_2_SERVO_ON;
			}
			else
			{
				event = NO_EVENT;
			}

			break;

		case RUN_STATE:

			diffServoTime = HAL_GetTick() - servoTime;
			
			if (diffServoTime >= SERVO_OFF_TIME)
			{
				
				event = EVENT_RUN_2_SERVO_OFF;
			}
			else
			{
				event = NO_EVENT;
			}
	
			break;

		case SERVO_OFF_STATE:

			if ((TRUE == isResetPinCheckedF()) && (1 == resetEnableFlag))
			{
				event =  EVENT_SERVO_OFF_2_RST_CHK;
				break;
			}

			if (TRUE == isStopPinCheckedF())
			{
				event = EVENT_SERVO_OFF_2_STOP;

			}
			else
			{
				event = NO_EVENT;

			}
			
			break;

		case SERVO_ON_STATE:
			
			diffServoTime = HAL_GetTick() - servoTime;

			if (diffServoTime >= MOTOR_RUN_TIME)
			{
				if ((TRUE == isResetPinCheckedF()) || TRUE == isStopPinCheckedF())
				{
					event = NO_EVENT;
					break;
				}

				if (1 == resetEnableFlag)
				{
					servoTimerEnableFlag = 1; 
					event = EVENT_SERVO_ON_2_RST;
					break;
				}

				if (1 == runEnableFlag)
				{
					servoTimerEnableFlag = 1;
					event = EVENT_SERVO_ON_2_RUN;
					break; 
				}

				event = NO_EVENT;

			}
			
			
			break;
			
		case RESET_STATE:

			diffServoTime = HAL_GetTick() - servoTime;
			
			if (diffServoTime >= SERVO_OFF_TIME)
			{
				
				event = EVENT_RST_2_SERVO_OFF;
			}
			else
			{
				event = NO_EVENT;
			}
				
			break;
			
		case RESET_CHECK_STATE:
			
				event = NO_EVENT;
			
			break;

		default:

			//printf ("pc system state error!\n");
			break;

	}
	
	return event;
}

static void vMotorTaskLoop (void)
{
	
	sysEvent = iGetEventF ();
	vFSM_EventHandleF(&motorFSM, sysEvent);

}

static void vMotorTaskInit (void)
{
	HAL_TIM_Base_Start (&htim1);
	HAL_TIM_Base_Start (&htim3);
	HAL_TIM_Base_Start (&htim4);

	servoCloseF ();
	motorStopF ();
	
	vFSM_RegistF(&motorFSM, motorStateTable, STOP_STATE, MOTOR_MAX_STATE_NUM, 3);
}
/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
void motorTaskF (void const * argument)
{

	vMotorTaskInit ();
	printf("Init finish\n");

#if 0
	servoCloseF();
	osDelay(1000);
	servoOpenF();
#endif
	
	for(; ;)
	{
		vMotorTaskLoop ();
	}
}
