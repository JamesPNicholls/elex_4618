#pragma once
#include "stdafx.h"
#include "CBase4618.h"

#define BALL_X_START CANVAS_WIDTH/2
#define BALL_Y_START CANVAS_HEIGHT/2

#define BALL_RADIUS 15

#define PADDLE_LEFT_X 100
#define PADDLE_LEFT_Y CANVAS_HEIGHT/2

#define PADDLE_RIGHT_X CANVAS_WIDTH - PADDLE_LEFT_X
#define PADDKE_RIGHT_Y CANVAS_HEIGHT/2

#define PADDLE_WIDTH	10
#define PADDLE_HEIGHT	100

#define SCORE_TEXT_HEIGHT	80
#define LEFT_SCORE_POS_X	150
#define RIGHT_SCORE_POS_X	650

#define LINE_CENTER CANVAS_WIDTH/2

struct paddle_Params
{	
	cv::Point paddle_Point;
	int width;
	int height;

	cv::Rect pl_rectangle;
	cv::Scalar paddle_Colour =	{ 255,255,255 };
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
	int FPS;
	int l_Score;
	int r_Score;

	cv::Point  player_L_Point;
	cv::Point  player_R_Point;
	cv::String player_L_str;
	cv::String player_R_str;
};

class CPong : public CBase4618
{
private:
	void update();
	void draw();

	void reset_Screen_Parameters();
	//structs usde to old the paramters for all of the objects
	ball_Params		_Ball;
	paddle_Params	left_Paddle_Params;
	paddle_Params	right_Paddle_Params;
	screen_Params	_canvas_Screen_Params;

	const cv::Scalar black_Canvas = { 0,0,0 };

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
