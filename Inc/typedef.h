#ifndef __TYPEDEF_H_
#define __TYPEDEF_H_

//#include "cmsis_os.h"
//#include "debug.h"

typedef		unsigned			char 	bool;

typedef   	signed          	char 	S8;
typedef   	signed short     	int 	S16;
typedef   	signed           	int 	S32;

typedef 	unsigned          	char 	U8;
typedef 	unsigned short     	int 	U16;
typedef 	unsigned           	int 	U32;

#if 1
typedef enum
{
	FALSE = 0,
	TRUE = !FALSE,
}stateE;

#endif

#endif

