#include "WPILib.h"

#include "CameraSystem.cpp"

class Robot: public IterativeRobot
{
private:
	RobotDrive *myRobot; // robot drive system
	Joystick *stick; // only joystick

	CameraSystem *cameraSystem; //Camera system

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
		cameraSystem->Scan();
	}

	void TeleopPeriodic()
	{
		//Use Z axis (twist) for rotation
		//myRobot->ArcadeDrive(stick, 1, stick, 2, true); // drive with arcade style (use right stick)


	}

	void TestPeriodic()
	{

	}

public:
	Robot()
	{
		myRobot = new RobotDrive(8,9);
		stick = new Joystick(0);

		cameraSystem = new CameraSystem();

		myRobot->SetExpiration(0.1);

		//The robot was wired backwards
		//Defaults to rear when using two drives
		myRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
		myRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	}

	~Robot ()
	{
		delete myRobot;
		delete stick;

		delete cameraSystem;
	}

};

START_ROBOT_CLASS(Robot)
