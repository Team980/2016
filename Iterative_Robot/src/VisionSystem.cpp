#include <unistd.h>
#include <stdio.h>

#include "WPILib.h"
#include "Constants.h"
#include "Parameters.h"

#include "Vision/BaeUtilities.h"
#include "Vision/FrcError.h"
#include "Vision/VisionAPI.h"

/*
 * CameraSystem class.
 * Implements vision system.
 * Sorry, no dragon detection system has been implemented.
 */
class VisionSystem {

	double twoTanTheta;

public:
	VisionSystem() {
		twoTanTheta = 2.0*tan(camViewAngle*PI/(180*2.0));

		std::cout << twoTanTheta << std::endl;
		std::cout << "Sure hope you got GRIP printing to NetworkTables..." << std::endl;
	}

	/* Requires GRIP to be running in order for this to do anything! */
	/* Should convert to output values more usefully*/
	void Scan() {
		auto grip = NetworkTable::GetTable("GRIP");

		auto xCoords = grip->GetNumberArray("targets/centerX", llvm::ArrayRef<double>());

		for (auto x : xCoords) {
			std::cout << "Got contour with centerX=" << x << std::endl;

			double xConv = (x - fovPixWidth/2)/(fovPixWidth/2);

			std::cout << "Converted to aiming system X=" << xConv << std::endl;
		}

		auto yCoords = grip->GetNumberArray("targets/centerY", llvm::ArrayRef<double>());

		for (auto y : yCoords) {
			std::cout << "Got contour with centerY=" << y << std::endl;

			double yConv = ((y - fovPixHeight/2)/(fovPixHeight/2))*-1;

			std::cout << "Converted to aiming system Y=" << yConv << std::endl;
		}

		auto targetWidths = grip->GetNumberArray("targets/width", llvm::ArrayRef<double>());

		for (auto targetWidth : targetWidths) {
			std::cout << "Got target with width=" << targetWidth << std::endl;

			double distance = vTargetWidth*fovPixWidth/(targetWidth*twoTanTheta);

			std::cout << "Got distance=" << distance << std::endl;
		}

	}
};
