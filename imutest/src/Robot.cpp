#include "WPILib.h"
#include "AHRS.h"

using std::cout;
using std::endl;

class Robot: public SampleRobot
{

    // Channels for the test motor
    const static int testMotorChannel	= 13;

    AHRS *ahrs;                         // navX MXP
    CANTalon testMotor;

public:
	Robot() : testMotor(testMotorChannel)
    {
        try {
            /* Communicate w/navX MXP via the MXP SPI Bus.                                       */
            /* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
            /* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */
            ahrs = new AHRS(SPI::Port::kMXP);
        	 //ahrs = new AHRS(SerialPort::Port::kUSB);
            cout << "Trying to create an ahrs" << endl;
        } catch (std::exception ex ) {
            std::string err_string = "Error instantiating navX MXP:  ";
            err_string += ex.what();
            cout << err_string.c_str() << endl;
        }

        cout << "Created an ahrs" << endl;

        if ( ahrs ) {
        	ahrs->ZeroYaw();

        	cout << "Zeroed the yaw" << endl;

            LiveWindow::GetInstance()->AddSensor("IMU", "Gyro", ahrs);

            cout << "currentYaw: " << ahrs->GetYaw() << endl;
        }
    }

    void OperatorControl()
    {
    	float currentYaw;
    	float yawTarget = 0; //degrees
    	float atTargetTol = 2.5; //degrees

        while (IsOperatorControl() && IsEnabled())
        {
            currentYaw = ahrs->GetYaw();


            cout << "currentYaw: " << currentYaw << endl;


            if(fabs(currentYaw - yawTarget) <= atTargetTol)
            {
            	testMotor.Set(0);
            	cout << "At the target" << endl;
            }
            else if(currentYaw > 0)
            	testMotor.Set(-0.25);
            else if(currentYaw < 0)
            	testMotor.Set(0.25);

            Wait(0.005); // wait 5ms to avoid hogging CPU cycles
        }
    }
};

START_ROBOT_CLASS(Robot);
