#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     infrared,       sensorI2CCustom)
#pragma config(Sensor, S3,     weight,         sensorHiTechnicTouchMux)
#pragma config(Sensor, S4,     touch,          sensorTouch)
#pragma config(Motor,  motorA,          motor_popcorn, tmotorNXT, openLoop, reversed)
#pragma config(Motor,  motorB,          motor_B,       tmotorNXT, openLoop)
#pragma config(Motor,  motorC,          motor_C,       tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motor_L,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motor_R,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motor_lift,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motor_G,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    servo_IR,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo_claw,           tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    servo_ramp,           tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
// Code generated by the 'ROBOTC' configuration wizard.
#include "JoystickDriver.c"
#include "hitechnic-irseeker-v2.h"
#include "typedefs.h"
#include "global vars.h"
#include "enums.h"
#include "structs.h"
#include "low-level functions.h"
#include "high-level functions.h"
#include "subroutines.h"



void initializeRobot()
{
	// Sensors are config'ed and setup by RobotC (need to stabalize).

	// The IR sensor needs this command (it seems like RobotC doesn't
	// initialize third-party sensors automatically.
	HTIRS2setDSPMode(infrared, g_IRsensorMode);

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
	// The IR signal strengh in all 5 directions.
	int IRdirA = 0;
	int IRdirB = 0;
	int IRdirC = 0;
	int IRdirD = 0;
	int IRdirE = 0;



	waitForStart();

	initializeRobot();



	// The amount of time the robot...
	const int turnTimeA 	= 40;
	const int forwardTimeA 	= 50;
	const int turnTimeB 	= 80;
	const int forwardTimeB 	= 30;
	const int liftTimeB 	= 60;
	const int forwardTimeC 	= 50;
	const int turnTimeD 	= 80;
	const int forwardTimeD 	= 30;
	const int liftTimeD 	= 60;
	const int forwardTimeE 	= 50;
	const int turnTimeF 	= 80;
	const int forwardTimeF 	= 30;
	const int liftTimeF 	= 60;


	Turn_Left(turnTimeA, 100, 100);
	Move_Forward(forwardTimeA, 100);
	Time_Wait(50);

	HTIRS2readAllDCStrength(infrared, IRdirA, IRdirB, IRdirC, IRdirD, IRdirE);

	if ( (IRdirA+IRdirB+IRdirC+IRdirD+IRdirE) > g_IRthreshold )
	{
		Turn_Left		(turnTimeB, g_AccurateMotorPower, g_AccurateMotorPower);
		Move_Forward	(forwardTimeB, g_AccurateMotorPower);
		Lift_Lift		(liftTimeB, g_AccurateMotorPower);
	}
	else
	{
		Move_Forward(ForwardTimeC, g_AccurateMotorPower);
		Time_Wait(50);
		HTIRS2readAllACStrength(infrared, IRdirA, IRdirB, IRdirC, IRdirD, IRdirE);
		if ( (IRdirA+IRdirB+IRdirC+IRdirD+IRdirE) > g_IRthreshold )
		{
			Turn_Left		(turnTimeD, g_AccurateMotorPower, g_AccurateMotorPower);
			Move_Forward	(forwardTimeD, g_AccurateMotorPower);
			Lift_Lift		(liftTimeD, g_AccurateMotorPower);
		}
		else
		{
			Move_Forward	(forwardTimeE, g_AccurateMotorPower);
			Turn_Left		(turnTimeF, g_AccurateMotorPower, g_AccurateMotorPower);
			Move_Forward	(forwardTimeF, g_AccurateMotorPower);
			Lift_Lift		(liftTimeF, g_AccurateMotorPower);
		}
	}



	while (true)
	{
		PlaySoundFile("moo.rso");
		while(bSoundActive == true)
		{
			Time_Wait(1);
		}
	}
}
