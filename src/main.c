/*
 * main.c
 *
 *  Created on: Apr 8, 2013
 *      Author: mee990
 */

#include "stdio.h"

#include "typedef.h"
#include "get.h"
#include "set.h"

#include "values.h"

#define JSON_BUF_SIZE (1024*4)

int isnumeric(char *str)
{
  while(*str)
  {
    if(!isdigit(*str))
      return 0;
    str++;
  }

  return 1;
}

UINT32 atoul(const char *nptr)
{
        int c;              /* current char */
        UINT32 total;         /* current total */
        int sign;           /* if '-', then negative, otherwise positive */

        /* skip whitespace */
        while (isspace((int)(unsigned char)*nptr))
            ++nptr;

        c = (int)(unsigned char)*nptr++;
        sign = c;           /* save sign indication */
        if (c == '-' || c == '+')
            c = (int)(unsigned char)*nptr++;    /* skip sign */

        total = 0;

        while (isdigit(c)) {
            total = 10 * total + (c - '0');     /* accumulate digit */
            c = (int)(unsigned char)*nptr++;    /* get next char */
        }

        return total;   /* return result, negated if necessary */
}
printDebugInfo(char *promote, value *val) {
	int i = 0;
	printf("*********%s********\n", promote);
	while (val[i].id != NULL) {
		printf("%s@0x%x:0x%x\n", val[i].id, val[i].addr, val[i].value);
		i++;
	}
	printf("---------------------\n");
}

int get() {
	int ret = 0;
	char jsonBuf[JSON_BUF_SIZE];

	ret = getArgsJson(jsonBuf, JSON_BUF_SIZE);
	if (ret >= 0) {
		printf("%s", jsonBuf);
	} else {
		printf("load args failed:%d\n", ret);
	}

	printDebugInfo("args", args);

	ret = getStatusJson(jsonBuf, JSON_BUF_SIZE);
	if (ret >= 0) {
		printf("%s", jsonBuf);
	} else {
		printf("load status failed:%d\n", ret);
	}
	printDebugInfo("status", status);

	ret = getAlerts();
	if (ret >= 0) {
		printf("getAlerts succ\n");
	} else {
		printf("load alerts failed:%d\n", ret);
	}

	return ret;
}

int setArg(char *id, char *value) {
	int ret = -1;
	if (isnumeric(value)) {
		ret = set(id, atoul(value));
	}

	return ret;
}

int _setTest() {
	int i = 0;

	setArg(args[0].id, "0");
	setArg(args[1].id, "1");
	setArg(args[2].id, "2");
	setArg(args[3].id, "3");
	setArg(args[4].id, "4");
	return 0;
	while (args[i].id != NULL) {
		setArg(args[i].id, "1");
		i++;
	}

	return 0;
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		int i = 1;
		for (;i<10000;i++) {
			printf("- %d ///////////////\n", i);
			get();
			sleep(2);
		}
		//_setTest();
	} else if (argc == 3) {
		setArg(argv[1], argv[2]);
	}

	return 0;
}
