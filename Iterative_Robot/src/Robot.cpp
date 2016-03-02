#include "WPILib.h"
#include "Parameters.h"
#include "Constants.h"
#include <math.h>

class Robot: public IterativeRobot
{
private:
	// declarations
	RobotDrive *myRobot; // robot drive system
	Joystick *driveStick;
	Encoder *leftDriveEnc;
	Encoder *rightDriveEnc;
	
	Joystick *controlStick;
	CANTalon *rollerMotor;
	DigitalInput *photoSwitch;
	bool rollerInOn;

	//same joystick as the roller
	AnalogInput *armPot;
	CANTalon *armMotor;
	PIDController *armPid;

	//Network Tables
	std::shared_ptr<NetworkTable> dataTablePtr;

	void RobotInit()
	{
		armPid->SetSetpoint(armUpPosition);
		armPid->Enable();

		//Show USB camera on drive station
		CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
	}

	void AutonomousInit()
	{
		leftDriveEnc->Reset();
		rightDriveEnc->Reset();
	}

	void AutonomousPeriodic()
	{
		double currentDistLeft = leftDriveEnc->GetDistance();
		double currentDistRight = rightDriveEnc->GetDistance();

		if(autoLeftDistInvert*currentDistLeft > autoDistance && autoRightDistInvert*currentDistRight > autoDistance)
			myRobot->Drive(MOTOR_STOP, NO_CURVE);
		else
			myRobot->Drive(autoSpeed, autoCurve);

		//status
		//std::cout << "leftEnc: " << (autoLeftDistInvert*currentDistLeft) << std::endl;
		//std::cout << "rightEnc: " << (autoRightDistInvert*currentDistRight) << std::endl;
		dataTablePtr ->PutNumber("signedLeftEncDist", autoLeftDistInvert*currentDistLeft);
		dataTablePtr ->PutNumber ("signedRightEncDist", autoRightDistInvert*currentDistRight);
	}

	void TeleopInit()
	{
		leftDriveEnc->Reset();
		rightDriveEnc->Reset();
	}

	void TeleopPeriodic()
	{
		//drive
		myRobot->ArcadeDrive(driveStick, Joystick::kYAxis, driveStick, Joystick::kZAxis, true);

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

		//status
		//std::cout << "leftEnc: " << leftDriveEnc->GetDistance() << std::endl;
		//std::cout << "rightEnc: " << rightDriveEnc->GetDistance() << std::endl;
		dataTablePtr ->PutNumber("LeftEncDist", leftDriveEnc->GetDistance());
		dataTablePtr ->PutNumber ("RightEncDist", rightDriveEnc->GetDistance());
		dataTablePtr ->PutBoolean("rollerInOn", rollerInOn);
		dataTablePtr ->PutBoolean("photoSwitch", photoSwitch);
		dataTablePtr ->PutNumber("armPidSetpoint", armPid ->GetSetpoint());
		dataTablePtr ->PutNumber("armPidError", armPid ->GetError());
		dataTablePtr ->PutNumber("armPot", armPot ->GetVoltage());
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
		myRobot->SetMaxOutput(maxOutputDriveFrac);

		driveStick = new Joystick(driveJsCh);

		leftDriveEnc = new Encoder(leftDriveEncA, leftDriveEncB);
		leftDriveEnc->SetDistancePerPulse((2*PI*(wheelRadius/INCHES_IN_FEET))/driveEncoderCounts);

		rightDriveEnc = new Encoder(rightDriveEncA, rightDriveEncB);
		rightDriveEnc->SetDistancePerPulse((2*PI*(wheelRadius/INCHES_IN_FEET))/driveEncoderCounts);

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
		delete myRobot;
		delete driveStick;
		delete leftDriveEnc;
		delete rightDriveEnc;
		delete controlStick;
		delete rollerMotor;
		delete photoSwitch;
		delete armPot;
		delete armMotor;
		delete armPid;
	}
};

START_ROBOT_CLASS(Robot);

