
/*****************************************  Include  ******************************************************/

#include "servo.h"
#include "pwm.h"
#include "main.h"


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
  * @others: 打开电磁阀
***************************************************************************/
void servoOpenF (void)
{	
	//printf("call %s!\n",__FUNCTION__);
#if SERVO_ENABLE_M
	setServoPwmPulseF (1940);
#else 
	HAL_GPIO_WritePin (CTR1_MOT_GPIO_Port, CTR1_MOT_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (CTR2_MOT_GPIO_Port, CTR2_MOT_Pin, GPIO_PIN_RESET);
#endif
}


/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 关闭电磁阀
***************************************************************************/
void servoCloseF (void)
{
	//printf("call %s!\n",__FUNCTION__);

#if SERVO_ENABLE_M
	setServoPwmPulseF (1100);
#else
	HAL_GPIO_WritePin (CTR1_MOT_GPIO_Port, CTR1_MOT_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (CTR2_MOT_GPIO_Port, CTR2_MOT_Pin, GPIO_PIN_RESET);
#endif
}
















