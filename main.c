#pragma config(Motor,  port1,           right,         tmotorVex393, 			openLoop,		reversed)
#pragma config(Motor,  port2,           middle,        tmotorVex393_MC29, openLoop						)
#pragma config(Motor,  port3,           rightLift,     tmotorVex393_MC29, openLoop						)
#pragma config(Motor,  port4,           leftLift,      tmotorVex393_MC29, openLoop						)
#pragma config(Motor,  port10,          left,          tmotorVex393, 			openLoop						)

// Platform config
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(10)
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

		bool bLiftDown = vexRT[Btn5D];
		bool bLiftUp = vexRT[Btn5U];
		bool bLiftStop = vexRT[Btn7L];

		tank_drive(xSpeed, ySpeed);

		if(bLiftUp)
			lift_up();
		else if(bLiftDown)
			lift_down();
		else if(bLiftStop)
			lift_stop();

		motor[middle] = midSpeed;
	}
}
