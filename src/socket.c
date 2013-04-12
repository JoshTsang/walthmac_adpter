/*
 * socket.c
 *
 *  Created on: Apr 3, 2013
 *      Author: mee990
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "defines.h"
#include "error.h"
#include "typedef.h"
#include "socket.h"

#define MAX_BUF_SIZE 	 1024
#define SERVER_IP 		 "192.168.1.128"
#define MSG_SEND_PORT	 4001
#define MSG_RECV_PORT	 6000

int _sendPkgAndGetRes(UINT16 ctrl, void *data, void *response) {
	if (ctrl == CTRL_GET_DATA) {
		dataGetPkg *pkg = data;
//		printf("*******get data********\nheader:0x%x\nctrl:0x%x\nreg:0x%x\ncount:0x%x\nchecksum:0x%x\n--------------\n",
//				pkg->header, pkg->ctrl, pkg->req_addr, pkg->count, pkg->checksum);
	} else if(CTRL_GET_ALERT) {
		dataGetPkg *pkg = data;
//		printf("*******get alert********\nheader:0x%x\nctrl:0x%x\nreg:0x%x\ncount:0x%x\nchecksum:0x%x\n--------------\n",
//						pkg->header, pkg->ctrl, pkg->req_addr, pkg->count, pkg->checksum);
	}else {
		dataSetPkg *pkg = data;
//		printf("*******set data********\nheader:%d\nreg:%x\nval:%x\n--------------\n",
//						pkg->header, pkg->req_addr, pkg->value);
	}
	return 0;
}

int verifyGetResponse(dataGetResponse *res) {
//	printf("*******get data res********\nheader:0x%x\nctrl:0x%x\nreg:0x%x\ncount:0x%x\nvalue:0x%x\nchecksum:0x%x\n--------------\n",
//			res->header, res->ctrl, res->req_addr, res->count, res->value,
//			res->checksum);

	//TODO edian covert?
	if (res->ctrl != SUCC_GET_DATA) {
		return GET_DATA_FAILED;
	}
	return res->checksum
			== (res->header + res->ctrl + res->req_addr + res->count
					+ 0xaa000000) ? 0 : VERIFY_CHECKSUM_FAILED;
}

int verifySetResponse(dataSetResponse *res) {
//	printf("*******set data res********\nheader:0x%x\nctrl:0x%x\nreg:0x%x\ncount:0x%x\nchecksum:0x%x\n--------------\n",
//			res->header, res->ctrl, res->req_addr, res->count, res->checksum);
	if (res->ctrl != SUCC_SET_DATA) {
		printf("set failed, ctrl:%d, expect:%d", res->ctrl, SUCC_SET_DATA);
		return SET_DATA_FAILED;
	}

	return res->checksum
			== (res->header + res->ctrl + res->req_addr + res->count
					+ 0xaa000000) ? 0 : VERIFY_CHECKSUM_FAILED;
}

int verifyAlertResponse(alertResponse *pkg) {
//	printf("*********alert*************\n");
//	printf("header:0x%x\nctrl:0x%x\nregAddr:0x%x\ncount:0x%x\ntype:0x%x\ndate:%d\ntime:%d\nchecksum:0x%x\n",
//				pkg->header, pkg->ctrl, pkg->addr, pkg->count, pkg->type, pkg->date, pkg->time, pkg->checksum);
//	printf("-----------------------------\n");
	return pkg->checksum==(pkg->header + pkg->ctrl + pkg->addr + pkg->count + 0xaa000000)?0:(VERIFY_CHECKSUM_FAILED);
}

int set_sock_time(int fd, int read_sec, int write_sec) {
    struct timeval send_timeval;
    struct timeval recv_timeval;

    if(fd <= 0) return -1;

    send_timeval.tv_sec = write_sec<0?0:write_sec;
    send_timeval.tv_usec = 0;
    recv_timeval.tv_sec = read_sec<0?0:read_sec;
    recv_timeval.tv_usec = 0;

	if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &send_timeval,
			sizeof(send_timeval)) == -1) {
		return -1;
	}

	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &recv_timeval,
			sizeof(recv_timeval)) == -1) {
		return -1;
	}

    return 0;
}

int pkgEdianConvert(UINT16 ctrl, void *data) {
	if (ctrl==CTRL_GET_DATA) {
		dataGetPkg *pkg = data;

		pkg->checksum = htonl(pkg->checksum);
		pkg->count = htons(pkg->count);
		pkg->header = htons(pkg->header);
		pkg->ctrl = htons(pkg->ctrl);
		pkg->req_addr = htons(pkg->req_addr);
	} else {
		dataSetPkg *pkg = data;

		pkg->checksum = htonl(pkg->checksum);
		pkg->value = htonl(pkg->value);
		pkg->count = htons(pkg->count);
		pkg->header = htons(pkg->header);
		pkg->ctrl = htons(pkg->ctrl);
		pkg->req_addr = htons(pkg->req_addr);
	}

	return 0;
}

int resEdianConvert(UINT16 ctrl, void *data) {
	return 0;
}

int sendPkg(void *data, int pkgLen) {
	int sockfd, ret;
	unsigned int addrLen;
	struct sockaddr_in server_addr;

	addrLen = sizeof(server_addr);
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket error");
		return CONNECT_FAILED;
	}

	set_sock_time(sockfd, 30, 30);
	memset (&server_addr, 0, sizeof(struct sockaddr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(MSG_SEND_PORT) ;
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	//TODO remove this if edian covert is not needed on the router!!
	//edianConvert(ctrl, data);
	if (sendto(sockfd, data, pkgLen, 0, (struct sockaddr*)&server_addr, addrLen) < 0) {
		ret = SOCKET_TIMEOUT;
	}
	close(sockfd);
	return ret;

}

int getResponseLen(UINT16 ctrl) {
	int responseLen;

	switch (ctrl) {
	case CTRL_GET_ALERT:
		responseLen = sizeof(alertResponse);
		break;
	case CTRL_GET_DATA:
		responseLen = sizeof(dataGetResponse);
		break;
	case CTRL_SET_DATA:
	case CTRL_CLR_ALERT:
		responseLen = sizeof(dataSetResponse);
		break;
	default:
		responseLen = 0;
	}
	return responseLen;
}

int verivyResponse(UINT16 ctrl, void* response) {
	int ret;

	switch (ctrl) {
	case CTRL_GET_ALERT:
		ret = verifyAlertResponse(response);
		break;
	case CTRL_GET_DATA:
		ret = verifyGetResponse(response);
		break;
	case CTRL_SET_DATA:
	case CTRL_CLR_ALERT:
		ret = verifySetResponse(response);
		break;
	default:
		ret = UNKNOWN_CTRL;
	}
	return ret;
}

int recvPkg(UINT16 ctrl, char *buf, void *response) {
	int ret, sockfd, len, lenSum, responseLen;
	struct sockaddr_in addr;
	unsigned int addr_len;
	UINT16 *header;
	UINT16 *pkgctrl;

	responseLen = getResponseLen(ctrl);

	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))<0) {
		perror("error");
		return 0;
	}

	addr_len = sizeof(struct sockaddr_in);

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(MSG_RECV_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("connect");
		return CONNECT_FAILED;
	}

	set_sock_time(sockfd, 30, 30);
	bzero(buf, MAX_BUF_SIZE);
	len = 0;
	lenSum = 0;
	while (1) {
		len = recvfrom (sockfd, buf+lenSum, MAX_BUF_SIZE, 0, (struct sockaddr*)&addr, &addr_len);
		if (len < 0) {
			close(sockfd);
			return SOCKET_TIMEOUT;
		} else {
			lenSum += len;
		}

		if (lenSum <= 8) {
			header = (UINT16 *)buf;
			pkgctrl = (UINT16 *)(buf + 2);
			if (*header == 0x4001) {

			} else {
				printf("err!header:%x, ctrl:%x\n", *header, *pkgctrl);
				lenSum = 0;
			}
		} else if(lenSum == responseLen)  {
			header = (UINT16 *)buf;
			pkgctrl = (UINT16 *)(buf + 2);
			if (*header == 0x4001) {
				break;
			} else {
				printf("err!header:%x, ctrl:%x\n", *header, *pkgctrl);
				lenSum = 0;
			}
		} else if (lenSum > responseLen){
			lenSum = 0;
			bzero(buf, MAX_BUF_SIZE);
			printf("overflow\n");
		}
	}

	if (lenSum == responseLen) {
		//TODO edian convert?
		memcpy(response, buf, responseLen);
		ret = verivyResponse(ctrl, response);
	} else {
		printf("recv:%d bytes,expect:%d bytes\n", lenSum, responseLen);
		ret = UNEXPECTED_RES_LEN;
	}

	close(sockfd);
	return ret;
}

int getPkgLen(UINT16 ctrl) {
	int pkgLen;

	switch (ctrl) {
	case CTRL_GET_DATA:
	case CTRL_GET_ALERT:
		pkgLen = sizeof(dataGetPkg);
		break;
	case CTRL_SET_DATA:
	case CTRL_CLR_ALERT:
		pkgLen = sizeof(dataSetPkg);
		break;
	default:
		pkgLen = UNKNOWN_CTRL;
	}
	return pkgLen;
}

int dprintSendPkg(UINT16 ctrl, void *data) {
	dataGetPkg *getPkg = data;
	dataSetPkg *setPkg = data;
	switch (ctrl) {
	case CTRL_GET_DATA:
	case CTRL_GET_ALERT:
		printf("*******get********\nheader:0x%x\nctrl:0x%x\nreg:0x%x\ncount:0x%x\nchecksum:0x%x\n--------------\n",
				getPkg->header, getPkg->ctrl, getPkg->req_addr, getPkg->count, getPkg->checksum);
		break;
	case CTRL_SET_DATA:
	case CTRL_CLR_ALERT:
		printf("*******set********\nheader:0x%x\nctrl:0x%x\nreg:0x%x\ncount:0x%x\nchecksum:0x%x\n--------------\n",
				setPkg->header, setPkg->ctrl, setPkg->req_addr, setPkg->count, setPkg->checksum);
		break;
	default:
		break;
	}
	return 0;
}

int dprintRecvPkg(UINT16 ctrl, void *data) {
	dataGetResponse *getRes = data;
	dataSetResponse *setRes = data;
	alertResponse *alertRes = data;

	switch (ctrl) {
	case CTRL_GET_DATA:
		printf("*******get res********\nheader:0x%x\nctrl:0x%x\nreg:0x%x\ncount:0x%x\nvalue:0x%x\nchecksum:0x%x\n--------------\n",
				getRes->header, getRes->ctrl, getRes->req_addr, getRes->count, getRes->value, getRes->checksum);
		break;
	case CTRL_CLR_ALERT:
	case CTRL_SET_DATA:
		printf("*******set res********\nheader:0x%x\nctrl:0x%x\nreg:0x%x\ncount:0x%x\nchecksum:0x%x\n--------------\n",
				setRes->header, setRes->ctrl, setRes->req_addr, setRes->count, setRes->checksum);
		break;
	case CTRL_GET_ALERT:
		printf("*******alert res********\nheader:0x%x\nctrl:0x%x\ntype:0x%x\ncount:0x%x\nchecksum:0x%x\n--------------\n",
				alertRes->header, alertRes->ctrl, alertRes->type, alertRes->count, alertRes->checksum);
		break;
	default:
		break;
	}
	return 0;
}

int sendPkgAndGetRes(UINT16 ctrl, void *data, void *response) {
	int ret = 0;
	char buf[MAX_BUF_SIZE];
	int pkgLen;

	_sendPkgAndGetRes(ctrl, data, response);

	pkgLen = getPkgLen(ctrl);

	sendPkg(data, pkgLen);
	ret = recvPkg(ctrl, buf, response);
	if (ret < 0) {
		dprintSendPkg(ctrl, data);
		dprintRecvPkg(ctrl, response);
	}
	return ret;
}


