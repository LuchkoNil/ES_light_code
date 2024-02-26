#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32g0xx_hal.h"

#define TIMEOUT_CHARGE 70000 // 1 min 10 s
#define TIMEOUT_DISCHARGE 70000 // 1 min 10 s

#define VOLTAGE_EXP 2.0
#define ACCELERATION 15 
#define MC3416_ADDR (0x4C<<1) 

#define PWM_min   				49
#define PWM_max   				52

#define InitPWM_min   		1 - 0.05
#define InitPWM_max   		1 + 0.05

#define ReadyPWM_min   		1.4 - 0.05
#define ReadyPWM_max   		1.4 + 0.05

#define ChargePWM_min    	1.2 - 0.05
#define ChargePWM_max   	1.2 + 0.05

#define SanctionPWM_min   1.7 - 0.05
#define SanctionPWM_max   1.7 + 0.05

#define ActivatePWM_min   2 - 0.05
#define ActivatePWM_max   2 + 0.05


#define VERSION 4.1

#endif
