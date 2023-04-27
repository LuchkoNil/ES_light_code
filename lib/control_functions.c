#include "control_functions.h"

void control_supercapacitor(FlagStatus state, TS_state_system *state_system){

	if(state == SET){
		HAL_GPIO_WritePin(CHARGE_GPIO_Port, CHARGE_Pin, GPIO_PIN_SET);
		state_system ->status_supercapacitor = CHARGING;
	}else
	if(state == RESET){
		HAL_GPIO_WritePin(CHARGE_GPIO_Port, CHARGE_Pin, GPIO_PIN_RESET);
		state_system ->status_supercapacitor = DISCHARGING;
	}
	
}

void check_voltage(TS_state_system *state_system){
	if(state_system->status_supercapacitor == CHARGE){
		if(state_system->voltage <= VOLTAGE_EXP){
			state_system->current_step = STEP_EXPLOSION;
		}
	}
}

void check_PWM(TS_state_system *state_system){
		
	if(state_system->status_init != INIT)return;
	
		if((state_system->command == COMMAND_INIT)&&(state_system->current_step == STEP_WAIT_COMMAND)){
				state_system->current_step = STEP_COMMAND_INIT;
		}
		if((state_system->command == COMMAND_READY)&&(state_system->current_step == STEP_COMMAND_INIT)){
				state_system->current_step = STEP_COMMAND_READY;
		}
		if((state_system->command == COMMAND_CHARGE)&&(state_system->current_step == STEP_COMMAND_READY)){
				state_system->current_step = STEP_COMMAND_CHARGE;
		}
		if((state_system->command == COMMAND_SANCTION)&&(state_system->current_step == STEP_WAIT_COMMAND_SANCTION)){
				state_system->current_step = STEP_COMMAND_SANCTION;
		}
		if((state_system->command == COMMAND_ACTIVATE)&&(state_system->current_step == STEP_COMMAND_SANCTION)){
				state_system->current_step = STEP_COMMAND_ACTIVATE;
		}
}


void control_explosion(FlagStatus status_explosion){
		
		if(status_explosion == SET){
			HAL_GPIO_WritePin(ACTIVATE_GPIO_Port, ACTIVATE_Pin, GPIO_PIN_SET);
		}else
		if(status_explosion == RESET){
			HAL_GPIO_WritePin(ACTIVATE_GPIO_Port, ACTIVATE_Pin, GPIO_PIN_RESET);
		}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC1){
			HAL_ADC_Stop_DMA(hadc);
			float tmp = 0;
			tmp = ((float) __HAL_ADC_CALC_VREFANALOG_VOLTAGE(state_system.ADC_Data[1], hadc->Init.Resolution));
			state_system.voltage = ((float)__HAL_ADC_CALC_DATA_TO_VOLTAGE(tmp, state_system.ADC_Data[2], hadc->Init.Resolution))*3/1000;
			state_system.temperature = __HAL_ADC_CALC_TEMPERATURE(tmp, state_system.ADC_Data[0], hadc->Init.Resolution);
    	state_system.flag_check_voltage = 1;
			HAL_ADC_Start_DMA(hadc, (uint32_t*)&state_system.ADC_Data, 3);
    }
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
		uint32_t tmp = 0;
		double second = 0;
	
    if (htim->Instance == TIM1)
    {
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            TIM1->CNT = 0;
        
						tmp = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
						second = (float)tmp/1000000;
            state_system.frequency = 1/second;
            state_system.msWidth = (float)HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2)/1000;
						state_system.flag_check_PWM = 1;
					
						if(49 < state_system.frequency < 52){
		
							if(( 0.8 < state_system.msWidth)&&(state_system.msWidth < 1)){
								state_system.command = COMMAND_INIT;
							}else
							if(( 1.1 < state_system.msWidth)&&( state_system.msWidth < 1.3)){
								state_system.command = COMMAND_READY;
							}else
							if(( 1.4 < state_system.msWidth)&&(state_system.msWidth < 1.6)){
								state_system.command = COMMAND_CHARGE;
							}else
							if(( 1.7 < state_system.msWidth)&&(state_system.msWidth < 1.9)){
								state_system.command = COMMAND_SANCTION;
							}else
							if(( 2 < state_system.msWidth)&&(state_system.msWidth < 2.2)){
								state_system.command = COMMAND_ACTIVATE;
							}
						}
        }
    }
}
