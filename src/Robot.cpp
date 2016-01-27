#include "WPILib.h"

#include "CameraSystem.cpp"

class Robot: public IterativeRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
	LiveWindow *lw;

	CameraSystem cameraSystem;

	int autoLoopCounter;

public:
	Robot() :
		myRobot(8, 9),	// these must be initialized in the same order
		stick(0),		// as they are declared above.
		lw(LiveWindow::GetInstance()),
		autoLoopCounter(0)
	{
		myRobot.SetExpiration(0.1);

		//The robot was wired backwards
		//Defaults to rear when using two drives
		myRobot.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
		myRobot.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	}

private:
	void AutonomousInit()
	{
		autoLoopCounter = 0;
	}

	void AutonomousPeriodic()
	{
		if(autoLoopCounter < 100) //Check if we've completed 100 loops (approximately 2 seconds)
		{
			myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
			autoLoopCounter++;
			} else {
			myRobot.Drive(0.0, 0.0); 	// stop robot
		}
	}

	void TeleopInit()
	{
		cameraSystem.Scan();
	}

	void TeleopPeriodic()
	{
		//Use Z axis (twist) for rotation
		myRobot.ArcadeDrive(stick, 1, stick, 2, true); // drive with arcade style (use right stick)
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
