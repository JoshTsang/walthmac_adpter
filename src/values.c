/*
 * values.c
 *
 *  Created on: Apr 8, 2013
 *      Author: mee990
 */

#include <stdio.h>

#include "addr.h"
#include "values.h"

value args[] = {
	{"digitPerG", 0, DIGIT_PER_G},
	{"hopper20", 0, HOPPER20},
	{"hopper20Warn", 0, HOPPER20_WARN},
	{"hopper80", 0, HOPPER80},
	{"hopper80Warn", 0, HOPPER80_WARN},
	{"hopperZero", 0, HOPPER_ZERO},
	{"wgtPeakDis", 0, WGT_PEAK_DIS},
	{"extrTime", 0, EXTR_TIME},
	{"calFrq", 0, CAL_FRQ},
	{"calFrqdis", 0, CAL_FRQ_DIS},
	{"ExtrAlgLen", 0, EXTR_ALG_LEN},
	{"ExtrAlgLendis", 0, EXTR_ALG_LEN_DIS},
	{"extrMinSpeed", 0, EXTR_MIN_SPEED},
	{"extrpGain", 0, EXTR_P_GAIN},
	{"extriGain", 0, EXTR_I_GAIN},
	{"extrDeadBand", 0, EXTR_DEAD_BAND},
	{"WgtPerHWarnUp", 0, WGT_PER_H_WARM_UP},
	{"WgtPerHWarnDw", 0, WGT_PER_H_WARN_DW},
	{"maxSpdPerMin", 0, MAX_SPD_PER_MIN},
	{"WgtPerMShLen", 0, WGT_PER_MSH_LEN},
	{"dragpGain", 0, DRAG_P_GAIN},
	{"dragiGain", 0, DRAG_I_GAIN},
	{"dragDeadBand", 0, DRAG_DEAD_BAND},
	{"kgPerMeterWarnUp", 0, KG_PER_METER_WARN_UP},
	{"kgPerMeterWarnDw", 0, KG_PER_METER_WARN_DW},
	{"dragMinSpeed", 0, DRAG_MIN_SPEED},
	{"dragHighScope", 0, DRAG_HIGH_SCOPE},
	{"dragZeroDeadband", 0, DRAG_ZERO_DEAD_BAND},
	{"extrZeroDeadband", 0, EXTR_ZERO_DEAD_BAND},
	{"systemRunMode", 0, SYSTEM_RUN_MODE},
	{"addupmeter", 0, ADD_UP_METER},
	{"addupweight", 0, ADD_UP_WEIGHT},
	{NULL, 0, 0}
};

value status[] = {
 	{"setkgPerMeter", 0, SET_KG_PER_METER},
	{"kgPerMeterShow", 0, KG_PER_METER_SHOW},
	{"autoManualstate", 0, AUTO_MANUAL_STATE},
	{"setWgtPerHour", 0, SET_WGT_PER_HOUR},
	{"wgtPerHour", 0, WGT_PER_HOUR},
	{"wgtPerRev", 0, WGT_PER_REV},
	{"speedPerMin", 0, SPEED_PER_MIN},
	{"meterPerMin", 0, METER_PER_MIN},
	{"AIN2Extruder", 0, AIN2_EXTRUDER},
	{"extrudDect", 0, EXTRUD_DECT},
	{"wgtPerHourAddup", 0, WGT_PER_HOUR_ADD_UP},
	{"AIN1Drager", 0, AIN1_DRAGER},
	{"dragerDect", 0, DRAGER_DECT},
	{"meterAddup", 0, METER_ADDUP},
	{NULL, 0, 0}
};
