#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     infrared,       sensorI2CCustom)
#pragma config(Sensor, S3,     color,          sensorCOLORFULL)
#pragma config(Sensor, S4,     ultrasonic,     sensorSONAR)
#pragma config(Motor,  motorA,          motor_popcorn, tmotorNXT, openLoop)
#pragma config(Motor,  motorB,          motor_B,       tmotorNXT, openLoop)
#pragma config(Motor,  motorC,          motor_C,       tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motor_L,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motor_R,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motor_lift,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motor_G,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    servo_IR,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo_claw,           tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    servo_ramp,           tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo_D,              tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo_E,              tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo_F,              tServoNone)
// Code generated by the 'ROBOTC' configuration wizard.
#include "JoystickDriver.c"
#include "hitechnic-irseeker-v2.h"
#include "enums.h"
#include "typedefs.h"
#include "global vars.h"
#include "structs.h"
#include "low-level functions.h"
#include "high-level functions.h"
#include "subroutines.h"



void initializeRobot()
{
	// Sensors are config'ed and setup by RobotC (need to stabalize).

	Servo_SetSpeed(servo_IR, 10);		// maximum speed!
	Servo_SetSpeed(servo_claw, 10);		// maximum speed!
	Servo_SetSpeed(servo_ramp, 100);	// slowly update so ramp doesn't release.

	Servo_Rotate(servo_IR, g_IRServoExtended);		// will fold back up in tele-op
	Servo_Rotate(servo_claw, g_clawServoExtended);	// will be folded in tele-op
	Servo_Rotate(servo_ramp, g_rampServoDefault);	// stops ramp from deploying

	Motor_SetMaxSpeed(g_FullRegulatedPower);

	Motor_ResetEncoder(motor_L);
	Motor_ResetEncoder(motor_R);
	Motor_ResetEncoder(motor_lift);

	// Wait this long so the claw & IR servos get to update.
	// The ramp-release servo shouldn't move; the long update time
	// is to prevent sudden jerks that might release the ramp.
	// We don't need to wait for the IR sensor to stabalize since
	// the robot doesn't read from it until it's at the first column,
	// which should be ample time for RobotC to setup the sensor.
	Time_Wait(10);

	return;
}



task main()
{
	waitForStart();

	initializeRobot();



	// The amount of time the robot...

	// ...moves forward at an angle.
	const int forwardTimeA	= 150;
	// ...turns to line up perpendicular to the center rack.
	const int turnTimeB		= 40;
	// ...drives up to the peg before lifting the lift up.
	const int forwardTimeC	= 155;
	// ...lifts the claw to put a ring on (row 2).
	const int liftTimeF		= 79;
	// ...moves forward, putting the ring onto the peg.
	const int forwardTimeG	= 65;
	// ...lowers its lift to get rid of the ring.
	const int liftTimeH		= 55;
	// ...backs up and gets ready to go to a dispenser.
	const int backwardTimeI	= 300;

	// ...turns to face parallel to the walls.
	const int turnTimeJ		= 40;
	// ...moves forward to align itself with a dispenser.
	const int forwardTimeK	= 100;
	// ...turns to face the dispenser.
	const int turnTimeL		= 80;
	// ...moves forward to be under the dispenser.
	const int forwardTimeM	= 50;


	Move_Forward	(forwardTimeA, g_AccurateMotorPower);
	Turn_Right		(turnTimeB, g_AccurateMotorPower, g_AccurateMotorPower);
	Move_Forward	(forwardTimeC, g_AccurateMotorPower);
	Lift_Up			(liftTimeF, g_AccurateMotorPower);
	Move_Forward	(forwardTimeG, g_AccurateMotorPower);

	// Lift power is negative so that the lift goes DOWN, not UP.
	Lift_Down		(liftTimeH, g_AccurateMotorPower);
	Move_Backward	(backwardTimeI, g_AccurateMotorPower);

	// Turn power doesn't need to be negative (turns in-place).
	Turn_Right		(turnTimeJ, g_AccurateMotorPower, g_AccurateMotorPower);
	Move_Forward	(forwardTimeK, g_AccurateMotorPower);
	Turn_Right		(turnTimeL, g_AccurateMotorPower, g_AccurateMotorPower);
	Move_Forward	(forwardTimeM, g_AccurateMotorPower);


	while (true)
	{
		PlaySoundFile("moo.rso");
		while(bSoundActive == true)
		{
			Time_Wait(1);
		}
	}



}
