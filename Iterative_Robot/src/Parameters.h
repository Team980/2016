#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

//pwm channels
#define leftSideMotorsCh 0
#define rightSideMotorsCh 1

//dio channels
#define photoSwitchCh 0
#define leftDriveEncA 1
#define leftDriveEncB 2
#define rightDriveEncA 3
#define rightDriveEncB 4

//can IDs
#define rollerMotorId 1
#define armMotorId 2

//analog channels
#define potCh 3

//usb channels
#define driveJsCh 0
#define controlJsCh 1

//joystick channels
#define rollerIn 1
#define rollerStop 2
#define rollerOut 3
#define armDown 6
#define armFlat 7
#define armUp 8

//control joystick settings
#define rollerInSpeed 0.5
#define rollerStopSpeed 0.0
#define rollerOutSpeed -0.5

//potentiometer set points (all in volts)
#define armDownPosition 0.0
#define armFlatPosition 0.38
#define armUpPosition 1.45

//potentiometer PID values
#define potP 3.0
#define potI 0.0
#define potD 0.0
#define potMinVolt 0.0
#define potMaxVolt 5.0
#define potTol 10.0

//drive parameters
#define maxOutputDriveFrac 0.4 //limit the drive motor output to this fraction of the total possible
#define wheelRadius 4.0 //inches
#define driveEncoderCounts 1024.0

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
