#include "WPILib.h"
#include "Parameters.h"
#include "Constants.h"

class Robot: public IterativeRobot
{
private:
	// declarations
	RobotDrive *myRobot; // robot drive system
	Joystick *driveStick;
	Encoder *leftDriveEnc;
	Encoder *rightDriveEnc;
	PIDController *leftDrivePid;
	PIDController *rightDrivePid;
	
	Joystick *controlStick;
	CANTalon *rollerMotor;

	//same joystick as the roller
	AnalogInput *armPot;
	CANTalon *armMotor;
	PIDController *armPid;

	void RobotInit()
	{
		//leftDrivePid->Enable();

		//rightDrivePid->Enable();

		armPid->SetSetpoint(armUpPosition);
		armPid->Enable();
	}

	void AutonomousInit()
	{
	}

	void AutonomousPeriodic()
	{
	}

	void TeleopInit()
	{
	}

	void TeleopPeriodic()
	{
		//drive
		myRobot->ArcadeDrive(driveStick, Joystick::kYAxis, driveStick, Joystick::kZAxis, true);

		//roller
		if (controlStick ->GetRawButton(rollerIn))
		{
			rollerMotor ->Set(rollerInSpeed);
		}
		else if (controlStick ->GetRawButton(rollerStop))
		{
			rollerMotor ->Set(rollerStopSpeed);
		}
		else if (controlStick ->GetRawButton(rollerOut))
		{
			rollerMotor ->Set(rollerOutSpeed);
		}

		//arm
		if (controlStick ->GetRawButton(armDown))
		{
			armPid->SetSetpoint(armDownPosition);
		}
		else if (controlStick ->GetRawButton(armFlat))
		{
			armPid->SetSetpoint(armFlatPosition);
		}
		else if (controlStick ->GetRawButton(armUp))
		{
			armPid->SetSetpoint(armUpPosition);
		}
	}

	void TestPeriodic()
	{
	}

public:
	Robot()
	{
		myRobot = new RobotDrive(leftSideMotorsCh,rightSideMotorsCh); //Constructor defaults to rear when using two drives
		myRobot->SetExpiration(0.1);
		myRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
		myRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
		
		driveStick = new Joystick(driveJsCh);

		leftDriveEnc = new Encoder(leftDriveEncA, leftDriveEncB);
		leftDriveEnc->SetDistancePerPulse((2*PI*(wheelRadius/INCHES_IN_FEET))/driveEncoderCounts);
		leftDriveEnc->SetPIDSourceType(PIDSourceType::kRate);

		rightDriveEnc = new Encoder(rightDriveEncA, rightDriveEncB);
		rightDriveEnc->SetDistancePerPulse((2*PI*(wheelRadius/INCHES_IN_FEET))/driveEncoderCounts);
		rightDriveEnc->SetPIDSourceType(PIDSourceType::kRate);

		//leftDrivePid = new PIDController(driveP, driveI, driveD, leftDriveEnc, ???);
		//leftDrivePid->SetOutputRange(drivePidMinOut, drivePidMaxOut);

		//rightDrivePid = new PIDController(driveP, driveI, driveD, rightDriveEnc, ???);
		//rightDrivePid->SetOutputRange(drivePidMinOut, drivePidMaxOut);

		controlStick = new Joystick(controlJsCh);

		rollerMotor = new CANTalon(rollerMotorId);

		armPot = new AnalogInput(potCh);

		armMotor = new CANTalon(armMotorId);

		armPid = new PIDController(potP, potI, potD, armPot, armMotor);
		armPid->SetInputRange(potMinVolt, potMaxVolt);
		armPid->SetTolerance(potTol);
	}

	~Robot()
	{
		delete myRobot;
		delete driveStick;
		delete leftDriveEnc;
		delete rightDriveEnc;
		//delete leftDrivePid;
		//delete rightDrivePid;
		delete controlStick;
		delete rollerMotor;
		delete armPot;
		delete armMotor;
		delete armPid;
	}
};

START_ROBOT_CLASS(Robot);
