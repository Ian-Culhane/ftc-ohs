#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     touch,          sensorTouch)
#pragma config(Sensor, S3,     infrared,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorA,          motor_grip,    tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorB,          motor_L,       tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          motor_R,       tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motor_scissor, tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motor_E,       tmotorNone, openLoop)
// Code generated by 'ROBOTC' configuration wizard

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "typedefs.h"
#include "global vars.h"
#include "enums.h"
#include "structs.h"
#include "low-level functions.h"
#include "high-level functions.h"
#include "subroutines.h"


void initializeRobot()
{
	// Place code here to init servos to starting positions.
	// Sensors are auto-config'ed and setup by RobotC. They may need to stabilize.
	return;
}


task main()
{
	initializeRobot();
	waitForStart(); // Wait for the beginning of autonomous phase.

	while (true)
	{
		// Code.
	}
}
