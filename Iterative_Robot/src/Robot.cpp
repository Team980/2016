#include "WPILib.h"
#include "Parameters.h"
#include "Constants.h"

class Robot: public IterativeRobot
{
private:
	// declarations
	RobotDrive *myRobot; // robot drive system
	Joystick *driveStick;
	Joystick *driveWheel;
	Encoder *leftDriveEnc;
	Encoder *rightDriveEnc;
	
	Joystick *controlStick;
	CANTalon *rollerMotor;
	DigitalInput *ballCapturedPhotoSwitch;
	bool rollerInOn;
	CANTalon *armMotor;
	bool armDownStatus; //indication if the arm is in the process of going down

	//Network Tables
	std::shared_ptr<NetworkTable> dataTablePtr;

	void RobotInit()
	{
		dataTablePtr = NetworkTable::GetTable("dataTable");

		//Show USB camera on drive station
		/*
		CameraServer::GetInstance()->SetQuality(50);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0"); //the camera name (ex "cam0") can be found through the roborio web interface
		*/
	}

	void AutonomousInit()
	{
		leftDriveEnc->Reset();
		rightDriveEnc->Reset();

		armMotor->SetPID(armPidP, armPidIAuto, armPidD);
		armMotor->Set(armUpPosition);
		armMotor->EnableControl();

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
		armMotor->SetPID(armPidP,armPidITeleop,armPidD);
	    armMotor->EnableControl();
	}

	void TeleopPeriodic()
	{
		//sets driving mode
		if(driveStick->GetRawButton(highSpeedMode))
		{
			myRobot->SetMaxOutput(maxOutputDriveFracHigh);
		}
		else
		{
			myRobot->SetMaxOutput(maxOutputDriveFracLow);
		}

		//drive
		myRobot->ArcadeDrive(driveStick, Joystick::kYAxis, driveWheel, Joystick::kXAxis, true);

		//roller
		if (controlStick ->GetRawButton(rollerIn))
		{
			rollerMotor ->Set(rollerInvState*rollerInSpeed);
			rollerInOn = true;
		}
		else if (controlStick ->GetRawButton(rollerStop))
		{
			rollerMotor ->Set(rollerStopSpeed);
			rollerInOn = false;
    	}
		else if (controlStick ->GetRawButton(rollerOut))
		{
			rollerMotor ->Set(rollerInvState*rollerOutSpeed);
			rollerInOn = false;
		}

		//photoswitch
		if (ballCapturedPhotoSwitch ->Get() == photoSwitchBeamBroken && rollerInOn)
		{
			rollerMotor ->Set(rollerStopSpeed);
			rollerInOn = false;
		}

		//arm
		if (controlStick->GetRawButton(armUp))
		{
			armDownStatus = false;
			armMotor->Set(armUpPosition);
			armMotor->Enable();
		}
		else if (controlStick->GetRawButton(armDown))
		{
			armDownStatus = true;
			armMotor->Set(armDownPosition);
			//pid should already be enabled (from going up)
		}

		if(armMotor->Get() < armPidDisablePosition && armDownStatus == true)
		{
			armDownStatus = false;
			armMotor->Disable();
		}

		//status
		dataTablePtr ->PutNumber("LeftEncDist", leftDriveEnc->GetDistance());
		dataTablePtr ->PutNumber ("RightEncDist", rightDriveEnc->GetDistance());
		dataTablePtr ->PutBoolean("rollerInOn", rollerInOn);
		dataTablePtr ->PutBoolean("ballCapturedPhotoSwitch", ballCapturedPhotoSwitch->Get());
		dataTablePtr ->PutNumber("armPidSetpoint", armMotor ->GetSetpoint());
		dataTablePtr ->PutNumber("armEnc", armMotor ->Get());
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
		myRobot->SetMaxOutput(maxOutputDriveFracLow);

		driveStick = new Joystick(driveJsCh);

		driveWheel = new Joystick(driveWheelCh);

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

		armMotor = new CANTalon(armMotorId);

		armMotor ->SetControlMode(CANSpeedController::kPosition);
		armMotor ->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
		armMotor ->SetSensorDirection(armPidInvert);
		armMotor ->ConfigNominalOutputVoltage(armPidMaxNominal,armPidMinNominal);
		armMotor ->ConfigPeakOutputVoltage(armPidMaxPeak,armPidMinPeak);
		armMotor ->SetAllowableClosedLoopErr(armPidAllowableErr);

		armDownStatus = false;
	}

	~Robot()
	{
		delete myRobot;
		delete driveStick;
		delete driveWheel;
		delete leftDriveEnc;
		delete rightDriveEnc;
		delete controlStick;
		delete rollerMotor;
		delete ballCapturedPhotoSwitch;
		delete armMotor;
	}
};

START_ROBOT_CLASS(Robot);
