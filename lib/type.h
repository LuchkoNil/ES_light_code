#ifndef __TYPE_H
#define __TYPE_H

#include "stm32g0xx_hal.h"

typedef enum{
	DISCHARGE = 0,
	DISCHARGING,
	CHARGE,
	CHARGING
}TE_status_supercapacitor;

typedef enum{
	COMMAND_NO = 0,
  COMMAND_INIT,
	COMMAND_READY,
	COMMAND_CHARGE,
	COMMAND_SANCTION,
	COMMAND_ACTIVATE,
}TE_command;

typedef enum{
	STEP_INIT_ACCELETOMETER = 0,
	STEP_WAIT_COMMAND,
	STEP_COMMAND_INIT,
	STEP_COMMAND_READY,
	STEP_COMMAND_CHARGE,
	STEP_WAIT_COMMAND_SANCTION,
  STEP_COMMAND_SANCTION,
	STEP_COMMAND_ACTIVATE,
	STEP_EXPLOSION,
	STEP_DISCHARGE
}TE_current_step;

typedef enum{
  INIT_NO = 0,
  INIT,
	INIT_ERROR
}TE_init;

typedef struct {
	TE_current_step current_step;
	
	TE_command command;
	
	TE_status_supercapacitor status_supercapacitor;
	
	uint8_t quantity_attempts_init;
	TE_init status_init;
	
	uint8_t flag_check_voltage;
	uint8_t flag_check_PWM;
	
	uint16_t ADC_Data[3];
	float voltage;
	float temperature;
	
	float frequency;
	float msWidth;

	uint8_t acceleration;

}TS_state_system;

typedef struct {
	
	double Ax;
	double Ay;
	double Az;
	
	double Ax_MAX;
	double Ay_MAX;
	double Az_MAX;
	
}TS_state_accel;


#endif
