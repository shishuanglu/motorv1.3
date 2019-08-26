
/*****************************************  Include  ******************************************************/
#include "signal.h"
#include "pin.h"
//#include "typedef.h"


/******************************************  Private type definition  *******************************************/


/******************************************  Private macro definition  ******************************************/
#define ERR_FILTER_NUM_M    20	//错误滤波次数

#define ROT_SIGNAL_M		0
#define RESET_SIGNAL_M		1

#define SHORT_PRESS_TIME_M 	(2000/20) //20为任务周期
#define LONG_PRESS_TIME_M 	(5000/20)

#define OUT_TIME_M		(1000/20)		//20为任务周期       /1S


#define ROT_SIGNAL_INIT_M \
{ \
	.GPIO_Pin = GPIO_PIN_10, \
	.pulseWidth = 0, \
	.pulseMaxValidValue = 20, \
	.pulseMinValidValue = 18, \
	.pulseMaxIdleValue = 12, \
	.pulseMinIdleValue = 10, \
	.keepTimer = 0, \
	.outTime = 0, \
	.errCnt = 0, \
	.cmdE = RUN_STATE, \
	.signalStatusE = IDLE, \
	.curStatusE = IDLE, \
	.lastStatusE = IDLE, \
	.htim = &htim3, \
}

#define RESET_SIGNAL_INIT_M \
{ \
	.GPIO_Pin = GPIO_PIN_11, \
	.pulseWidth = 0, \
	.pulseMaxValidValue = 20, \
	.pulseMinValidValue = 18, \
	.pulseMaxIdleValue = 12, \
	.pulseMinIdleValue = 10, \
	.keepTimer = 0, \
	.outTime = 0, \
	.errCnt = 0, \
	.cmdE = RESET_STATE, \
	.signalStatusE = IDLE, \
	.curStatusE = IDLE, \
	.lastStatusE = IDLE, \
	.htim = &htim4, \
}



/******************************************  	Private function declaration  **************************************/

/******************************************  Private variable definition  ***************************************/

/******************************************  Global variable definition  ****************************************/

/******************************************  Function definition  ***********************************************/
signal signalListT [SIGNAL_NUM_M] = {ROT_SIGNAL_INIT_M, RESET_SIGNAL_INIT_M};

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
void HAL_GPIO_EXTI_Callback (U16 GPIO_Pin)
{
	U8 signalId = 0xff;
	
	//GPIO_PinState pinState;
	
	for (U8 i=0; i<SIGNAL_NUM_M; i++)
	{
		if (GPIO_Pin == signalListT[i].GPIO_Pin)
		{
			signalId = i;
			break;
		}
	}
	if (0xff == signalId)
	{
		return;
	}
	else
	{	 
		
		if (GPIO_PIN_RESET == HAL_GPIO_ReadPin (GPIOB, GPIO_Pin))
		{
			/*falling edge*/
			signalListT[signalId].pulseWidth = __HAL_TIM_GET_COUNTER (signalListT[signalId].htim);
			
			if ((signalListT[signalId].pulseWidth >= signalListT[signalId].pulseMinIdleValue)
				&& (signalListT[signalId].pulseWidth <= signalListT[signalId].pulseMaxIdleValue))
			{
				signalListT[signalId].signalStatusE = IDLE;
			}
			else if ((signalListT[signalId].pulseWidth >= signalListT[signalId].pulseMinValidValue)
				&& (signalListT[signalId].pulseWidth <= signalListT[signalId].pulseMaxValidValue))
			{
				signalListT[signalId].signalStatusE = VALID;
			}
			else
			{
				signalListT[signalId].signalStatusE = ERR;
			}

		}
		else
		{
			/*rising edge*/
			__HAL_TIM_SET_COUNTER(signalListT[signalId].htim, 0);
			signalListT[signalId].pulseWidth = 0;
			//signalListT[signalId].lastTick = signalListT[signalId].currentTick;

		}
	}

	if (GPIO_Pin == RESET_CHK_Pin)
	{
		resetCheckFlag = SET;
	}

	if (GPIO_Pin == STOP_CHK_Pin)
	{
		stopCheckFlag = SET;

	}
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
stateE isMotorRunCtrF (void)
{
	stateE status = TRUE;
	
	if (VALID == signalListT [ROT_SIGNAL_M].signalStatusE)
	{
		status = TRUE;
	}
	else
	{
		status = FALSE;
	}

	return status;
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
stateE isResetCtrF (void)
{
	stateE status = TRUE;
	
	if (VALID == signalListT [RESET_SIGNAL_M].signalStatusE)
	{
		status = TRUE;
	}
	else
	{
		status = FALSE;
	}

	return status;
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
void signalFunctionHandleF (U8 signalId)
{
#if 0//带使能

	if (ROT_SIGNAL_M == signalId)
	{
		if ((IDLE == signalListT[ROT_SIGNAL_M].curStatusE) && (VALID == signalListT[ROT_SIGNAL_M].lastStatusE)
			&& (signalListT[ROT_SIGNAL_M].outTime >= OUT_TIME_M) &&(VALID == signalListT[RESET_SIGNAL_M].curStatusE))
		{
			signalListT[ROT_SIGNAL_M].outTime = 0;
			
			addCmd2ListF (signalListT[ROT_SIGNAL_M].cmdE);
			printf("%s\n",__FUNCTION__);
		}
	}
#else

if ((IDLE == signalListT[signalId].curStatusE) && (VALID == signalListT[signalId].lastStatusE)
	&& (signalListT[signalId].outTime >= OUT_TIME_M))
{
	signalListT[signalId].outTime = 0;
	
	addCmd2ListF (signalListT[signalId].cmdE);
	printf("%s\n",__FUNCTION__);
}

	
#endif

#if 0
	if (VALID == signalListT[signalId].curStatusE)
	{
		signalListT[signalId].keepTimer++;
	}
	else
	{
		signalListT[signalId].keepTimer = 0;
	}
	
	if (signalListT[signalId].keepTimer < SHORT_PRESS_TIME_M)
	{

	}
	else if (signalListT[signalId].keepTimer < LONG_PRESS_TIME_M)
	{

	}
	else
	{

	}
#endif
	
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
void signalFilterHandleF (void)
{
	U8 signalId;

	for (signalId=0; signalId<SIGNAL_NUM_M; signalId++)
	{
		signalListT[signalId].curStatusE = signalListT[signalId].signalStatusE;
		//signalListT[signalId].signalStatusE = RES;
	
		if (ERR == signalListT[signalId].curStatusE)
		{
			signalListT[signalId].errCnt++;
			if (signalListT[signalId].errCnt <= ERR_FILTER_NUM_M)
			{
				signalListT[signalId].curStatusE = signalListT[signalId].lastStatusE;
			}
			else
			{
				signalListT[signalId].errCnt = 0;
				signalListT[signalId].curStatusE = ERR;
			}
			
		}
		else
		{
			signalListT[signalId].errCnt = 0;
		}

		signalFunctionHandleF (signalId);
	
		signalListT[signalId].lastStatusE = signalListT[signalId].curStatusE;

		if (signalListT[signalId].outTime < OUT_TIME_M)
		{
			signalListT[signalId].outTime++;
		}
		else
		{
			signalListT[signalId].outTime = OUT_TIME_M;
		}
	}

}


