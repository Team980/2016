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

		auto areas = grip->GetNumberArray("targets/area", llvm::ArrayRef<double>());

		for (auto area : areas) {
			std::cout << "Got contour with area=" << area << std::endl;
		}
	}

	//Legacy code. Not recommended for use
	/*void Scan()
	{
		int ret;
		ParticleFilterCriteria2 criteria[] = {{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}};
		Range *hueRange, *saturationRange;//, luminanceRange;
		int numParticles, i;
		ParticleAnalysisReport report;
		ParticleFilterOptions  particleFilterOpt;

		int dispField;
		double distance[2];

		printf("Starting Vision...\n");

		Image *inputImage = frcCreateImage(IMAQ_IMAGE_RGB);
		Image *thresholdImage = frcCreateImage(IMAQ_IMAGE_U8);
		Image *particleImage = frcCreateImage(IMAQ_IMAGE_U8);

		ret = camera->GetImage(inputImage);
		if (!ret)
		{
			printf("problem getting image\n");
		}
		else
		{
			printf("Got image\n");
		}

		ret = frcWriteImage (inputImage, "/home/lvuser/raw.png");

		if (!ret)
		{
			printf("PROBLEM writing file\n");
			printf(GetVisionErrorText(GetLastVisionError()));
		}
		else
		{
			printf("Wrote image: raw.png\n");
		}
		// values needed to discriminate the GREEN REFLECTIVE TAPE - TODO Make these work
		hueRange = new Range();
		saturationRange = new Range();
		//luminanceRange = new Range();

		hueRange->minValue = 150;
		hueRange->maxValue = 170;
		saturationRange->minValue = 80;
		saturationRange->maxValue = 100;
		//luminanceRange.minValue = 70;//120;
		//luminanceRange.maxValue = 255;//150;

		printf("Thresholding...\n");

		ret = frcColorThreshold(thresholdImage, inputImage, 170, IMAQ_HSL, hueRange, saturationRange, nullptr); //TODO make this work
		if (!ret)
		{
			printf("Problem thresholding image\n");
		}
		else
		{
			printf("Thresholding image complete\n");
		}

		frcWriteImage (thresholdImage, "/home/lvuser/threshold.png");

		particleFilterOpt.rejectMatches = 0;  // accept only particles passing all criteria
		particleFilterOpt.rejectBorder = 1;  // reject blobs on the image border
		particleFilterOpt.connectivity8 = 1;  // use 8-way connectivity
		ret = frcParticleFilter (particleImage, thresholdImage, criteria, 1,
				&particleFilterOpt, &numParticles);
		if (!ret)
		{
			printf("problem with particle filter\n");
		}
		else
		{
			printf("particle fltr complete %d\n", numParticles);
		}

		frcWriteImage (particleImage, "/home/lvuser/Filtered.png");

		dispField = 0;
		for (i=0; i<numParticles; i++)
		{
			ret = frcParticleAnalysis(particleImage, i, &report);
			if (!ret)
			{
				printf("prbm w/part.analysis %d\n", i);
			}

			if ((report.particleArea > AREA_MINIMUM) && (report.particleArea < AREA_MAXIMUM)) //TODO change this
			{
				printf("CM:%d, %d\n", report.center_mass_x, report.center_mass_y);
				printf("BB:%d, %d / %d, %d\n", report.boundingRect.top, report.boundingRect.left,
						report.boundingRect.width, report.boundingRect.height);
				if (dispField < 2)
					distance[dispField] = computeDistance(&report);
				dispField++;
			}
		}
		printf("dist: %lf %lf", distance[0], distance[1]);
		printf("dispField: %d", dispField);
	}*/

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


