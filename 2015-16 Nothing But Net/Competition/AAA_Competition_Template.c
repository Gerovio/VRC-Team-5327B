#pragma config(Sensor, in1,    AnglePot,       sensorPotentiometer)
#pragma config(Sensor, in2,    BallSensorRamp, sensorLineFollower)
#pragma config(Sensor, in3,    BallSensorElevator, sensorLineFollower)
#pragma config(Sensor, in4,    BallSensorLauncher, sensorLineFollower)
#pragma config(Sensor, in5,    AccelX,         sensorAccelerometer)
#pragma config(Sensor, in6,    LLine,          sensorLineFollower)
#pragma config(Sensor, in7,    RLine,          sensorLineFollower)
#pragma config(Sensor, in8,    Gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  DirectionLED, sensorLEDtoVCC)
#pragma config(Sensor, dgtl5,  BallFinder1,    sensorSONAR_mm)
#pragma config(Sensor, dgtl7,  BallFinder2,    sensorSONAR_mm)
#pragma config(Sensor, dgtl9,  BallSensorLauncher, sensorSONAR_mm)
#pragma config(Sensor, dgtl11, BallSensorRamp2, sensorSONAR_mm)
#pragma config(Motor,  port10,           Intake,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           Out1,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           RFBase,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           LFBase,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port1,           Angle,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           Out2,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           RBBase,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LBBase,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           AutoLoader,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,          Elevator,      tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
BUILD DATE: 4/6/16
AUTHOR: JS
V4.1.2
*/

//VRC Specific pragmas below
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"
//VRC Specific pragmas above
//The following lines define each of the buttons and joysticks on the controller in more readable terms
#define X_Joy vexRT[Ch4]
#define Y_Joy vexRT[Ch3]
#define rot_Joy vexRT[Ch1]
#define inBtn vexRT[Btn6U]
#define outBtn vexRT[Btn6D]
#define launchFastBtn vexRT[Btn5D]
#define launchSlowBtn vexRT[Btn6D]
#define angleUpBtn vexRT[Btn7U]
#define angleDownBtn vexRT[Btn7D]
#define angleLongBtn vexRT[Btn8D]
#define angleShortBtn vexRT[Btn8U]
#define overrideBtn vexRT[Btn7R]
#define toggleSlowBtn vexRT[Btn7L]
#define autoLoaderManual vexRT[Ch2Xmtr2]
#define angleSetBtn vexRT[Btn8L]
#define launchHoldToggleBtn vexRT[Btn7UXmtr2]
#define autoIntakeToggleBtn vexRT[Btn7DXmtr2]
#define autoLoadInBtn vexRT[Btn7R]
#define autoLoadOutBtn vexRT[Btn7L]
#define directionToggleBtn vexRT[Btn8R]

//The following lines are explicitly for sound effects on the partner joystick
#define sfxShiftBtn 0
#define sfxGreetingBtn 0
#define sfxAnothaOneBtn 0
#define sfxFriendBtn 0
#define sfxPlsBtn 0
#define sfxEmergencyStopBtn 0

#define sfxShift2Btn 0
#define sfxAlpha2Btn 0

#define sfxGreeting2Btn 0
#define sfxAnothaOne2Btn 0
#define sfxFriend2Btn 0
#define sfxJohnCenaBtn 0

#define sfxYesBtn 0
#define sfxNoBtn 0
#define sfxGLBtn 0
#define sfxGGBtn 0

#define sfxExcuseBtn 0
#define sfxOkBtn 0
#define sfxPls2Btn 0
#define sfxThxBtn 0

#define sfxJeopardyBtn 0
#define sfxEmergencyStop2Btn 0

//These global variables are used to manage toggle and emergency stop functions
int emergenStop = false;
bool elevatorOn = false;
//bool launchHoldToggle = true;
bool autoIntakeToggle = false;
int robotDirection = 1;

int Auton_Drive_Array[4]; //Arrays that are used during autonomous in a manner similar to the motor array, contains: X, Y, Rot, and Duration
int Auton_Aim_Array[2]; //Contains: Absolute and Adjust
int Auton_Launch_Array[2]; //Contains: Ball Count and Adjust
int Auton_Intake_Array[1]; //Contains: Direction
int Auton_AutoLoad_Array[1]; //Contains: Direction

//Include statements to reference the other header files containing specific parts of the code
#include "CONSTANTS.h"
#include "General_Functions.h"
#include "Robot_Functions.h"
#include "Sfx.h"
#include "Always_Tasks.h"
#include "Autonomous_Tasks.h"
#include "DriverControl_Tasks.h"

//Define a handy (and fun to use) shortcut for launching, so that we can write "pew pew pew pew" to shoot
#define pew LauncherControl(1, 500)

//Include this file last, since it makes use of the pew reference defined above
#include "Autonomous_Skills_Routines.h"

//Predefined construct
void pre_auton()
{
	bStopTasksBetweenModes = true;
	SensorType[in8] = sensorNone; //Reset gyroscope at beginning of program
	wait1Msec(1000);
	SensorType[in8] = sensorGyro;
	wait1Msec(1000);
}

//Predefined construct
task autonomous
{
	//Start necessary Autonomous control tasks
	/*startTask(Auton_Aim);
	startTask(Auton_Drive);
	startTask(Auton_Intaking);
	startTask(Auton_Launch);*/
	startTask(Auton_AutoLoading);
	string routineName = "redAuton1"; //This line allows us to manually change the routine to be run easily and quickly
	startRoutine(routineName); //Begins the desired autonomous routine
}

//Predefined construct
task usercontrol()
{
	//Start necessary tasks for user control, including Always tasks which must never be turned off
	Always();
	startTask(Drive);
	startTask(Intaking);
	startTask(autoLoading);
	startTask(Launch);
	startTask(Aim);
	startTask(SoundEffects);
	startTask(EmergencyOverride);
	startTask(sfxOverride);
	startTask(LCD);
	wait1Msec(500);
	slaveMotor(Out2, Out1);
	while (true) //Keep this task going so that the Vex Competition system does not mistake the robot for disconnected
	{
		EndTimeSlice();
	}
}
