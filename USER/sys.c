/*************************************************************
 * Copyright (C) 2024-09-27 Jerry Yang. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
 
#include "sys.h"
#include <stdio.h>
#include <stdlib.h>


void assert_failed(uint8_t* file, uint32_t line)
{
    printf("[assert]:file %s on line %d\r\n",file,(int)line);
    while(1){};
}




