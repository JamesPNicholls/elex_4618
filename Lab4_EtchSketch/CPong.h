#pragma once
#include "stdafx.h"
#include "CBase4618.h"

#define BALL_X_START CANVAS_WIDTH/2
#define BALL_Y_START CANVAS_HEIGHT/2

#define BALL_RADIUS 15

#define LINE_CENTER CANVAS_WIDTH/2

struct paddle_Params
{	
	cv::Point pl_Point = { 40,400 };
	int width = 10;
	int height = 100;
};

struct ball_Params
{
	cv::Point ball_Cords;
	
	int8_t x_a;
	int8_t y_a;

	int8_t x_v;
	int8_t y_v;
};

struct screen_Params
{

};

class CPong : public CBase4618
{
private:
	//void update_Ball();	do i really need these?
	//void update_Paddle();
	void update();
	void draw();

	ball_Params		_Ball;
	paddle_Params	paddle_L;
	paddle_Params	paddle_R;
	screen_Params	screen_Params;
	

public:

	/**
	 * @brief Construct a new CPong object
	 * 
	 */
	CPong();

	/**
	 * @brief Constructor that initalizes the cv::Mat and draws the starting objects
	 * 
	 * @param _Size 		size of _canvas to draw on
	 * @param comPort_Num 	com port for communicating with a MK2 launchpad/boosterpack
	 */
	CPong(cv::Size _Size, int comPort_Num);
	~CPong();

	void run();
};

