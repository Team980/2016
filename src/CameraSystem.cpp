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

#define VIEW_ANGLE 59.0

#define TARGET_WIDTH 16.75
#define FOV_PIX_WIDTH 640
#define FOV_PIX_HEIGHT 480

class CameraSystem {

	double twoTanTheta;

public:
	CameraSystem() {
		twoTanTheta = 2.0*tan(VIEW_ANGLE*PI/(180.0*2.0));
	}

	/* Requires GRIP to be running in order for this to do anything! */
	void Scan() {
		auto grip = NetworkTable::GetTable("grip");

		auto xCoords = grip->GetNumberArray("targets/centerX", llvm::ArrayRef<double>());

		for (auto x : xCoords) {
			std::cout << "Got contour with centerX=" << x << std::endl;

			double xConv = (x - 320/2)/(640/2);

			std::cout << "Converted to aiming system X=" << xConv << std::endl;
		}

		auto yCoords = grip->GetNumberArray("targets/centerY", llvm::ArrayRef<double>());

		for (auto y : yCoords) {
			std::cout << "Got contour with centerY=" << y << std::endl;

			double yConv = -1((y - 240/2)/(240/2));

			std::cout << "Converted to aiming system Y=" << yConv << std::endl;
		}
	}

private:
	double computeDistance (ParticleAnalysisReport *report)
	{
		double distance;
		int targetWidthPix;

		targetWidthPix = report->boundingRect.width;
		distance = (TARGET_WIDTH * FOV_PIX_WIDTH) / (targetWidthPix * twoTanTheta);
		return (distance);
	}
};


