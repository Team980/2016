#include "WPILib.h"
#include "Parameters.h"
#include "Constants.h"
#include <math.h>

class Robot: public IterativeRobot
{
private:
	// declarations
	Talon *leftDriveSpeedController;
	Talon *rightDriveSpeedController;
	RobotDrive *myRobot; // robot drive system
	Joystick *driveStick;
	Encoder *leftDriveEnc;
	Encoder *rightDriveEnc;
	PIDController *leftDrivePid;
	PIDController *rightDrivePid;
	
	Joystick *controlStick;
	CANTalon *rollerMotor;
	DigitalInput *photoSwitch;
	bool rollerInOn;

	//same joystick as the roller
	AnalogInput *armPot;
	CANTalon *armMotor;
	PIDController *armPid;

	void RobotInit()
	{
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
		//leftDrivePid->Enable();

		//rightDrivePid->Enable();
	}

	void TeleopPeriodic()
	{
		//drive
		//myRobot->ArcadeDrive(driveStick, Joystick::kYAxis, driveStick, Joystick::kZAxis, true);
		std::cout << "leftDriveEnc: " << leftDriveEnc->GetRate() << std::endl;
		std::cout << "rightDriveEnc: " << rightDriveEnc->GetRate() << std::endl;
		//implement a deadband
		float yCommand = driveStick->GetY();
		if(fabs(yCommand) < 0.2)
			yCommand = 0;


		leftDriveSpeedController->Set(-1*drivePidMaxOut*yCommand);
		rightDriveSpeedController->Set(drivePidMaxOut*yCommand);
		//leftDrivePid->SetSetpoint(-1*drivePidMaxOut*driveStick->GetY());
		//rightDrivePid->SetSetpoint(drivePidMaxOut*driveStick->GetY());

		//roller
		if (controlStick ->GetRawButton(rollerIn))
		{
			rollerMotor ->Set(rollerInSpeed);
			rollerInOn = true;
		}
		else if (controlStick ->GetRawButton(rollerStop))
		{
			rollerMotor ->Set(rollerStopSpeed);
		}
		else if (controlStick ->GetRawButton(rollerOut))
		{
			rollerMotor ->Set(rollerOutSpeed);
		}

		if (photoSwitch ->Get()== false && rollerInOn)
		{
			rollerMotor ->Set(rollerStopSpeed);
			rollerInOn = false;
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
		leftDriveSpeedController = new Talon(leftSideMotorsCh);

		rightDriveSpeedController = new Talon(rightSideMotorsCh);

		myRobot = new RobotDrive(leftDriveSpeedController,rightDriveSpeedController); //Constructor defaults to rear when using two drives
		myRobot->SetExpiration(0.1);
		myRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
		myRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

		driveStick = new Joystick(driveJsCh);

		leftDriveEnc = new Encoder(leftDriveEncA, leftDriveEncB);
		leftDriveEnc->SetDistancePerPulse((2*PI*(wheelRadius/INCHES_IN_FEET))/driveEncoderCounts);
		leftDriveEnc->SetPIDSourceType(PIDSourceType::kRate);
		leftDriveEnc->Reset();

		rightDriveEnc = new Encoder(rightDriveEncA, rightDriveEncB);
		rightDriveEnc->SetDistancePerPulse((2*PI*(wheelRadius/INCHES_IN_FEET))/driveEncoderCounts);
		rightDriveEnc->SetPIDSourceType(PIDSourceType::kRate);
		rightDriveEnc->Reset();

		leftDrivePid = new PIDController(driveP, driveI, driveD, leftDriveEnc, leftDriveSpeedController);
		leftDrivePid->SetOutputRange(drivePidMinOut, drivePidMaxOut);
		leftDrivePid->SetContinuous();

		rightDrivePid = new PIDController(driveP, driveI, driveD, rightDriveEnc, rightDriveSpeedController);
		rightDrivePid->SetOutputRange(drivePidMinOut, drivePidMaxOut);
		rightDrivePid->SetContinuous();

		controlStick = new Joystick(controlJsCh);

		rollerMotor = new CANTalon(rollerMotorId);

		photoSwitch = new DigitalInput(photoSwitchCh);
		rollerInOn = false;

		armPot = new AnalogInput(potCh);

		armMotor = new CANTalon(armMotorId);

		armPid = new PIDController(potP, potI, potD, armPot, armMotor);
		armPid->SetInputRange(potMinVolt, potMaxVolt);
		armPid->SetTolerance(potTol);
	}

	~Robot()
	{
		delete leftDriveSpeedController;
		delete rightDriveSpeedController;
		delete myRobot;
		delete driveStick;
		delete leftDriveEnc;
		delete rightDriveEnc;
		delete leftDrivePid;
		delete rightDrivePid;
		delete controlStick;
		delete rollerMotor;
		delete photoSwitch;
		delete armPot;
		delete armMotor;
		delete armPid;
	}
};

START_ROBOT_CLASS(Robot);
