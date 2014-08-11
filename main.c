#pragma config(Motor,  port1,           rightDrive,    tmotorVex393_HBridge,	openLoop, reversed)
#pragma config(Motor,  port2,           claw,          tmotorVex393_MC29, 		openLoop)
#pragma config(Motor,  port3,           rightClawPivot,tmotorVex393_MC29, 		openLoop, reversed)
#pragma config(Motor,  port4,           leftClawPivot, tmotorVex393_MC29, 		openLoop)
#pragma config(Motor,  port5,           rightArmPivot, tmotorVex393_MC29, 		openLoop)
#pragma config(Motor,  port6,           leftArmPivot,  tmotorVex393_MC29, 		openLoop)
#pragma config(Motor,  port7,           rightRackLift, tmotorVex393_MC29, 		openLoop)
#pragma config(Motor,  port8,           leftRackLift,  tmotorVex393_MC29, 		openLoop)
#pragma config(Motor,  port9,           middleDrive,   tmotorVex393_MC29, 		openLoop)
#pragma config(Motor,  port10,          leftDrive,     tmotorVex393_HBridge,	openLoop)	
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Platform config
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(OFF) //OFF or Competition
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

// One joystick tank drive control. Also called arcade drive
void tank_drive(float x, float y)
{
	if(abs(x) > 5 || abs(y) > 5)
	{
		motor[rightDrive] = (x - y) / 2;
		motor[leftDrive] = (x + y) / 2;
	}
	else
	{
		motor[rightDrive] = 0;
		motor[leftDrive] = 0;
	}
}

//Two joystick h-drive control
void h_drive(float xLeftStick, float yLeftStick, float xRightStick, float yRightStick)
{
	if(abs(yRightStick) > 5)
	{
		//Directional Movement
		motor[rightDrive] = yRightStick;
		motor[leftDrive] = yRightStick;
	}
	else if(abs(xLeftStick) > 5)
	{
		//Turning
		motor[rightDrive] = xLeftStick;
		motor[leftDrive] = -xLeftStick;
	}
	else
	{
		motor[rightDrive] = 0;
		motor[leftDrive] = 0;	
	}
	
	//Middle
	if(abs(xRightStick) > 5)
	{
		motor[middleDrive] = xRightStick;
	}
	else
	{
		motor[middleDrive] = 0;
	}
	
}
// Lift for the claw arm
void drive_rack_lift(int speed)
{
	motor[rightRackLift] = speed;
	motor[leftRackLift] = -speed;
}

// Drive the lift down
void rack_lift_down()
{
	drive_rack_lift(-127);
}

// Drive the lift up
void rack_lift_up()
{
	drive_rack_lift(127);
}

// Stop the lift
void rack_lift_stop()
{
	drive_rack_lift(0);
}

void arm_pivot_drive(int speed)
{
	motor[rightArmPivot] = speed;
	motor[leftArmPivot] = speed;
}

void arm_pivot_up()
{
	arm_pivot_drive(64);
}

void arm_pivot_down()
{
	arm_pivot_drive(-64);
}

void arm_pivot_stop()
{
	arm_pivot_drive(0);
}

void claw_drive(int speed)
{
	motor[claw] = speed;
}

void claw_open()
{
	claw_drive(64);
}

void claw_close()
{
	claw_drive(-64);
}

void claw_stop()
{
	claw_drive(0);
}

void claw_pivot_up()
{
	motor[rightClawPivot] = 60;
	motor[leftClawPivot] = 60;
}

void claw_pivot_down()
{
	motor[rightClawPivot] = -60;
	motor[leftClawPivot] = -60;
}

void claw_pivot_stop()
{
	motor[rightClawPivot] = 0;
	motor[leftClawPivot] = 0;
}

// All init functions and definitions go in here
void pre_auton()
{
}

// All functions for fully autonomous control of robot go here
task autonomous()
{
	//AutonomousCodePlaceholderForTesting();
}

// All functions for joystick-operated mode go here
task usercontrol()
{
	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
	motor[middleDrive] = 0;
	while(true)
	{
		int xRightStick = vexRT[Ch1];
		int yRightStick = vexRT[Ch2];
		int xLeftStick = vexRT[Ch4];
		int yLeftStick = vexRT[Ch3];

		bool bRackLiftDown = vexRT[Btn6D];
		bool bRackLiftUp = vexRT[Btn6U];

		bool bArmPivotUp = vexRT[Btn8U];
		bool bArmPivotDown = vexRT[Btn8D];

		bool bClawOpen = vexRT[Btn5D];
		bool bClawClose = vexRT[Btn5U];

		bool bClawPivotUp = vexRT[Btn7U];
		bool bClawPivotDown = vexRT[Btn7D];

		//tank_drive(xRightStick, yRightStick);
		h_drive(xLeftStick, yLeftStick, xRightStick, yRightStick);

		if(bRackLiftUp)
			rack_lift_up();
		else if(bRackLiftDown)
			rack_lift_down();
		else if(bArmPivotUp)
			arm_pivot_up();
		else if(bArmPivotDown)
			arm_pivot_down();
		else if(bClawOpen)
			claw_open();
		else if(bClawClose)
			claw_close();
		else if(bClawPivotUp)
			claw_pivot_up();
		else if(bClawPivotDown)
			claw_pivot_down();

		if(!bRackLiftUp && !bRackLiftDown)
			rack_lift_stop();

		if(!bArmPivotUp && !bArmPivotDown)
			arm_pivot_stop();

		if(!bClawOpen && !bClawClose)
			claw_stop();

		if(!bClawPivotUp && !bClawPivotDown)
			claw_pivot_stop();

		motor[middleDrive] = xLeftStick;
	}
}
