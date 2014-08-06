#pragma config(Motor,  port1,           right,         tmotorVex393, 			openLoop,		reversed)
#pragma config(Motor,  port2,           middle,        tmotorVex393_MC29, openLoop						)
#pragma config(Motor,  port3,           rightLift,     tmotorVex393_MC29, openLoop						)
#pragma config(Motor,  port4,           leftLift,      tmotorVex393_MC29, openLoop						)
#pragma config(Motor,  port10,          left,          tmotorVex393, 			openLoop						)
#pragma config(Motor,  port6,						claw1,					tmotorVex393_MC29, openLoop						)
#pragma config(Motor,		port7,					claw2,					tmotorVex393_MC29,	openLoop					)
#pragma config(Motor,		port5,					armRot1,					tmotorVex393_MC29,	openLoop,			)
#pragma config(Motor,		port8,					armRot2,					tmotorVex393_MC29,	openLoop,		reversed			)


// Platform config
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Off) //Off or Competition
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

// One joystick tank drive control. Also called arcade drive
void tank_drive(float x, float y)
{
	motor[right] = (x - y) / 2;
	motor[left] = (x + y) / 2;
}

// Lift for the claw arm
void drive_lift(int speed)
{
	motor[rightLift] = speed;
	motor[leftLift] = -speed;
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

void claw_drive(int speed)
{
	motor[claw1] = speed;
	motor[claw2] = speed;
}

void claw_up()
{
	claw_drive(64);
}

void claw_down()
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

		bool bLiftDown = vexRT[Btn5D];
		bool bLiftUp = vexRT[Btn5U];
		bool bLiftStop = vexRT[Btn7L];

		bool bClawUp = vexRT[Btn8U];
		bool bClawDown = vexRT[Btn8D];
		bool bClawStop = vexRT[Btn8L];

		tank_drive(xSpeed, ySpeed);
		arm_rotate(armSpeed);

		if(bLiftUp)
			lift_up();
		else if(bLiftDown)
			lift_down();
		else if(bLiftStop)
			lift_stop();
		else if(bClawUp)
			claw_up();
		else if(bClawDown)
			claw_down();
		else if(bClawStop)
			claw_stop();

		motor[middle] = midSpeed;
	}
}

