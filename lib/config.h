#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32g0xx_hal.h"

#define TIMEOUT_CHARGE 300000 // 5 min
#define TIMEOUT_DISCHARGE TIMEOUT_CHARGE/2 

#define VOLTAGE_EXP 3.0
#define ACCELERATION 3 
#define MC3416_ADDR (0x4C<<1) 

#define VERSION 1.0

#endif
