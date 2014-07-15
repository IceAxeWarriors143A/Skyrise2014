#pragma config(Motor,    port1,    leftWheels, tmotorNormal, openLoop, reversed)
#pragma config(Motor,    port2,    rightWheels, tmotorNormal, openLoop)
#pragma config(Motor,    port3,    middleWheel, tmotorNormal, openLoop)

int rightx;
int leftx;
int righty;
int lefty;

task main
{
    rightx = vexRT[1];
    righty = vexRT[1];
    leftx = vexRT[4];
    lefty = vexRT[3];
    motor[leftWheels] = (leftx + righty)/2;
    motor[rightWheels] = (-leftx + righty)/2;
    motor[middleWheel] = rightx;
}
