
/*****************************************  Include  ******************************************************/
#include "command.h"




/******************************************  Private type definition  *******************************************/
typedef struct
{
	U8 in;
	U8 out;
	U8 validNum;
	U8 totalNum;
}FIFO;

/******************************************  Private macro definition  ******************************************/

/******************************************  Private function declaration  **************************************/

/******************************************  Private variable definition  ***************************************/

/******************************************  Global variable definition  ****************************************/
SYS_STATE cmdListG[CMD_TOTAL_NUM_M];
FIFO buffPara = { \
					.in 		= 0, \
					.out 		= 0, \
					.validNum 	= 0, \
					.totalNum 	= CMD_TOTAL_NUM_M, \
				};

/******************************************  Function definition  ***********************************************/



/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
static stateE isCmdListEmptyF (void)
{
	stateE status = TRUE;

	if (0 == buffPara.validNum)
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
void addCmd2ListF (SYS_STATE cmd)
{
	if (buffPara.validNum >= buffPara.totalNum)
	{
		return;
	}
	else
	{
		cmdListG[buffPara.in] = cmd;
		buffPara.in++;
		buffPara.validNum++;

		if (buffPara.in >= buffPara.totalNum)
		{
			buffPara.in = 0;
		}
	}
}

/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
SYS_STATE getCurrentCmdF (void)
{
	SYS_STATE cmd = STOP_STATE;


	if (TRUE == isCmdListEmptyF())
	{
		return cmd;
	}
	else
	{
		cmd = cmdListG[buffPara.out];
		buffPara.out++;
		buffPara.validNum--;

		if (buffPara.out >= buffPara.totalNum)
		{
			buffPara.out = 0;
		}

	}

	return cmd;
}


