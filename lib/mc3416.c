#include "mc3416.h"

extern I2C_HandleTypeDef hi2c1;
extern TS_state_accel state_accel;
extern TS_state_debug state_debug;

TE_init MC34X9_Init(TS_state_system *state_system){
	
	uint8_t DataOutBuf[32] = {0};
	uint8_t DataInBuf[32] = {0};
	int TempSW;

  // Stand by mode
	DataOutBuf[0] = MC34X9_REG_MODE;
	DataOutBuf[1] = 0x00;
	if (HAL_OK != HAL_I2C_Master_Transmit(&hi2c1,MC3416_ADDR,DataOutBuf,2,100)){
		return INIT_ACC_ERROR;
	}

  HAL_Delay(50);

	//  MOTION CONTROL REGISTER(SHAKE_EN and ANYM_EN)
	DataOutBuf[0] = MC34X9_REG_MOTION_CTRL;
	DataOutBuf[1] = 0x04;
	if (HAL_OK != HAL_I2C_Master_Transmit(&hi2c1,MC3416_ADDR,DataOutBuf,2,100)){
		return INIT_ACC_ERROR;
	}
	HAL_Delay(10);
	
  // INTERRUPT ENABLE REGISTER (AUTO_CLR_EN and ANYM_INT_EN)
	DataOutBuf[0] = MC34X9_REG_INTR_CTRL;
	DataOutBuf[1] = 0x44;
	if (HAL_OK != HAL_I2C_Master_Transmit(&hi2c1,MC3416_ADDR,DataOutBuf,2,100)){
		return INIT_ACC_ERROR;	
	}
	
	HAL_Delay(10);
	
		// ODR (512 Hz)
	DataOutBuf[0] = MC34X9_REG_SR;
	DataOutBuf[1] = 0x05;
	if (HAL_OK != HAL_I2C_Master_Transmit(&hi2c1,MC3416_ADDR,DataOutBuf,2,100)){
		return INIT_ACC_ERROR;
	}
		HAL_Delay(10);
	//RANGE AND SCALE CONTROL REGISTER
	DataOutBuf[0] = MC34X9_REG_RANGE_C;
	DataOutBuf[1] = 0x30; // 16G
	if (HAL_OK != HAL_I2C_Master_Transmit(&hi2c1,MC3416_ADDR,DataOutBuf,2,100)){
		return INIT_ACC_ERROR;
	}
	HAL_Delay(10);
	// ANYMOTION THRESHOLD REGISTERS
	DataOutBuf[0] = MC34X9_REG_AM_THRESH_LSB;	
	TempSW = state_system->acceleration/(16.0/0x7fff);	
	DataOutBuf[1] = TempSW&0x00ff;
	DataOutBuf[2] = (TempSW>>8)&0x00ff;
	if (HAL_OK != HAL_I2C_Master_Transmit(&hi2c1,MC3416_ADDR,DataOutBuf,3,100)){
		return INIT_ACC_ERROR;
	}
		HAL_Delay(10);
	//ANYMOTION DEBOUNCE REGISTER
	DataOutBuf[0] = MC34X9_REG_AM_DB;	
	DataOutBuf[1] = 0x05;
	if (HAL_OK != HAL_I2C_Master_Transmit(&hi2c1,MC3416_ADDR,DataOutBuf,2,100)){
		return INIT_ACC_ERROR;
	}
		HAL_Delay(10);
  //Mode: Active
	DataOutBuf[0] = MC34X9_REG_MODE;
	DataOutBuf[1] = 0x01;
	if (HAL_OK != HAL_I2C_Master_Transmit(&hi2c1,MC3416_ADDR,DataOutBuf,2,300)){
		return INIT_ACC_ERROR;
	}

return INIT_ACC;

}



uint8_t MC3416Read(I2C_HandleTypeDef *hi2cx, TS_state_system *state_system, TS_state_accel *state_accel){

int16_t TempSW;	
uint8_t DataOutBuf[6] = {0};
uint8_t DataInBuf[6] = {0};

	if (HAL_OK == HAL_I2C_Mem_Read(&hi2c1, MC3416_ADDR, MC34X9_REG_XOUT_EX_L, 1, DataInBuf,6, 10)){
		TempSW = (DataInBuf[1]<<8)|DataInBuf[0]; 
		state_accel->Ax = TempSW*16.0/0x7fff; 
		TempSW = (DataInBuf[3]<<8)|DataInBuf[2];
		state_accel->Ay = TempSW*16.0/0x7fff; 
		TempSW = (DataInBuf[5]<<8)|DataInBuf[4];
		state_accel->Az = TempSW*16.0/0x7fff; 
		
		if(fabs(state_accel->Ax)>16) state_accel->Ax = 0;
		if(fabs(state_accel->Ay)>16) state_accel->Ay = 0;
		if(fabs(state_accel->Az)>16) state_accel->Az = 0;		
		
		if(fabs(state_accel->Ax) > state_accel->Ax_MAX){ 
				state_accel->Ax_MAX = fabs(state_accel->Ax);
			}
		
			if(fabs(state_accel->Ay) > state_accel->Ay_MAX){ 
				state_accel->Ay_MAX = fabs(state_accel->Ay);
			}

			if(fabs(state_accel->Az) > state_accel->Az_MAX){ 
				state_accel->Az_MAX = fabs(state_accel->Az);
			}
			state_debug.x = state_accel->Ax_MAX; 
			state_debug.y = state_accel->Ay_MAX;
			state_debug.z = state_accel->Az_MAX;
	}else{
		state_system ->count_error_read_acc++;
		if(state_system ->count_error_read_acc >= 0xFF)state_system ->count_error_read_acc = 0;
		return HAL_ERROR;
	}
	return HAL_OK;
}
