#include "timer.h"

uint32_t timout_charge = TIMEOUT_CHARGE;
uint32_t timout_discharge = TIMEOUT_DISCHARGE;
	
void timer_1ms_tick(TS_state_system *state_system){
	timeout_charge(state_system);
}


void timeout_charge(TS_state_system *state_system){

	
	if(state_system ->status_supercapacitor == CHARGING){
	
		if(timout_charge != 0){
			timout_charge --;
		}else{
			state_system->status_supercapacitor = CHARGE; 
			timout_charge = TIMEOUT_CHARGE;
		}
	}else
	if(state_system ->status_supercapacitor == DISCHARGING){
		
		if(timout_discharge != 0){
			timout_discharge --;
		}else{
			state_system->status_supercapacitor = DISCHARGE; 
			timout_discharge = TIMEOUT_DISCHARGE;
		}
	}	
}
