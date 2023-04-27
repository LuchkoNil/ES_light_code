#ifndef __TIMER_H
#define __TIMER_H

#include "type.h"
#include "control_functions.h"

void timer_1ms_tick(TS_state_system *state_system);
void timeout_init_i2c(TS_state_system *state_system);
void timeout_charge(TS_state_system *state_system);

#endif
