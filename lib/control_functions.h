#ifndef __CONTROL_FUNCTIONS_H
#define __CONTROL_FUNCTIONS_H

#include "type.h"
#include "main.h"
#include <math.h>
#include "stm32g0xx_hal.h"

extern TS_state_system state_system;

void control_supercapacitor(FlagStatus state, TS_state_system *state_system);
void check_voltage(TS_state_system *state_system);
void control_explosion(FlagStatus status_explosion);
void check_PWM(TS_state_system *state_system);

#endif
