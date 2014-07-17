#pragma config(Motor,    port1,    right, tmotorNormal, openLoop, reversed)
#pragma config(Motor,    port10,    left, tMotorNormal, openLoop)
#pragma config(Motor,		 port2,	 middle, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port3, rightLift, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port4, leftLift, tmotorVex393_MC29, openLoop)

void tankDrive(float x, float y)
{
		motor[right] = (x - y) / 2;
		motor[left] = (x + y) / 2;
}

void driveLift(int speed)
{
		motor[rightLift] = speed;
		motor[leftLift] = -speed;
}

task main()
{
	while(true)
	{
		float xSpeed = vexRT[Ch2];
		float ySpeed = vexRT[Ch1];

		tankDrive(xSpeed, ySpeed);

		if(vexRT[Btn5U])
			driveLift(127);
		else if(vexRT[Btn5D])
			driveLift(-127);
		else if(vexRT[Btn7L])
			driveLift(0);

		motor[middle] = vexRT[Ch4];
	}
}
