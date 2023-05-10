#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32g0xx_hal.h"
// 120000// 2 min

#define TIMEOUT_CHARGE 300000// 5 min
#define TIMEOUT_DISCHARGE 240000 // 4 min

#define VOLTAGE_EXP 2.0
#define ACCELERATION 15 
#define MC3416_ADDR (0x4C<<1) 


#define PWM_min   				800
#define PWM_max   				2500

#define InitPWM_min   		0.9
#define InitPWM_max   		1

#define ReadyPWM_min   		1.1
#define ReadyPWM_max   		1.2

#define ChargePWM_min    	1.4
#define ChargePWM_max   	1.5

#define SanctionPWM_min   1.7
#define SanctionPWM_max   1.8

#define ActivatePWM_min   2
#define ActivatePWM_max   2.1


#define VERSION 2.0

#endif
