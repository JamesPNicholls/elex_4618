#pragma once
#include "CControl.h"

#define CANVAS_WIDTH		800
#define CANVAS_HEIGHT		800
#define CANVAS_W_DRAW		1100
#define CANVAS_H_DRAW		1100

#define DRAW_CANVAS_OFFSET	150

#define COM_PORT		10
#define CIRCLE_RADIUS	10

class CBase4618
{
protected:
	CControl _base;
	cv::Mat _canvas; //OpenCV image type

	virtual void update() = 0;
	virtual void draw() = 0;

public:
	CBase4618();
	~CBase4618();
	void init_RGB_LED();
	void run();
};

class CSketch : public CBase4618
{
private:
	void update();
	void draw();//add a method to get the colour

	cv::Scalar current_Colour = { 255, 0, 0 };
	cv::Point new_XY_Cords;
	cv::Point current_XY_Cords;

public:
	CSketch(cv::Size _Size, int comPort_Num);
	~CSketch();
};
