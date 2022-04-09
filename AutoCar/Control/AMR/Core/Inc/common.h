/*
 * common.h
 *
 *  Created on: Mar 12, 2022
 *      Author: sees1
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#define HIGH 			SET
#define LOW 			RESET
/*
#define STRAIGHT		'A'
#define BACK			'B'
#define RIGHT			'C'
#define LEFT			'D'
#define NONE			'Q'
*/
typedef enum
{
	STRAIGHT = 65,
	BACK,
	UPPERLIGHT,
	UPPERLEFT,
	RIGHT,
	LEFT,
	NONE = 199,
}drive_t;

#endif /* INC_COMMON_H_ */
