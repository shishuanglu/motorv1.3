
/*****************************************  Include  ******************************************************/
#include "pwm.h"
#include "cmsis_os.h"



/******************************************  Private macro definition  ******************************************/

/******************************************  Private type definition  *******************************************/

/******************************************  Private function declaration  **************************************/

/******************************************  Private variable definition  ***************************************/

/******************************************  Global variable definition  ****************************************/


/******************************************  Function definition  ***********************************************/

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: …Ë÷√µÁ¥≈∑ß¬ˆøÌ
***************************************************************************/
void setServoPwmPulseF (U32 pulseValue)
{
	HAL_StatusTypeDef status = HAL_OK;

	taskENTER_CRITICAL ();

	TIM_OC_InitTypeDef sConfigOC;
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);

	//sConfigOC.OCMode = TIM_OCMODE_PWM1;
	//sConfigOC.Pulse = pulseValue;
	//sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	//sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = pulseValue;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

	while (HAL_OK != HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3));
	while (HAL_OK != HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3));
	//status |= HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
	//status |= HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	//if (HAL_OK != status)
	//printf("status err!\n");
	

	taskEXIT_CRITICAL ();
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: …Ë÷√≤‚ ‘Õ®µ¿1¬ˆøÌ
***************************************************************************/
void setCh1PwmPulseF (U32 pulseValue)
{
	TIM_OC_InitTypeDef sConfigOC;
	HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = pulseValue;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: …Ë÷√≤‚ ‘Õ®µ¿2¬ˆøÌ
***************************************************************************/
void setCh2PwmPulseF (U32 pulseValue)
{
	TIM_OC_InitTypeDef sConfigOC;
	HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_2);

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = pulseValue;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: …Ë÷√≤‚ ‘Õ®µ¿3¬ˆøÌ
***************************************************************************/
void setCh3PwmPulseF (U32 pulseValue)
{
	TIM_OC_InitTypeDef sConfigOC;
	HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_3);

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = pulseValue;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
}






