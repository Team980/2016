#include "WPILib.h"
#include <cmath>

class Robot: public IterativeRobot
{
	Talon m_motor;

	DigitalInput photoSwitch;


public:
	Robot() :
		m_motor(8), photoSwitch(1)
	{
	}

private:
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


	 if (photoSwitch.Get()== false)
		{

		   m_motor.Set(.5);
		}
	 else
		 {
		   m_motor.Set(0);
		 }
	}
	void TestPeriodic()
	{

	}
};

START_ROBOT_CLASS(Robot)
