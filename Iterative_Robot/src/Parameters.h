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
#define rollerMotorId 10
#define armMotorId 13
#endif

//analog channels
#if robotConfig == robot2016
#define potCh 0
#elif robotConfig == robot2015
#define potCh 0
#endif

//usb channels
#define driveJsCh 0
#define controlJsCh 1

//control joystick channels
#define rollerIn 3
#define rollerStop 1
#define rollerOut 2
#define armDown 8
#define armFlat 7
#define armUp 6

//drive joystick channels
#define highSpeedMode 1

//control joystick settings
#define rollerInSpeed 0.8
#define rollerStopSpeed 0.0
#define rollerOutSpeed -1.0

//Arm invert state
#if robotConfig == robot2016
#define rollerInvState -1.0  // -1 to invert; 1 to not invert
#elif robotConfig == robot2015
#define rollerInvState -1.0
#endif

//potentiometer set points (all in volts)
#if robotConfig == robot2016
#define armFlatPosition 1.11
#define armDownPosition armFlatPosition
#define armUpPosition 0.1
#elif robotConfig == robot2015
#define armFlatPosition 0.38
#define armDownPosition armFlatPosition
#define armUpPosition 1.45
#endif

//potentiometer PID values
#define potMinVolt 0.0
#define potMaxVolt 5.0
#define potTol 1.0 //percent
//
#if robotConfig == robot2016
#define potP -0.4
#define potIAuto 0.0
#define potITeleop -0.01
#define potD 0.0
#elif robotConfig == robot2015
#define potP -0.2
#define potIAuto 0.0
#define potITeleop -0.005
#define potD 0.0
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

//camera system parameters
#define camViewAngle 49.0
#define vTargetWidth 20
#define fovPixWidth 320
#define fovPixHeight 240

//autonomous parameters
#define autoDistance 15.0 //in feet
#if robotConfig == robot2016
#define autoLeftSpeed 0.82 //normalized speed from -1 to 1
#define autoRightSpeed 0.9
#define autoSpeedInvert -1.0 // -1 to invert; 1 to not invert
#elif robotConfig == robot2015
#define autoLeftSpeed 0.9 //normalized speed from -1 to 1
#define autoRightSpeed 0.8
#define autoSpeedInvert -1.0 // -1 to invert; 1 to not invert
#endif

#endif /* _PARAMETERS_H_ */

