#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

//pwm channels
#define leftSideMotorsCh 8
#define rightSideMotorsCh 9

//dio channels
#define leftDriveEncA 9
#define leftDriveEncB 8
#define rightDriveEncA 7
#define rightDriveEncB 6

//can IDs
#define rollerMotorId 13
#define armMotorId 10

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
#define wheelRadius 4.0 //in inches
#define driveEncoderCounts 1024.0 //counts per revolution

//drive PID values (same for both left and right drive)
#define driveP 2.0
#define driveI 0.0
#define driveD 0.0
#define drivePidMinOut -1.0
#define drivePidMaxOut 1.0


#endif /* _PARAMETERS_H_ */
