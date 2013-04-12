/*
 * socket.h
 *
 *  Created on: Apr 3, 2013
 *      Author: mee990
 */

#ifndef SOCKET_H_
#define SOCKET_H_

typedef struct {
	UINT16 header;
	UINT16 ctrl;
	UINT16 req_addr;
	UINT16 count;
	UINT32 value;
	UINT32 checksum;
} dataSetPkg;

typedef struct {
	UINT16 header;
	UINT16 ctrl;
	UINT16 req_addr;
	UINT16 count;
	UINT32 checksum;
} dataGetPkg;

typedef struct {
	UINT16 header;
	UINT16 ctrl;
	UINT16 req_addr;
	UINT16 count;
	UINT32 checksum;
} dataSetResponse;

typedef struct {
	UINT16 header;
	UINT16 ctrl;
	UINT16 req_addr;
	UINT16 count;
	UINT32 value;
	UINT32 checksum;
} dataGetResponse;

typedef struct {
	UINT16 header;
	UINT16 ctrl;
	UINT16 addr;
	UINT16 count;
	UINT32 type;
	UINT32 date;
	UINT32 time;
	UINT32 checksum;
} alertResponse;

int sendPkgAndGetRes(UINT16 ctrl, void *data, void *response);
int dprintRecvPkg(UINT16 ctrl, void *data);

#endif /* SOCKET_H_ */
