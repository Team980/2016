#include "WPILib.h"

#include "CameraSystem.cpp"

class Robot: public IterativeRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
	LiveWindow *lw;

	CameraSystem cameraSystem; //Camera system

private:
	void RobotInit() {

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
		//Use Z axis (twist) for rotation
		myRobot.ArcadeDrive(stick, 1, stick, 2, true); // drive with arcade style (use right stick)

		cameraSystem.Scan();
	}

	void TestPeriodic()
	{
		lw->Run();
	}

public:
	Robot()
	{
		myRobot = new RobotDrive(8,9);
		stick = new Joystick(0);
		lw = new LiveWindow(LiveWindow::GetInstance());

		cameraSystem = new CameraSystem();

		myRobot.SetExpiration(0.1);

		//The robot was wired backwards
		//Defaults to rear when using two drives
		myRobot.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
		myRobot.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	}

	~Robot ()
	{
		~myRobot();
		~stick();
		~lw();

		~cameraSystem();
	}

};

START_ROBOT_CLASS(Robot)
