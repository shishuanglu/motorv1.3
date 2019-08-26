#ifndef __FSM_H_
#define __FSM_H_

#if 1

#ifndef NULL
#define NULL (void*)0
#endif // !NULL

typedef int STATE;
typedef int EVENT;
typedef void (*ActFun)(void);


typedef struct
{
	STATE		nextState;
	ActFun		vEventActFun;
}STATE_EVENT_TABLE_T;

typedef struct
{
	EVENT					event;
	STATE_EVENT_TABLE_T*	stateEventTable;
}ACT_TABLE_T;

typedef struct
{
	STATE			state;
	ACT_TABLE_T*	actTable;
}STATE_TABLE_T;

typedef struct
{
	unsigned int	maxStateNum;
	unsigned int	maxEventNum;
	STATE			curState;
	STATE_TABLE_T*	stateTable;
}FSM_T;

void vFSM_RegistF(FSM_T* pFsm, STATE_TABLE_T* pStateTable, STATE initState, int stateNum, int eventNum);
void vFSM_EventHandleF(FSM_T* pFsm, EVENT event);

#endif

#endif // !__FSM_H_

