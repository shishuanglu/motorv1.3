#include "FSM.h"
#if 1

/*״̬Ǩ��*/
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

/*״̬��ע��*/
void vFSM_RegistF(FSM_T* pFsm, STATE_TABLE_T* pStateTable, STATE initState, int stateNum, int eventNum)
{
	pFsm->maxStateNum = stateNum;
	pFsm->maxEventNum = eventNum;
	pFsm->curState = initState;
	pFsm->stateTable = pStateTable;
	return;
}

/*�¼�����*/
void vFSM_EventHandleF (FSM_T* pFsm, EVENT event)
{

	ACT_TABLE_T* pActTable = NULL;
	STATE_TABLE_T* pStateTable = NULL;
	STATE_EVENT_TABLE_T* pStateEventTable = NULL;
	ActFun pEventActFun = NULL;

	STATE state = tFSM_getCurStateF (pFsm);

	/*��ȡ��ǰ״̬��*/
	pStateTable = ptFSM_getStateTableF (pFsm);


	/*��ȡ��ǰ������*/
	for (unsigned int i = 0; i < uiFSM_getStateNumF(pFsm); i++)
	{
		if (state == pStateTable[i].state)
		{
			pActTable = pStateTable[i].actTable;
			break;
		}
	}

	/*��ȡ��ǰ״̬�¼���*/
	for (unsigned int i = 0; i < uiFSM_getEventNumF(pFsm); i++)
	{
		if (event == pActTable[i].event)
		{
			pStateEventTable = pActTable[i].stateEventTable;
			pEventActFun = pStateEventTable->vEventActFun;
			break;
		}
	}

	/*����ִ��*/
	if (pEventActFun)
	{
		(*pEventActFun)();
		vFSM_MoveStateF (pFsm, pStateEventTable->nextState);

	}
}

#endif