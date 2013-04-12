/*
 * addr.h
 *
 *  Created on: Apr 3, 2013
 *      Author: mee990
 */

#ifndef ADDR_H_
#define ADDR_H_

#define EXTR_ALG_LEN         0x0040
#define EXTR_ALG_LEN_DIS     0x0042
#define EXTR_P_GAIN          0x0048
#define EXTR_I_GAIN			 0x004A
#define EXTR_DEAD_BAND		 0x004C
#define WGT_PER_H_WARM_UP	 0x0052
#define WGT_PER_H_WARN_DW 	 0x0054
#define EXTR_MIN_SPEED 		 0x0046
#define MAX_SPD_PER_MIN 	 0x0056
#define EXTR_ZERO_DEAD_BAND  0x0082
#define CAL_FRQ 			 0x0022
#define CAL_FRQ_DIS 		 0x0024
#define DRAG_P_GAIN 		 0x0064
#define DRAG_I_GAIN 		 0x0066
#define DRAG_DEAD_BAND 		 0x0068
#define KG_PER_METER_WARN_UP 	 0x006e
#define KG_PER_METER_WARN_DW 	 0x0070
#define DRAG_MIN_SPEED 	 	 0x0074
#define DRAG_HIGH_SCOPE 	 0x006a
#define DRAG_ZERO_DEAD_BAND  0x0080
#define SYSTEM_RUN_MODE 	 0x00a0
#define DIGIT_PER_G 	   	 0x0002
#define WGT_PER_MSH_LEN 	 0x0060
#define HOPPER20 	 		 0x0004
#define HOPPER20_WARN 		 0x0006
#define HOPPER80 			 0x0008
#define HOPPER80_WARN 	 	 0x000a
#define HOPPER_ZERO 		 0x000c
#define WGT_PEAK_DIS 		 0x000e
#define EXTR_TIME 			 0x0016
#define ADD_UP_METER		 0x0a10
#define ADD_UP_WEIGHT		 0x0a20

#define SET_KG_PER_METER 	 0x006c
#define KG_PER_METER_SHOW 	 0x0214
#define AUTO_MANUAL_STATE 	 0X0218

#define SET_WGT_PER_HOUR 	 0x0050
#define WGT_PER_HOUR 		 0X020C

#define WGT_PER_REV 		 0x020a
#define SPEED_PER_MIN 		 0x0208
#define METER_PER_MIN 		 0X0210

#define AIN2_EXTRUDER   	 0x0222
#define EXTRUD_DECT 		 0x0226
#define WGT_PER_HOUR_ADD_UP  0x0240
#define AIN1_DRAGER 		 0x0220
#define DRAGER_DECT 		 0x0224
#define METER_ADDUP 		 0x0242

#endif /* ADDR_H_ */
