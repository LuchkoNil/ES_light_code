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
	
	COMMAND_WAIT = 0x0F55,
  COMMAND_INIT = 0x1307,
	COMMAND_READY = 0x28B4,
	COMMAND_CHARGE = 0x3AC4,
	COMMAND_SANCTION = 0x4675,
	COMMAND_ACTIVATE = 0x5130,
}TE_command;

typedef enum{
	STEP_INIT_ACCELETOMETER = 0,
	
	STEP_COMMAND_WAIT = 0x0F55,
	STEP_COMMAND_INIT = 0x1307,
	STEP_COMMAND_READY = 0x28B4,
	STEP_COMMAND_CHARGE = 0x3AC4,
  STEP_COMMAND_SANCTION = 0x4675,
	STEP_COMMAND_ACTIVATE = 0x5130,
	
	STEP_NO = 0xAAAA,
	STEP_ERROR = 0xFFFF,
}TE_step;

typedef enum{
  INIT_ACC_NO = 0,
  INIT_ACC,
	INIT_ACC_ERROR
}TE_init;

typedef struct {
	TE_step current_step;
	
	TE_step step_init;
	TE_step step_ready;
	TE_step step_charge;
	
	TE_command command;
	TE_command wait_command;
	uint8_t flag_new_cmd;
	
	TE_status_supercapacitor status_supercapacitor;
	
	uint8_t quantity_attempts_init;
	TE_init status_init;
	
	uint8_t flag_check_voltage;
	//uint8_t flag_check_PWM;
	
	uint16_t ADC_Data[3];
	float voltage;
	float temperature;
	
	float frequency_pwm;
	float msWidth;

	uint8_t acceleration;
	uint8_t ID_ACC;
	uint8_t count_error_read_acc;
}TS_state_system;

typedef struct {
	
	double Ax;
	double Ay;
	double Az;
	
	uint8_t Ax_MAX;
	double Ay_MAX;
	double Az_MAX;
	
}TS_state_accel;

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t z;
	uint16_t status;
}TS_state_debug;

#endif
