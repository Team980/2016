/*
 * CameraSystem.cpp
 *
 *  Created on: Jan 26, 2016
 *      Author: Luke
 */
#include <unistd.h>
#include <stdio.h>

#include "WPILib.h"
#include "Constants.h"

#include "Vision/BaeUtilities.h"
#include "Vision/FrcError.h"
#include "Vision/VisionAPI.h"

#define VIEW_ANGLE 49.0

#define TARGET_WIDTH 1.667
#define FOV_PIX_WIDTH 320
#define FOV_PIX_HEIGHT 240

class CameraSystem {

	double twoTanTheta;

public:
	CameraSystem() {
		twoTanTheta = 2.0*tan(VIEW_ANGLE*PI/(180.0*2.0));

		std::cout << "Suuuure hope you got GRIP printing to NetworkTables..." << std::endl;
	}

	/* Requires GRIP to be running in order for this to do anything! */
	void Scan() {
		auto grip = NetworkTable::GetTable("grip");

		auto xCoords = grip->GetNumberArray("targets/centerX", llvm::ArrayRef<double>());

		for (auto x : xCoords) {
			std::cout << "Got contour with centerX=" << x << std::endl;

			double xConv = (x - FOV_PIX_WIDTH/2)/(FOV_PIX_WIDTH/2);

			std::cout << "Converted to aiming system X=" << xConv << std::endl;
		}

		auto yCoords = grip->GetNumberArray("targets/centerY", llvm::ArrayRef<double>());

		for (auto y : yCoords) {
			std::cout << "Got contour with centerY=" << y << std::endl;

			double yConv = -1((y - FOV_PIX_HEIGHT/2)/(FOV_PIX_HEIGHT/2));

			std::cout << "Converted to aiming system Y=" << yConv << std::endl;
		}

		auto targetWidths = grip->GetNumberArray("targets/width", llvm::ArrayRef<double>());

		for (auto targetWidth : targetWidths) {
			std::cout << "Got target with width=" << targetWidth << std::endl;

			double distance = TARGET_WIDTH*FOV_PIX_WIDTH/(targetWidth*twoTanTheta);

			std::cout << "Got distance=" << distance << std::endl;
		}

	}

private:
	/*double computeDistance (ParticleAnalysisReport *report)
	{
		double distance = TARGET_WIDTH*FOV_PIX_WIDTH/(targetWidth*twoTanTheta);

		return (distance);
	}*/
};


