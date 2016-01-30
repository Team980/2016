#include "WPILib.h"
#include "Parameters.h"

//defines go here

class Robot: public IterativeRobot
{
private:
	//declare all objects here but do not create objects
	
	void RobotInit()
	{
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
	}

	void TestPeriodic()
	{
	}

public:
	Robot()
	{
		//create all objects here (all new statements)
	}

	~Robot()
	{
		//destroy all objects here (all delete statements)
	}
};

START_ROBOT_CLASS(Robot);
