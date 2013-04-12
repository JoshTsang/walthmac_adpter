/*
 * values.h
 *
 *  Created on: Apr 7, 2013
 *      Author: mee990
 */

#ifndef VALUES_H_
#define VALUES_H_

#include "defines.h"
#include "typedef.h"
#include "addr.h"

typedef struct _value{
	char *id;
	UINT32 value;
	UINT16 addr;
} value;

extern value args[];
extern value status[];

#endif /* VALUES_H_ */
