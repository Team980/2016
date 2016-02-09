#include "WPILib.h"
#include "Parameters.h"
#include "Constants.h"

//defines go here

class Robot: public IterativeRobot
{
private:
	// declarations
	CanTalonSRX *m_motor;
	Joystick *stick;
	DigitalInput *limitSwitch;
	
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
		float stickVal;


		stickVal = stick->GetY();

		if (limitSwitch->Get()== false and stickVal < 0)
		{

			m_motor->Set(0);
		}
		else
		{
			m_motor->Set(stickVal);
		}
	}

	void TestPeriodic()
	{
	}

public:
	Robot()
	{
		m_motor = new CanTalonSRX(13);
		stick = new Joystick(0);
		limitSwitch = new DigitalInput(1);

	}

	~Robot()
	{
		delete m_motor;
		delete stick;
		delete limitSwitch;
	}
};

START_ROBOT_CLASS(Robot);
