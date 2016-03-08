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
	DigitalInput *ballCapturedPhotoSwitch; //not broken=true ,broken=false
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
		//armPid->Enable();

		dataTablePtr = NetworkTable::GetTable("dataTable");

#if robotConfig == robot2016
		//Show USB camera on drive station
		CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
#endif
	}

	void AutonomousInit()
	{
		leftDriveEnc->Reset();
		rightDriveEnc->Reset();

		armPid ->SetSetpoint(armUpPosition);
		rollerMotor ->Set(rollerStopSpeed);
	}

	void AutonomousPeriodic()
	{
		double currentDistLeft = leftDriveEnc->GetDistance();
		double currentDistRight = rightDriveEnc->GetDistance();

		if(currentDistLeft > autoDistance && currentDistRight > autoDistance)
			myRobot->SetLeftRightMotorOutputs(MOTOR_STOP, MOTOR_STOP);
		else
			myRobot->SetLeftRightMotorOutputs(autoSpeedInvert*autoLeftSpeed, autoSpeedInvert*autoRightSpeed);

		//status
		dataTablePtr ->PutNumber("LeftEncDist", leftDriveEnc->GetDistance());
		dataTablePtr ->PutNumber ("RightEncDist", rightDriveEnc->GetDistance());
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
			rollerMotor ->Set(armInvState*rollerInSpeed);
			rollerInOn = true;
		}
		else if (controlStick ->GetRawButton(rollerStop))
		{
			rollerMotor ->Set(rollerStopSpeed);
			rollerInOn = false;
		}
		else if (controlStick ->GetRawButton(rollerOut))
		{
			rollerMotor ->Set(armInvState*rollerOutSpeed);
		}

		if (ballCapturedPhotoSwitch ->Get()== false && rollerInOn)
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
		dataTablePtr ->PutNumber("LeftEncDist", leftDriveEnc->GetDistance());
		dataTablePtr ->PutNumber ("RightEncDist", rightDriveEnc->GetDistance());
		dataTablePtr ->PutBoolean("rollerInOn", rollerInOn);
		dataTablePtr ->PutBoolean("ballCapturedPhotoSwitch", ballCapturedPhotoSwitch->Get());
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
		leftDriveEnc->SetReverseDirection(leftEncInv);

		rightDriveEnc = new Encoder(rightDriveEncA, rightDriveEncB);
		rightDriveEnc->SetDistancePerPulse((2*PI*(wheelRadius/INCHES_IN_FEET))/driveEncoderCounts);
		rightDriveEnc->SetReverseDirection(rightEncInv);

		controlStick = new Joystick(controlJsCh);

		rollerMotor = new CANTalon(rollerMotorId);

		ballCapturedPhotoSwitch = new DigitalInput(ballCapturedPhotoSwitchCh);
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
		delete ballCapturedPhotoSwitch;
		delete armPot;
		delete armMotor;
		delete armPid;
	}
};

START_ROBOT_CLASS(Robot);
