/*
 * socket.c
 *
 *  Created on: Apr 3, 2013
 *      Author: mee990
 */
#include "defines.h"
#include "typedef.h"
#include "error.h"
#include "socket.h"

int getData(UINT16 reg, UINT32 *value) {
	int ret = 0;
	dataGetPkg pkg;
	dataGetResponse response;

	pkg.count = 1;
	pkg.ctrl = CTRL_GET_DATA;
	pkg.header = PKG_HEADER;
	pkg.req_addr = reg;
	pkg.checksum = 0xaa000000 + pkg.header + pkg.ctrl + pkg.req_addr + pkg.count;

	//TODO retry?
	ret = sendPkgAndGetRes(CTRL_GET_DATA, &pkg, &response);
	if (ret >= 0) {
		*value = response.value;
	} else {
		printf("get data failed, ret:%d, %d@%s\n", ret, __LINE__, __FILE__);
	}
	return ret;
}

int getAlert(alertResponse *response) {
	int ret = 0;
	dataGetPkg pkg;

	pkg.count = 0;
	pkg.ctrl = CTRL_GET_ALERT;
	pkg.header = PKG_HEADER;
	pkg.req_addr = 0;
	pkg.checksum = 0xaa000000 + pkg.header + pkg.ctrl + pkg.req_addr + pkg.count;

	//TODO retry?
	ret = sendPkgAndGetRes(CTRL_GET_ALERT, &pkg, response);
	if (ret < 0) {
		printf("get data failed, ret:%d, %d@%s\n", ret, __LINE__, __FILE__);
	}

	return ret;
}

int clearAlert() {
	int ret = 0;
	dataSetPkg pkg;
	dataSetResponse response;

	pkg.count = 0;
	pkg.ctrl = CTRL_CLR_ALERT;
	pkg.header = PKG_HEADER;
	pkg.req_addr = 0;
	pkg.checksum = 0xaa000000 + pkg.header + pkg.ctrl + pkg.req_addr + pkg.count;

	//TODO retry?
	ret = sendPkgAndGetRes(CTRL_CLR_ALERT, &pkg, &response);
	if (ret < 0) {
		printf("get data failed, ret:%d, %d@%s\n", ret, __LINE__, __FILE__);
	}

	return ret;
}

int setParam(UINT16 reg, UINT32 value) {
	int ret = 0;
	dataSetPkg pkg;
	dataGetResponse response;

	pkg.count = 1;
	pkg.ctrl = CTRL_SET_DATA;
	pkg.header = PKG_HEADER;
	pkg.req_addr = reg;
	pkg.value = value;
	pkg.checksum = 0xaa000000 + pkg.header + pkg.ctrl + pkg.req_addr + pkg.count;

	//TODO retry
	ret = sendPkgAndGetRes(CTRL_SET_DATA, &pkg, &response);
	if (ret >= 0) {
		if (response.ctrl == SUCC_SET_DATA) {

		} else {

		}
	} else {
		printf("get data failed, ret:%d, %d@%s\n", ret, __LINE__, __FILE__);
	}
	return ret;
}
