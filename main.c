#pragma config(Motor,    port1,    leftWheels, tmotorNormal, openLoop, reversed)
#pragma config(Motor,    port2,    rightWheels, tmotorNormal, openLoop)
#pragma config(Motor,    port3,    middleWheel, tmotorNormal, openLoop)

int rightX;
int leftX;
int rightY;
int leftY;

task main
{
    rightX = vexRT[1];
    rightY = vexRT[1];
    leftX = vexRT[4];
    leftY = vexRT[3];
    motor[leftWheels] = (leftX + rightY)/2;
    motor[rightWheels] = (-leftX + rightY)/2;
    motor[middleWheel] = rightX;
}
