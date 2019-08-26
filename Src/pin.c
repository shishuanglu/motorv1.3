
/*****************************************  Include  ******************************************************/
#include "pin.h"



/******************************************  Private type definition  *******************************************/


/******************************************  Private macro definition  ******************************************/

/******************************************  Private function declaration  **************************************/

/******************************************  Private variable definition  ***************************************/

/******************************************  Global variable definition  ****************************************/
FlagStatus stopCheckFlag = RESET, resetCheckFlag = RESET;


/******************************************  Function definition  ***********************************************/



/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
void motorRunF (void)
{	
	HAL_GPIO_WritePin (CTR3_MOT_GPIO_Port, CTR3_MOT_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (CTR4_MOT_GPIO_Port, CTR4_MOT_Pin, GPIO_PIN_RESET);

	//HAL_GPIO_WritePin (CTR3_MOT_GPIO_Port, CTR3_MOT_Pin, GPIO_PIN_SET);
	//HAL_GPIO_WritePin (CTR4_MOT_GPIO_Port, CTR4_MOT_Pin, GPIO_PIN_RESET);
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
void motorBackRunF (void)
{	
	HAL_GPIO_WritePin (CTR3_MOT_GPIO_Port, CTR3_MOT_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (CTR4_MOT_GPIO_Port, CTR4_MOT_Pin, GPIO_PIN_SET);
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
void motorStopF (void)
{


	HAL_GPIO_WritePin (CTR3_MOT_GPIO_Port, CTR3_MOT_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (CTR4_MOT_GPIO_Port, CTR4_MOT_Pin, GPIO_PIN_SET);

	//HAL_GPIO_WritePin (CTR3_MOT_GPIO_Port, CTR3_MOT_Pin, GPIO_PIN_SET);
	//HAL_GPIO_WritePin (CTR4_MOT_GPIO_Port, CTR4_MOT_Pin, GPIO_PIN_RESET);
}





/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
void servoPwrOnF (void)
{	
#if 0
	HAL_GPIO_WritePin (CTR1_MOT_GPIO_Port, CTR1_MOT_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (CTR2_MOT_GPIO_Port, CTR2_MOT_Pin, GPIO_PIN_RESET);

#endif
}


/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
void buzzerOpenF (void)
{
	HAL_GPIO_WritePin (CTR_BUZZER_GPIO_Port, CTR_BUZZER_Pin, GPIO_PIN_SET);
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
void buzzerCloseF (void)
{
	HAL_GPIO_WritePin (CTR_BUZZER_GPIO_Port, CTR_BUZZER_Pin, GPIO_PIN_RESET);
}

stateE isBuzzerOpenF (void)
{
	stateE status = TRUE;

	if (GPIO_PIN_SET == HAL_GPIO_ReadPin(CTR_BUZZER_GPIO_Port, CTR_BUZZER_Pin))
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
void testLedOpenF (void)
{
	HAL_GPIO_WritePin (TEST_LED_GPIO_Port, TEST_LED_Pin, GPIO_PIN_SET);
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
void testLedCloseF (void)
{
	HAL_GPIO_WritePin (TEST_LED_GPIO_Port, TEST_LED_Pin, GPIO_PIN_RESET);
}


/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
stateE isStopPinCheckedF (void)
{
	stateE status = TRUE;
	
	//if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(STOP_CHK_GPIO_Port, STOP_CHK_Pin))
	if ((SET == stopCheckFlag) || (GPIO_PIN_RESET == HAL_GPIO_ReadPin(STOP_CHK_GPIO_Port, STOP_CHK_Pin)))
	{
		status = TRUE;
	}
	else
	{
		status = FALSE;
	}

	stopCheckFlag = RESET;

	return status;
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
stateE isResetPinCheckedF (void)
{
	stateE status = TRUE;
	
	//if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(RESET_CHK_GPIO_Port, RESET_CHK_Pin))
	if ((SET == resetCheckFlag) || (GPIO_PIN_RESET == HAL_GPIO_ReadPin(RESET_CHK_GPIO_Port, RESET_CHK_Pin)))
	{
		
		status = TRUE;
	}
	else
	{
		status = FALSE;
	}
	resetCheckFlag = RESET;

	return status;
}



