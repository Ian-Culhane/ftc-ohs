#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     touch,          sensorTouch)
#pragma config(Sensor, S3,     infrared_L,     sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     infrared_R,     sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          claw_L,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          claw_R,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          release_ramp,  tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motor_L,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motor_R,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motor_lift,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motor_G,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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
	// Sensors are auto-config'ed and setup by RobotC.
	// They may need to stabilize.
	return;
}


task main()
{
	initializeRobot();
	waitForStart();

	while (true)
	{
		Joystick_UpdateData();



		//----------SEMI-ENCAPSULATED VERSION A (BASIC)----------//

		// Get-axis-value is NOT encapsulated. Everything else is.

		int motorL = 0;
		int motorR = 0;

		if ( Joystick_Button(BUTTON_LB)==1 || Joystick_Button(BUTTON_RB)==1 )
		{
			motorL = -1 * joystick.joy1_y1 / 4;
			motorR = -1 * joystick.joy1_y2 / 4;

			if (motorL > 0)
			{
				motorL -= (motorL - 100);
			}
			if (motorR > 0)
			{
				motorR -= (motorR - 100);
			}
			if (motorL < 0)
			{
				motorL += (motorL + 100);
			}
			if (motorR < 0)
			{
				motorR += (motorR + 100);
			}
		}
		else
		{
			motorL = -1 * joystick.joy1_y1;
			motorR = -1 * joystick.joy1_y2;
		}

		Motor_SetPower( motor_L, motorL );
		Motor_SetPower( motor_R, motorR );



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



		//----------TEST OF DIRECTION PAD----------//

		//if ( Joystick_Direction()==DIRECTION_F )
		//{
		//	Motor_SetPower( motor_L, 75 );
		//	Motor_SetPower( motor_R, 75 );
		//	Time_Wait( 100 );
		//	Motor_Stop( motor_L );
		//	Motor_Stop( motor_R );
		//}



		//----------TEST OF BUTTON -> INT CONVERSION----------//

		// Go to `enums.h` and change "enum JoystickButton" from
		// 0# to # and see what happens (e.g., 01 to 1).

		//if ( Joystick_Button(BUTTON_A)==1 )
		//{
		//	Motor_SetPower( motor_L, 75 );
		//	Motor_SetPower( motor_R, 75 );
		//	Time_Wait( 100 );
		//	Motor_Stop( motor_L );
		//	Motor_Stop( motor_R );
		//}



		//----------SINGLE-JOYSTICK CONTROL CODE----------//

		//int powerL = 0;
		//int powerR = 0;

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

		if ( Joystick_Button(BUTTON_B)==1 )
		{
			Motor_SetPower( motor_lift, 100 );
			Time_Wait( 100 );
			Motor_Stop( motor_lift );
		}
		if ( Joystick_Button(BUTTON_A)==1 )
		{
			Motor_SetPower( motor_lift, -100 );
			Time_Wait( 100 );
			Motor_Stop( motor_lift );
		}



		//----------MOO TEST - TOP SECRET!----------//

		// Doesn't work yet. I do not know why (the .rso file exists).
		// Could use a while loop to delay, or call a different function.

		if ( Joystick_Button(BUTTON_X)==1 )
		{
			ClearSounds();
			nVolume = 4;
			PlaySoundFile("moo.rso");
		}



		//////////////////////////////////////////////////
		//                                              //
		//=========== FINAL DRAFT OF PROGRAM ===========//
		//                                              //
		//////////////////////////////////////////////////



	}
}
