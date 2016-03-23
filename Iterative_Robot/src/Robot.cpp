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
	Joystick *driveWheel;
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
	bool armDownStatus = false;

	//Network Tables
	std::shared_ptr<NetworkTable> dataTablePtr;

	void RobotInit()
	{
		dataTablePtr = NetworkTable::GetTable("dataTable");

#if robotConfig == robot2016
		//Show USB camera on drive station
		//CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		//CameraServer::GetInstance()->StartAutomaticCapture("cam0");
#endif
	}

	void AutonomousInit()
	{
		leftDriveEnc->Reset();
		rightDriveEnc->Reset();

<<<<<<< HEAD
		armMotor->SetPID(potP, potIAuto, potD);
		//armPid ->SetSetpoint(armFlatPosition); //Uncomment this is want to go under the LOW BAR in autonomous
		armMotor->SetSetpoint(armMotor->Get()); //hold the current position
		armMotor->EnableControl();
=======
		armPid->SetPID(potP, potIAuto, potD);
		//armPid ->SetSetpoint(armFlatPosition); //Uncomment this is want to go under the LOW BAR in autonomous
		armPid->SetSetpoint(armPot->GetAverageVoltage()); //hold the current position
		armPid->Enable();
>>>>>>> origin/2016_Robot_ManualArm

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
<<<<<<< HEAD
		/*armPid->SetPID(potP, potITeleop, potD);
		armPid->Disable();*/
		armMotor->SetPID(potP,potITeleop,potD);
	    armMotor->EnableControl();
=======
		armPid->SetPID(potP, potITeleop, potD);
		armPid->Disable();
>>>>>>> origin/2016_Robot_ManualArm

		leftDriveEnc->Reset();
		rightDriveEnc->Reset();
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
<<<<<<< HEAD
		myRobot->ArcadeDrive(driveStick, Joystick::kYAxis, driveWheel, Joystick::kXAxis, true);
		//myRobot->ArcadeDrive(driveStick, Joystick::kYAxis, driveStick, Joystick::kZAxis, true);
=======
		myRobot->ArcadeDrive(driveStick, Joystick::kYAxis, driveStick, Joystick::kZAxis, true);
>>>>>>> origin/2016_Robot_ManualArm
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

		/*if (ballCapturedPhotoSwitch ->Get()== false && rollerInOn)
		{
			rollerMotor ->Set(rollerStopSpeed);
			rollerInOn = false;
		}*/

		//arm
		/*if (controlStick ->GetRawButton(armDown))
		{
			armPid->SetSetpoint(armDownPosition);
<<<<<<< HEAD
		}
=======
		}*/
>>>>>>> origin/2016_Robot_ManualArm
		if (controlStick ->GetRawButton(armFlat))
		{
			armPid->Disable();
		}
		else if (controlStick ->GetRawButton(armUp))
		{
			armPid->SetSetpoint(armUpPosition);
			armPid->Enable();
<<<<<<< HEAD
		}*/
		if (controlStick->GetRawButton(armUp))
		{
			armMotor->Enable();
			std::cout<< "GOING UP Get: "<< armMotor->Get()<<std::endl;
			armMotor->Set(armUpPosition);
			std::cout<<"END going up, armDown: "<<armDownStatus<<" enc: "<<armMotor->Get()<<std::endl;
		}
		else if (controlStick->GetRawButton(armDown))
		{
			std::cout<< "Going down, Get: "<< armMotor->Get()<<std::endl;

			armDownStatus = true;
			armMotor->Set(armDownPosition);

			std::cout<<"End button 2, armDown: "<<armDownStatus << " enc: "<<armMotor->Get()<<std::endl;
		}
		if(armMotor->Get()< -1.6 && armDownStatus == true)
		{
			armMotor->Disable();
			armDownStatus = false;
=======
>>>>>>> origin/2016_Robot_ManualArm
		}

		//status
		dataTablePtr ->PutNumber("LeftEncDist", leftDriveEnc->GetDistance());
		dataTablePtr ->PutNumber ("RightEncDist", rightDriveEnc->GetDistance());
		dataTablePtr ->PutBoolean("rollerInOn", rollerInOn);
		dataTablePtr ->PutBoolean("ballCapturedPhotoSwitch", ballCapturedPhotoSwitch->Get());
<<<<<<< HEAD
		dataTablePtr ->PutNumber("armPidSetpoint", armMotor ->GetSetpoint());
		//dataTablePtr ->PutNumber("armPidError", armPot ->GetError());
		dataTablePtr ->PutNumber("armEnc", armMotor ->Get());
=======
		dataTablePtr ->PutNumber("armPidSetpoint", armPid ->GetSetpoint());
		dataTablePtr ->PutNumber("armPidError", armPid ->GetError());
		dataTablePtr ->PutNumber("armPot", armPot ->GetVoltage());
		dataTablePtr ->PutNumber("yAxis", driveStick ->GetRawAxis(1));
		dataTablePtr ->PutNumber("zAxis", driveStick ->GetRawAxis(2));
>>>>>>> origin/2016_Robot_ManualArm
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

		armPot = new AnalogInput(potCh);

		armMotor = new CANTalon(armMotorId);

<<<<<<< HEAD
		/*armPid = new PIDController(potP, potIAuto, potD, armPot, armMotor);
=======
		armPid = new PIDController(potP, potIAuto, potD, armPot, armMotor);
>>>>>>> origin/2016_Robot_ManualArm
		armPid->SetInputRange(potMinVolt, potMaxVolt);
		armPid->SetTolerance(potTol);*/
		armMotor ->SetControlMode(CANSpeedController::kPosition);
		armMotor ->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
		armMotor ->SetSensorDirection(true);
		armMotor ->ConfigNominalOutputVoltage(+0,-0);
		armMotor ->ConfigPeakOutputVoltage(+12,-12);
		armMotor ->SetAllowableClosedLoopErr(0);
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
		delete armPot;
		delete armMotor;
		delete armPid;
	}
};

START_ROBOT_CLASS(Robot);
