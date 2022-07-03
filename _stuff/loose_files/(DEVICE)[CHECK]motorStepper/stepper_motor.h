/* -----------------------------------------------------------------------------
 * File:			stepper_motor.h
 * Module:			Stepper motor interface
 * Authors:			Fábio Cabral Pacheco
 * 					Leandro Schwarz
 * Version:			1.0
 * Last edition:	2015-03-10
 * -------------------------------------------------------------------------- */

#ifndef __STEPPER_MOTOR_H
#define __STEPPER_MOTOR_H 10

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "LS_defines.h"
#if __LS_DEFINES_H < 110
	#error Error 100 - The defintion file is outdated (LS_defines must be version 11.0 or greater).
#endif

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef enum stepperResult_t{
	STEPPER_OK = 1,
	STEPPER_PORTS_NOT_CONFIGURED,
	STEPPER_NOT_INITIALIZED,
	STEPPER_MODE_NOT_CONFIGURED,
	STEPPER_DIRECTION_NOT_CONFIGURED
} stepperResult_t;

typedef enum stepperMode_t{
	STEPPER_WAVE		= 0,
	STEPPER_FULL_STEP,
	STEPPER_HALF_STEP
} stepperMode_t;

typedef enum stepperDirection_t{
	STEPPER_CLOCKWISE			= 0,
	STEPPER_COUNTERCLOCKWISE
} stepperDirection_t;

typedef struct stepperConfiguration_t{
	volatile uint8 * stepperDDR;
	volatile uint8 * stepperPORT;
	uint8 stepperLsb:			3;
	uint8 position:				3;
	uint8 mode:					2;
	uint8 direction:			1;
	uint8 portConfigured:		1;
	uint8 directionConfigured:	1;
	uint8 modeConfigured:		1;
	uint8 initialized:			1;
	uint8 unusedBits:			3;
} stepperConfiguration_t;

// -----------------------------------------------------------------------------
// Macrofunctions --------------------------------------------------------------

#define attachStepper(object) volatile stepperConfiguration_t object = {.stepperDDR = NULL, .stepperPORT = NULL, .stepperLsb = 0, .position = 0, .mode = STEPPER_WAVE, .direction = STEPPER_CLOCKWISE, .portConfigured = FALSE, .modeConfigured = FALSE, .directionConfigured = FALSE, .initialized = FALSE, .unusedBits = 0}

// -----------------------------------------------------------------------------
// Functions declarations ------------------------------------------------------

stepperResult_t stepperResetConfiguration(volatile stepperConfiguration_t * motor);
stepperResult_t stepperSetPort(volatile stepperConfiguration_t * motor, volatile uint8 * ddr, volatile uint8 * port, uint8 lsb);
stepperResult_t stepperSetDirection(volatile stepperConfiguration_t * motor, stepperDirection_t direction);
stepperDirection_t stepperGetDirection(volatile stepperConfiguration_t * motor);
stepperResult_t stepperSetMode(volatile stepperConfiguration_t * motor, stepperMode_t mode);
stepperMode_t stepperGetMode(volatile stepperConfiguration_t * motor);
stepperResult_t stepperInit(volatile stepperConfiguration_t * motor);
stepperResult_t stepperMove(volatile stepperConfiguration_t * motor);

#endif