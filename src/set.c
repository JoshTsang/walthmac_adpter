/*
 * set.c
 *
 *  Created on: Apr 9, 2013
 *      Author: mee990
 */

#include <stdio.h>
#include <string.h>

#include "typedef.h"
#include "defines.h"
#include "request.h"
#include "values.h"
#include "socket.h"

value* findArgById(char *id) {
	int i = 0;

	while(args[i].id != NULL) {
		if (strcmp(id, args[i].id) == 0) {
			return &args[i];
		}

		i++;
	}

	return NULL;
}

int set(char *id, UINT32 val) {
	int ret = 0;
	value *arg;

	arg = findArgById(id);
	if (arg != NULL) {
		arg->value = val;
		ret = setParam(arg->addr, arg->value);
	} else {
		ret = -1;
	}

	return ret;
}
