#include "FSM.h"
#if 1

/*状态迁移*/
static void vFSM_MoveStateF (FSM_T* pFsm, STATE state)
{
	pFsm->curState = state;
	return;
}

static STATE_TABLE_T* ptFSM_getStateTableF (FSM_T* pFsm)
{
	return pFsm->stateTable;
}

static STATE tFSM_getCurStateF (FSM_T* pFsm)
{
	return pFsm->curState;
}

static unsigned int uiFSM_getStateNumF( FSM_T* pFsm)
{
	return pFsm->maxStateNum;
}

static unsigned int uiFSM_getEventNumF(FSM_T* pFsm)
{
	return pFsm->maxEventNum;
}

/*状态表注册*/
void vFSM_RegistF(FSM_T* pFsm, STATE_TABLE_T* pStateTable, STATE initState, int stateNum, int eventNum)
{
	pFsm->maxStateNum = stateNum;
	pFsm->maxEventNum = eventNum;
	pFsm->curState = initState;
	pFsm->stateTable = pStateTable;
	return;
}

/*事件处理*/
void vFSM_EventHandleF (FSM_T* pFsm, EVENT event)
{

	ACT_TABLE_T* pActTable = NULL;
	STATE_TABLE_T* pStateTable = NULL;
	STATE_EVENT_TABLE_T* pStateEventTable = NULL;
	ActFun pEventActFun = NULL;

	STATE state = tFSM_getCurStateF (pFsm);

	/*获取当前状态表*/
	pStateTable = ptFSM_getStateTableF (pFsm);


	/*获取当前动作表*/
	for (unsigned int i = 0; i < uiFSM_getStateNumF(pFsm); i++)
	{
		if (state == pStateTable[i].state)
		{
			pActTable = pStateTable[i].actTable;
			break;
		}
	}

	/*获取当前状态事件表*/
	for (unsigned int i = 0; i < uiFSM_getEventNumF(pFsm); i++)
	{
		if (event == pActTable[i].event)
		{
			pStateEventTable = pActTable[i].stateEventTable;
			pEventActFun = pStateEventTable->vEventActFun;
			break;
		}
	}

	/*动作执行*/
	if (pEventActFun)
	{
		(*pEventActFun)();
		vFSM_MoveStateF (pFsm, pStateEventTable->nextState);

	}
}

#endif