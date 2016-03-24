#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

//robot config
#define robot2015 0
#define robot2016 1
#define robotConfig robot2016

//pwm channels
#if robotConfig == robot2016
#define leftSideMotorsCh 1
#define rightSideMotorsCh 0
#elif robotConfig == robot2015
#define leftSideMotorsCh 9
#define rightSideMotorsCh 8
#endif

//dio channels
#if robotConfig == robot2016
#define ballCapturedPhotoSwitchCh 0
#define leftDriveEncA 1
#define leftDriveEncB 2
#define rightDriveEncA 3
#define rightDriveEncB 4
#elif robotConfig == robot2015
#define ballCapturedPhotoSwitchCh 0
#define leftDriveEncA 7
#define leftDriveEncB 6
#define rightDriveEncA 9
#define rightDriveEncB 8
#endif

//can IDs
#if robotConfig == robot2016
#define rollerMotorId 1
#define armMotorId 2
#elif robotConfig == robot2015
#define rollerMotorId 13
#define armMotorId 10
#endif

//usb channels
#define driveJsCh 0
#define driveWheelCh 1
#define controlJsCh 2

//control joystick channels
#define rollerIn 3
#define rollerStop 1
#define rollerOut 2
#define armDown 7
#define armUp 6

//drive joystick channels
#define highSpeedMode 1

//control joystick settings
#define rollerInSpeed 0.8
#define rollerStopSpeed 0.0
#define rollerOutSpeed -1.0

//photoswitch settings
#if robotConfig == robot2016
#define photoSwitchBeamBroken false //state when the beam is broken
#elif robotConfig == robot2015
#define photoSwitchBeamBroken true
#endif

//Arm invert state
#if robotConfig == robot2016
#define rollerInvState -1.0  // -1 to invert; 1 to not invert
#elif robotConfig == robot2015
#define rollerInvState -1.0
#endif

//arm position set points (all in fractions of a full encoder rotation)
#if robotConfig == robot2016
#define armDownPosition -0.65
#define armUpPosition -0.54
#define armPidDisablePosition -0.6 //point on the way down to disable the arm pid
#elif robotConfig == robot2015
#define armDownPosition -1.65
#define armUpPosition -1.54
#define armPidDisablePosition -1.6 //point on the way down to disable the arm pid
#endif

//arm position PID controller
#define armPidMinNominal -0.0 //min and maxes are all in volts
#define armPidMaxNominal +0.0
#define armPidMinPeak -12.0
#define armPidMaxPeak +12.0
#define armPidAllowableErr 0.0 //same units are arm position set points
#if robotConfig == robot2016
#define armPidP 1.0
#define armPidIAuto 0.0
#define armPidITeleop 0.0006
#define armPidD 100.0
#define armPidInvert true //true to invert, false not to invert
#elif robotConfig == robot2015
#define armPidP 1.0
#define armPidIAuto 0.0
#define armPidITeleop 0.0006
#define armPidD 100.0
#define armPidInvert true //true to invert, false not to invert
#endif

//drive parameters
#define driveEncoderCounts 1024.0
//
#if robotConfig == robot2016
#define maxOutputDriveFracLow 0.85 //limit the drive motor output to this fraction of the total possible
#define maxOutputDriveFracHigh 1.0
#define wheelRadius 4.0 //inches
#define leftEncInv false
#define rightEncInv true
#elif robotConfig == robot2015
#define maxOutputDriveFracLow 0.7 //limit the drive motor output to this fraction of the total possible
#define maxOutputDriveFracHigh 1.0
#define wheelRadius 2.0 //inches
#define leftEncInv false
#define rightEncInv true
#endif

//autonomous parameters
#define autoDistance 15.0 //in feet
#if robotConfig == robot2016
#define autoLeftSpeed 0.8 //normalized speed from -1 to 1
#define autoRightSpeed 0.9
#define autoSpeedInvert -1.0 // -1 to invert; 1 to not invert
#elif robotConfig == robot2015
#define autoLeftSpeed 0.9 //normalized speed from -1 to 1
#define autoRightSpeed 0.8
#define autoSpeedInvert -1.0 // -1 to invert; 1 to not invert
#endif

#endif /* _PARAMETERS_H_ */
