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
		delete controlStick;
		delete rollerMotor;
		delete photoSwitch;
		delete armPot;
		delete armMotor;
		delete armPid;
	}
};

START_ROBOT_CLASS(Robot);
