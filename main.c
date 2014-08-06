#pragma config(Motor,  port10,           right,         tmotorVex393, 			openLoop,		reversed)
#pragma config(Motor,  port2,           middle,        tmotorVex393_MC29, openLoop						)
#pragma config(Motor,  port3,           rightLift,     tmotorVex393_MC29, openLoop						)
#pragma config(Motor,  port4,           leftLift,      tmotorVex393_MC29, openLoop						)
#pragma config(Motor,  port1,          left,          tmotorVex393, 			openLoop						)
#pragma config(Motor,  port6,						clawLift1,					tmotorVex393_MC29, openLoop						)
#pragma config(Motor,		port7,					clawLift2,					tmotorVex393_MC29,	openLoop					)
#pragma config(Motor,		port5,					armRot1,					tmotorVex393_MC29,	openLoop,			)
#pragma config(Motor,		port8,					armRot2,					tmotorVex393_MC29,	openLoop,		reversed			)
#pragma config(Motor,		port9,					claw,					tmotorVex393_MC29,	openLoop			)



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
		motor[right] = (x - y) / 2;
		motor[left] = (x + y) / 2;
	}
}

// Lift for the claw arm
void drive_lift(int speed)
{
	if(abs(speed) > 5)
	{
		motor[rightLift] = speed;
		motor[leftLift] = -speed;
	}
}

// Drive the lift down
void lift_down()
{
	drive_lift(-127);
}

// Drive the lift up
void lift_up()
{
	drive_lift(127);
}

// Stop the lift
void lift_stop()
{
	drive_lift(0);
}

void claw_lift_drive(int speed)
{
	motor[clawLift1] = speed;
	motor[clawLift2] = speed;
}

void claw_lift_up()
{
	claw_lift_drive(64);
}

void claw_lift_down()
{
	claw_lift_drive(-64);
}

void claw_lift_stop()
{
	claw_lift_drive(0);
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

void arm_rotate(int speed)
{
	motor[armRot1] = speed;
	motor[armRot2] = speed;

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
	while(true)
	{
		int xSpeed = vexRT[Ch2];
		int ySpeed = vexRT[Ch1];
		int midSpeed = vexRT[Ch4];

		int armSpeed = vexRT[Ch3];

		bool bLiftDown = vexRT[Btn7D];
		bool bLiftUp = vexRT[Btn7U];

		bool bClawLiftUp = vexRT[Btn8U];
		bool bClawLiftDown = vexRT[Btn8D];

		bool bClawOpen = vexRT[Btn5D];
		bool bClawClose = vexRT[Btn5U];

		tank_drive(xSpeed, ySpeed);
		arm_rotate(-armSpeed);

		if(bLiftUp)
			lift_up();
		else if(bLiftDown)
			lift_down();
		else if(bClawLiftUp)
			claw_lift_up();
		else if(bClawLiftDown)
			claw_lift_down();
		else if(bClawOpen)
			claw_open();
		else if(bClawClose)
			claw_close();
			
		if(!bLiftUp && !bLiftDown)
			lift_stop();
			
		if(!bClawLiftUp && !bClawLiftDown)
			claw_lift_stop();
			
		if(!bClawOpen && !bClawClose)
			claw_stop();

		motor[middle] = midSpeed;
	}
}
