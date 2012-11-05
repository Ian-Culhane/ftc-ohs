#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S2,     touch,          sensorTouch)
#pragma config(Sensor, S3,     weight,         sensorLightInactive)
#pragma config(Sensor, S4,     infrared,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          motor_A,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motor_B,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          release_ramp,  tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motor_L,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motor_R,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motor_lift,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motor_G,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servoIR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servoForce,           tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
// Code generated by the 'ROBOTC' configuration wizard.
#include "JoystickDriver.c"
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
	// Sensors are auto-config'ed and setup by RobotC.
	// They may need to stabilize.

	Motor_SetMaxSpeed(g_FullMotorPower);

	return;
}



task main()
{
	initializeRobot();

	// These will be used later and are declared here to save from having to
	// declare them every single loop.
	int powerL = 0;
	int powerR = 0;
	int powerLift = 0;

	waitForStart();

	while (true)
	{
		Joystick_UpdateData();



		//----------SEMI-ENCAPSULATED VERSION A (BASIC)----------//

		// Get-axis-value is NOT encapsulated. Everything else is.

		if ( Joystick_Button(BUTTON_LB)==1 || Joystick_Button(BUTTON_RB)==1 )
		{
			powerL = -1 * joystick.joy1_y1 / 4;
			powerR = -1 * joystick.joy1_y2 / 4;
		}
		else
		{
			powerL = -1 * joystick.joy1_y1;
			powerR = -1 * joystick.joy1_y2;
		}

		Motor_SetPower( motor_L, powerL );
		Motor_SetPower( motor_R, powerR );



		//----------SEMI-ENCAPSULATED VERSION B (BASIC)----------//

		// Buttons are NOT encapsulated. Everything else is.

		//if ( Joystick_Button(5)==1 || Joystick_Button(6)==1 )
		//{
		//	Motor_SetPower( motor_L, -1 * Joystick_Joystick(JOYSTICK_L, AXIS_Y) / 4 );
		//	Motor_SetPower( motor_R, -1 * Joystick_Joystick(JOYSTICK_R, AXIS_Y) / 4 );
		//}
		//else
		//{
		//	Motor_SetPower( motor_L, -1 * Joystick_Joystick(JOYSTICK_L, AXIS_Y) );
		//	Motor_SetPower( motor_R, -1 * Joystick_Joystick(JOYSTICK_R, AXIS_Y) );
		//}



		//----------ENCAPSULATED VERSION (BASIC)----------//

		//if ( Joystick_Button(BUTTON_LB)==1 || Joystick_Button(BUTTON_RB)==1 )
		//{
		//	Motor_SetPower( motor_L, -1 * Joystick_Joystick(JOYSTICK_L, AXIS_Y) / 4 );
		//	Motor_SetPower( motor_R, -1 * Joystick_Joystick(JOYSTICK_R, AXIS_Y) / 4 );
		//}
		//else
		//{
		//	Motor_SetPower( motor_L, -1 * Joystick_Joystick(JOYSTICK_L, AXIS_Y) );
		//	Motor_SetPower( motor_R, -1 * Joystick_Joystick(JOYSTICK_R, AXIS_Y) );
		//}



		//----------SINGLE-JOYSTICK CONTROL CODE----------//

		//int axisX = joystick.joy1_x1;	// this is low-level code
		//int axisY = joystick.joy1_y1;	// this is low-level code

		//int axisX = Joystick_Joystick(JOYSTICK_L, AXIS_X);
		//int axisY = Joystick_Joystick(JOYSTICK_L, AXIS_X);

		//int angle = radiansToDegrees( atan2(axisY,axisX) );	//standard (from theta=0)
		//int powerTotal = sqrt( axisX*axisX + axisY*axisY );	//Pythagorean theorem


		//if ( 0<angle && angle<=90 )	//Quadrant I
		//{
		//	powerL = powerTotal;
		//	powerR = powerTotal*angle/45 - powerTotal;	//I think
		//}
		//else if ( 90<angle && angle<=180 )	//Quadrant II
		//{
		//	powerL = (-1)*powerTotal*(angle-90)/45 + powerTotal;	//I think
		//	powerR = powerTotal;
		//}
		//else if ( -180<angle && angle<=-90 )	//Quadrant III
		//{
		//	powerL = (-1) * powerTotal;
		//	powerR = (-1) * powerTotal*(angle+180)/45 + powerTotal;	//I think
		//}
		//else if ( -90<angle && angle<=0 )	//Quadrant IV
		//{
		//	powerL = powerTotal*(angle+90)/45 - powerTotal;	//I think
		//	powerR = (-1) * powerTotal;
		//}

		//Motor_SetPower(motor_L, powerL);
		//Motor_SetPower(motor_R, powerR);



		//----------NON-PID LIFT ASSIGNMENTS----------//

		//if ( Joystick_Button(BUTTON_B)==1 && Joystick_Button(BUTTON_RT)==1 )
		//{
		//	Motor_SetPower( motor_lift, 25 );
		//	Time_Wait( 25 );
		//	Motor_Stop( motor_lift );
		//}
		if ( Joystick_Button(BUTTON_B)==1)
		//else
		{
			Motor_SetPower( motor_lift, 100 );
			Time_Wait( 25 );
			Motor_Stop( motor_lift );
		}

		//if ( Joystick_Button(BUTTON_A)==1 && Joystick_Button(BUTTON_RT)==1 )
		//{
		//	Motor_SetPower( motor_lift, -25 );
		//	Time_Wait( 25 );
		//	Motor_Stop( motor_lift );
		//}

		if ( Joystick_Button(BUTTON_A)==1)
		//else
		{
			Motor_SetPower( motor_lift, -100 );
			Time_Wait( 25 );
			Motor_Stop( motor_lift );
		}






			//////////////////////////////////////////////////
			//                                              //
			//=========== FINAL DRAFT OF PROGRAM ===========//
			//                                              //
			//////////////////////////////////////////////////




		// See if a direction is being pressed, then test for the direction.
		// This is inside an `if` statement to optimize speed (less checking).
		// `JoystickController` arguments are not passed to increase speed.

		//if ( Joystick_Direction() != DIRECTION_NONE )
		//{
		//	switch ( Joystick_Direction() )	//fall-through very intentional
		//	{
		//		case DIRECTION_F:
		//		case DIRECTION_FL:
		//		case DIRECTION_FR:
		//			sub_PutRingOn();
		//			break;
		//		case DIRECTION_B:
		//		case DIRECTION_BL:
		//		case DIRECTION_BR:
		//			sub_TakeRingOff();
		//			break;
		//	}
		//}



		// See if a button (no LB/LT/RB) is being pressed, then react.
		// This is inside an `if` statement to optimize speed (less checking).

		// The argument to this first `if` statement is a masked version
		// of the "bitmap" of buttons directly from the controller.

		// Everything other than the buttons used are masked off, to increase
		// processing speed (possibly, just speculation). Reasoning:
		// `&` compares all bits of the variables, so we might as well mask
		// everything we won't need, in case something irrelevant is pressed.

		// A `0` value means no buttons (that we are testing for) are pressed.
		// Directly using the struct since this is the only possible time to
		// use it, and this is very low-level anyways.
		//if( (g_ControllerMask & joystick.joy1_Buttons) != 0 )
		//{
		//	if ( Joystick_Button(BUTTON_Y)==true )
		//	{
		//		sub_LiftToTop();
		//	}
		//	if ( Joystick_Button(BUTTON_B)==true )
		//	{
		//		sub_LiftToMiddle();
		//	}
		//	if ( Joystick_Button(BUTTON_A)==true )
		//	{
		//		sub_LiftToBottom();
		//	}
		//	if ( Joystick_Button(BUTTON_X)==true )
		//	{
		//		if (	(Joystick_Button(BUTTON_JOYL)||
		//				 Joystick_Button(BUTTON_JOYR)) == true )
		//		{
		//			sub_DeployRamp();
		//		}
		//	}
		//}



		// L/R motor code. Only triggered when the left joystick returns a
		// value greater than the global threshold (`global vars.h`).

		// TODO

		// Logarithmic control probably won't be implemented anytime soon.
		//if ( joystick.joy1_y1||joystick.joy1_y2 > g_JoystickThreshold )
		//{
		//	;
		//}
		//else if ( joystick.joy1_y1||joystick.joy1_y2 < g_JoystickThreshold )
		//{
		//	;
		//}
		//Motor_SetPower(motor_L, powerL);
		//Motor_SetPower(motor_R, powerR);



		// The right joystick on Controller 1 controls the lift ("manual mode")
		// in addition to the Y/B/A buttons. Pressing RB divides the speed by 4.
		// Logarithmic control probably won't be implemented anytime soon.

		//if ( Joystick_Button(BUTTON_RB)==1 && Joystick_Button(BUTTON_X)==1 )
		//{
		//	powerLift = joystick.joy1_y2 / 4;
		//}
		//else if ( Joystick_Button(BUTTON_X)==1 )
		//{
		//	powerLift = joystick.joy1_y2;
		//}
		//Motor_SetPower(motor_lift, powerLift);



		// Input from CONTROLLER_2 will be processed last. Very low priority.



		// Flush the controller input buffer periodically (every 1/4 sec?)



	}
}
