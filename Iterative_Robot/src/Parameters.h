#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

//robot config
#define robot2015 0
#define robot2016 1
#define robotConfig robot2016

//pwm channels
#if robotConfig == robot2016
#define leftSideMotorsCh 0
#define rightSideMotorsCh 1
#elif robotConfig == robot2015
#define leftSideMotorsCh 8
#define rightSideMotorsCh 9
#endif

//dio channels
#if robotConfig == robot2016
#define photoSwitchCh 0
#define leftDriveEncA 1
#define leftDriveEncB 2
#define rightDriveEncA 3
#define rightDriveEncB 4
#elif robotConfig == robot2015
#define photoSwitchCh 0 //there is no photo switch but channel has to be defined
#define leftDriveEncA 9
#define leftDriveEncB 8
#define rightDriveEncA 7
#define rightDriveEncB 6
#endif

//can IDs
#if robotConfig == robot2016
#define rollerMotorId 1
#define armMotorId 2
#elif robotConfig == robot2015
#define rollerMotorId 13
#define armMotorId 10
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

//joystick channels
#define rollerIn 1
#define rollerStop 3
#define rollerOut 2
#define armDown 8
#define armFlat 7
#define armUp 6

//control joystick settings
#define rollerInSpeed 0.5
#define rollerStopSpeed 0.0
#define rollerOutSpeed -0.5

//potentiometer set points (all in volts)
#if robotConfig == robot2016
#define armDownPosition 0.0
#define armFlatPosition 0.38
#define armUpPosition 1.45
#elif robotConfig == robot2015
#define armDownPosition 0.0
#define armFlatPosition 0.38
#define armUpPosition 1.45
#endif

//potentiometer PID values
#define potMinVolt 0.0
#define potMaxVolt 5.0
#define potTol 10.0
//
#if robotConfig == robot2016
#define potP 3.0
#define potI 0.0
#define potD 0.0
#elif robotConfig == robot2015
#define potP 3.0
#define potI 0.0
#define potD 0.0
#endif


//drive parameters
#define driveEncoderCounts 1024.0
//
#if robotConfig == robot2016
#define maxOutputDriveFrac 0.6 //limit the drive motor output to this fraction of the total possible
#define wheelRadius 4.0 //inches
#elif robotConfig == robot2015
#define maxOutputDriveFrac 0.7 //limit the drive motor output to this fraction of the total possible
#define wheelRadius 2.0 //inches
#endif

//camera system parameters
#define camViewAngle 49.0
#define vTargetWidth 20
#define fovPixWidth 320
#define fovPixHeight 240

//autonomous parameters
#define autoLeftDistInvert 1.0 //-1.0 to invert, 1.0 not to invert
#define autoRightDistInvert -1.0 //-1.0 to invert, 1.0 not to invert
#define autoDistance 5.0 //in feet
#define autoSpeedInvert -1.0 //-1.0 to invert, 1.0 not to invert
#define autoSpeed (autoSpeedInvert*0.5) //normalized speed from -1 to 1
#define autoCurve NO_CURVE

#endif /* _PARAMETERS_H_ */
