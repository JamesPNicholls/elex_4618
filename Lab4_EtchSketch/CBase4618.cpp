#include "stdafx.h"
#include "CBase4618.h"

/**********************
	CBase4618 Methods
***********************/
CBase4618::CBase4618()
{

}
CBase4618::~CBase4618()
{

}
void CBase4618::run()
{	
	cv::Point xy_Cords;
	while (cv::waitKey(1) != 'q')
	{
		update(xy_Cords);
		draw(xy_Cords);

		cv::imshow("_canvas", _canvas);
	}	
}
/* CBase4618 Methods*/

/******************** 
	CSketch Methods
*********************/
CSketch::CSketch(cv::Size _Size, int commPort_Num)
{
	_canvas = cv::Mat::zeros(_Size, CV_8UC3);
	_base.init_com(commPort_Num);
}

CSketch::~CSketch()
{

}

void CSketch::update(cv::Point &xy_Cords)
{
	_base.get_data(analog, joyStick_X, xy_Cords.x);
	_base.get_data(analog, joyStick_Y, xy_Cords.y);

	xy_Cords.x = (int)((float)xy_Cords.x / analog_Convesion_Factor * CANVAS_WIDTH);
	xy_Cords.y = CANVAS_HEIGHT - (int)((float)xy_Cords.y / analog_Convesion_Factor * CANVAS_HEIGHT);
}

void CSketch::draw(cv::Point xy_Cords)
{
	cv::circle(_canvas, xy_Cords, CIRCLE_RADIUS, colours_Struct.cv_Blue,-1);
}
/* CSketch Methods*/
	