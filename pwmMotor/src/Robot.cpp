#include "WPILib.h"
#include <cmath>

class Robot: public IterativeRobot
{
	Talon m_motor;
	Joystick stick;
	DigitalInput limitSwitch;


public:
	Robot() :
		m_motor(8), stick(0), limitSwitch(1)
	{m_motor.SetInverted(true);
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
		float stickVal;


		stickVal = stick.GetY();

	 if (limitSwitch.Get()== false and stickVal < 0)
		{

		   m_motor.Set(0);
		}
	 else
		 {
		 	 m_motor.Set(stickVal);
		 }
	}
	void TestPeriodic()
	{

	}
};

START_ROBOT_CLASS(Robot)

