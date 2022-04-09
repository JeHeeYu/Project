/*
 * motor.c
 *
 *  Created on: Mar 12, 2022
 *      Author: sees1
 */

#include "main.h"
#include "common.h"
#include "motor.h"
#include "debug.h"



/*************Wheel Description************************************
 *
 * FR : FRONT_IN_1_Pin, FRONT_IN_2_Pin
 * FL : FRONT_IN_3_Pin, FRONT_IN_4_Pin
 * BR : BACK_IN_3_Pin, BACK_IN_4_Pin
 * BL : BACK_IN_1_Pin, BACK_IN_2_Pin
 *
 * Direction of Movement	FL		 FR		   BL		BR
 *		  Straight		 Forward   Forward   Forward  Forward
 *		  Back	    	 Backward  Backward  Backward Backward
 *	      Left 			 Backward  Forward	 Forward  Backward
 *		  Right			 Forward   Backward	 Backward Forward
 *		Upper Right		 Forward      -	        -     Forward
 *		Upper Left		    -      Forward	 Forward     -
 *		Bottom Right	    -      Backward  Backward    -
 *		Bottom Left		 Backward     -	        -     Backward
 *****************************************************************/

void MotorControl(uint8_t data)
{
	if(data == STRAIGHT)
	{
		Straight();
	}
	else if(data == UPPERLIGHT)
	{
		UpperRight();
	}
	else if(data == UPPERLEFT)
	{
		UpperLeft();
	}
	else
	{
		Stop();
	}
}

void Straight()
{
	MotorOn(GPIOA, BACK_IN_1_Pin, BACK_IN_2_Pin);
	MotorOn(GPIOC, BACK_IN_3_Pin, BACK_IN_4_Pin);

	MotorOn(GPIOB, FRONT_IN_2_Pin, FRONT_IN_1_Pin);
	MotorOn(GPIOA, FRONT_IN_3_Pin, FRONT_IN_4_Pin);
	HAL_Delay(100);
}

void Stop()
{
	MotorOff(GPIOA, BACK_IN_1_Pin, BACK_IN_2_Pin);
	MotorOff(GPIOC, BACK_IN_3_Pin, BACK_IN_4_Pin);

	MotorOff(GPIOB, FRONT_IN_2_Pin, FRONT_IN_1_Pin);
	MotorOff(GPIOA, FRONT_IN_3_Pin, FRONT_IN_4_Pin);
	HAL_Delay(100);
}

void UpperLeft()
{
	MotorOff(GPIOC, BACK_IN_3_Pin, BACK_IN_4_Pin);
	MotorOff(GPIOA, FRONT_IN_3_Pin, FRONT_IN_4_Pin);

	MotorOn(GPIOA, FRONT_IN_2_Pin, FRONT_IN_1_Pin);
	MotorOn(GPIOC, BACK_IN_1_Pin, BACK_IN_2_Pin);
	HAL_Delay(100);
}

void UpperRight()
{
	MotorOff(GPIOA, BACK_IN_1_Pin, BACK_IN_2_Pin);
	MotorOff(GPIOA, FRONT_IN_3_Pin, FRONT_IN_4_Pin);

	MotorOn(GPIOC, BACK_IN_3_Pin, BACK_IN_4_Pin);
	MotorOn(GPIOA, FRONT_IN_3_Pin, FRONT_IN_4_Pin);
	HAL_Delay(100);
}

void Right()
{

}

void Left()
{

}

void MotorOn(GPIO_TypeDef* port, uint16_t pinA, uint16_t pinB)
{
	HAL_GPIO_WritePin(port, pinA, LOW);
	HAL_GPIO_WritePin(port, pinB, HIGH);
	HAL_Delay(100);
}

void MotorOff(GPIO_TypeDef* port, uint16_t pinA, uint16_t pinB)
{
	HAL_GPIO_WritePin(port, pinA, LOW);
	HAL_GPIO_WritePin(port, pinB, LOW);
	HAL_Delay(100);
}
