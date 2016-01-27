/*
 * CameraSystem.cpp
 *
 *  Created on: Jan 26, 2016
 *      Author: Luke
 */
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

	AxisCamera *camera;
	double twoTanTheta;

public:
	CameraSystem() {
		camera = new AxisCamera("10.9.80.20");

		twoTanTheta = 2.0*tan(VIEW_ANGLE*PI/(180.0*2.0));
	}

	void Scan()
	{
		int ret;
		Threshold threshold(0, 255, 50, 255, 70, 255);
		ParticleFilterCriteria2 criteria[] = {{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}};
		char myString[64];
		Range hueRange;  //, saturationRange, luminanceRange;
		int numParticles, i;
		ParticleAnalysisReport report;
		ParticleFilterOptions  particleFilterOpt;

		int dispField;
		double distance[2];

		sprintf(myString, "starting vision\n");
		SmartDashboard::PutString("DB/String 0", myString);

		Image *inputImage = frcCreateImage(IMAQ_IMAGE_RGB);
		Image *thresholdImage = frcCreateImage(IMAQ_IMAGE_U8);
		Image *particleImage = frcCreateImage(IMAQ_IMAGE_U8);

		ret = camera->GetImage(inputImage);
		if (!ret)
		{
			sprintf(myString, "problem getting image\n");
			SmartDashboard::PutString("DB/String 1", myString);
		}
		else
		{
			sprintf(myString, "Got image\n");
			SmartDashboard::PutString("DB/String 1", myString);
		}

		ret = frcWriteImage (inputImage, "/home/lvuser/raw.png");

		if (!ret)
		{
			sprintf(myString, "PROBLEM writing file\n");
			sprintf(myString,GetVisionErrorText(GetLastVisionError()));
			SmartDashboard::PutString("DB/String 2", myString);
		}
		else
		{
			sprintf(myString, "wrote image\n");
			SmartDashboard::PutString("DB/String 2", myString);
		}
		// values needed to discriminate the GREEN REFLECTIVE TAPE
		// these values are probably wrong but no harm in trying...
		hueRange.minValue = 80;
		hueRange.maxValue = 120;
		//	saturationRange.minValue = 135;
		//	saturationRange.maxValue = 165;
		//	luminanceRange.minValue = 120;
		//	luminanceRange.maxValue = 150;

		sprintf(myString, "threshold\n");
		SmartDashboard::PutString("DB/String 0", myString);

		ret = frcHueThreshold(thresholdImage, inputImage, &hueRange);
		if (!ret)
		{
			sprintf(myString, "problem thresholding image\n");
			SmartDashboard::PutString("DB/String 3", myString);
		}
		else
		{
			sprintf(myString, "t-holding image complete\n");
			SmartDashboard::PutString("DB/String 3", myString);
		}

		frcWriteImage (thresholdImage, "/home/lvuser/threshold.png");

		particleFilterOpt.rejectMatches = 0;  // accept only particles passing all criteria
		particleFilterOpt.rejectBorder = 1;  // reject blobs on the image border
		particleFilterOpt.connectivity8 = 1;  // use 8-way connectivity
		ret = frcParticleFilter (particleImage, thresholdImage, criteria, 1,
				&particleFilterOpt, &numParticles);
		if (!ret)
		{
			sprintf(myString, "problem with particle filter\n");
			SmartDashboard::PutString("DB/String 4", myString);
		}
		else
		{
			sprintf(myString, "particle fltr complete %d\n", numParticles);
			SmartDashboard::PutString("DB/String 4", myString);
		}

		frcWriteImage (particleImage, "/home/lvuser/Filtered.png");

		dispField = 0;
		for (i=0; i<numParticles; i++)
		{
			ret = frcParticleAnalysis(particleImage, i, &report);
			if (!ret)
			{
				sprintf(myString, "prbm w/part.analysis %d\n", i);
				SmartDashboard::PutString("DB/String 5", myString);
			}

			if ((report.particleArea > AREA_MINIMUM) && (report.particleArea < AREA_MAXIMUM))
			{
				sprintf(myString, "CM:%d, %d\n", report.center_mass_x, report.center_mass_y);
				SmartDashboard::PutString("DB/String 6", myString);
				sprintf(myString, "BB:%d, %d / %d, %d\n", report.boundingRect.top, report.boundingRect.left,
						report.boundingRect.width, report.boundingRect.height);
				SmartDashboard::PutString("DB/String 7", myString);
				if (dispField < 2)
					distance[dispField] = computeDistance(&report);
				dispField++;
			}
		}
		sprintf(myString, "dist: %lf %lf", distance[0], distance[1]);
		SmartDashboard::PutString("DB/String 8", myString);
		sprintf(myString, "dispField: %d", dispField);
		SmartDashboard::PutString("DB/String 9", myString);
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


