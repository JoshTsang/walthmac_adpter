/*
 * defines.h
 *
 *  Created on: Apr 3, 2013
 *      Author: mee990
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define PKG_HEADER    	  0x4001

// Ctrl command
#define CTRL_GET_DATA 	  0xaaa5
#define CTRL_SET_DATA	  0xaaaa
#define CTRL_GET_ALERT    0xaaab
#define CTRL_CLR_ALERT	  0xaabb

//Error
#define SUCC_GET_DATA 	  0xaaa5
#define FAIL_GET_DATA 	  0x55a5
#define SUCC_ALERT	  	  0xaaab
#define FAIL_ALERT    	  0x55ab
#define SUCC_SET_DATA 	  0xaaaa
#define FAIL_SET_DATA 	  0x55aa

#endif /* DEFINES_H_ */
