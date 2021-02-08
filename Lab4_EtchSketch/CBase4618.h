#pragma once
#include "CControl.h"

#define CANVAS_WIDTH	1000
#define CANVAS_HEIGHT	1000
#define COM_PORT		10

#define CIRCLE_RADIUS		10


struct cv_Colours
{								//{ B, G, R }
	const cv::Scalar cv_Blue	= { 255, 0, 0 };
	const cv::Scalar cv_Green	= { 0, 255, 0 };
	const cv::Scalar cv_Red		= { 0, 0, 255 };
};

class CBase4618
{
protected:
	CControl _base;
	cv::Mat _canvas; //OpenCV image type

	cv_Colours colours_Struct;

	virtual void update(cv::Point& xy_Cords) = 0;
	virtual void draw(cv::Point xy_Cords) = 0;

public:
	CBase4618();
	~CBase4618();
	void run();
};

class CSketch : public CBase4618
{
private:
	void update(cv::Point& xy_Cords);
	void draw(cv::Point xy_Cords);//add a method to get the colour

public:
	CSketch(cv::Size _Size, int comPort_Num);
	~CSketch();
};
