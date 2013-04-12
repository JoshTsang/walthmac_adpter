#include <stdio.h>
#include <string.h>

#include "typedef.h"
#include "defines.h"
#include "request.h"
#include "socket.h"
#include "values.h"

#define VALUE_JSON_BUF_SIZE 1024

int getValues(value *valArr);
int getArgsValue();
int getStatusValue();
int value2json(value *p, char *buf);
int jsonEncode(value *val, char *buf, int bufSize);

int getArgsJson(char *jsonBuf, int bufSize) {
	int ret = getArgsValue();
	if (ret >= 0) {
		ret = jsonEncode(args, jsonBuf, bufSize);
	}

	return ret;
}

int getStatusJson(char *jsonBuf, int bufSize) {
	int ret = getStatusValue();
	if (ret >= 0) {
		ret = jsonEncode(status, jsonBuf, bufSize);
	}

	return ret;
}

int getArgsValue() {
	int ret = 0;

	ret = getValues(args);
	return ret;
}

int getStatusValue() {
	int ret = 0;

	ret = getValues(status);
	return ret;
}

int saveAlert(alertResponse *alert) {
	printf("*******alert res********\nheader:0x%x\nctrl:0x%x\ntype:0x%x\ncount:0x%x\nchecksum:0x%x\n--------------\n",
			alert->header, alert->ctrl, alert->type, alert->count, alert->checksum);
	return 0;
}
int getAlerts() {
	int ret = 0;
	alertResponse alertRes;

	while(1) {
		bzero(&alertRes, sizeof(alertResponse));
		ret = getAlert(&alertRes);
		if (ret < 0) {
			dprintRecvPkg(CTRL_GET_ALERT, &alertRes);
			return ret;
		} else {
			if (alertRes.type == 0) {
				return 0;
			} else {
				ret = saveAlert(&alertRes);
				if (ret < 0) {
					return ret;
				}
				ret = clearAlert();
				if (ret < 0) {

				}
			}
		}
	}
}

int getValues(value *valArr) {
	int ret = 0;
	UINT32 valueTmp;

	int i = 0;

	while (valArr[i].id != NULL) {
		ret = getData(valArr[i].addr, &valueTmp);
		if (ret >= 0) {
			valArr[i].value = valueTmp;
		} else {
			//TODO retry?
		}
		i++;
	}

	return ret;
}

int jsonEncode(value *val, char *buf, int bufSize) {
	int ret = 0;
	char valueJsonBuf[VALUE_JSON_BUF_SIZE];
	char *p = buf;

	memset(p, 0, bufSize);
	strcpy(p, "[");

	int i = 0;
	while (val[i].id != NULL) {
		p += strlen(p);
		ret = value2json(&val[i], valueJsonBuf);
		if (ret >= 0) {
			if (strlen(valueJsonBuf)+(p-buf) >= bufSize) {
				//TODO define err code -- overflow
				return -1;
			} else {
				strcat(p, valueJsonBuf);
			}

			if (val[i+1].id != NULL) {
				strcat(p, ",");
			}
		} else {
			//TODO handle fail
		}

		i++;
	}

	strcat(p, "]");

	return ret;
}

int value2json(value *p, char *buf) {
	memset(buf, 0, VALUE_JSON_BUF_SIZE);

	sprintf(buf, "{\"id\":\"%s\",\"value\":%u}", p->id, p->value);
	return 0;
}

int save(char *json, char *path) {
	return 0;
}
