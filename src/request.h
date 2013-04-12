/*
 * request.h
 *
 *  Created on: Apr 7, 2013
 *      Author: mee990
 */

#ifndef REQUEST_H_
#define REQUEST_H_
#include "socket.h"

int getData(UINT16 reg, UINT32* value);
int setParam(UINT16 reg, UINT32 value);
int getAlert(alertResponse *response);
int clearAlert();

#endif /* REQUEST_H_ */
