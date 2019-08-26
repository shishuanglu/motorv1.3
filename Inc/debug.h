#ifndef __DEBUG_H_
#define __DEBUG_H_

/*****************************************  Include  ******************************************************/
#include "typedef.h"
#include "stm32f1xx_hal.h"

/******************************************  Global macro definition  ******************************************/
#define TASK_RUNNING_TEST 0

/******************************************  Global type definition  *******************************************/

/******************************************  Global variable declaration  **************************************/
extern UART_HandleTypeDef huart1;

/******************************************  Global function declaration  **************************************/
void print_ch(const char ch);
void print_int(const int dec);
void print_str(const char *ptr);
void print_float(const float flt);
void my_printf(const char *format,...);


#endif









