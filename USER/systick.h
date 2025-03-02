/*************************************************************
 * Copyright (C) 2024-09-27 Jerry Yang. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
 
#ifndef __SYSTICK
#define __SYSTICK

#include "sys.h"

void SysTick_Init(void);
void delay_us(u32 nus);
void delay_ms(u16 nms);

#endif /*__SYSTICK*/



