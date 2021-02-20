#pragma once
#include "stdafx.h"
#include "CBase4618.h"

#define BALL_X_START PONG_CANVAS_WIDTH/2
#define BALL_Y_START PONG_CANVAS_HEIGHT/2

#define BALL_RADIUS 8

#define PADDLE_LEFT_X 100
#define PADDLE_LEFT_Y PONG_CANVAS_HEIGHT/2

#define PADDLE_RIGHT_X PONG_CANVAS_WIDTH - PADDLE_LEFT_X
#define PADDKE_RIGHT_Y PONG_CANVAS_HEIGHT/2

#define PADDLE_WIDTH	10
#define PADDLE_HEIGHT	100

#define SCORE_TEXT_HEIGHT	80
#define LEFT_SCORE_POS_X	150
#define RIGHT_SCORE_POS_X	650

#define LINE_CENTER PONG_CANVAS_WIDTH/2


struct paddle_Params
{	
	cv::Point paddle_Point;
	int width;
	int height;

	cv::Rect pl_rectangle;
	cv::Rect pl_Hit_Box; 	//follows pl_rectangle and extends behind it, a really bad way to deal with the collision
							//a better way would be to track the postion of the ball and determine if it passed over the paddle in the past tick
	const cv::Scalar paddle_Colour = { 255,255,255 };//White, could use CV_RGB type
};

struct ball_Params
{
	cv::Point ball_Cords;
	cv::Point ball_Vel;
	cv::Point ball_Acc;

	double current_Time;
	double old_Time;
};

struct screen_Params
{
	int FPS;
	cv::Point fps_Point;

	int l_Score = 0;
	int r_Score = 0;
	 
	cv::Point  player_L_Point;
	cv::Point  player_R_Point;
	cv::String player_L_str;
	cv::String player_R_str;
};

/**
 * @brief 	Iinherited class of CBase 1618
 * 			Contains the structs of the different drawable polygons
 * 			I should make each of the paddles and balls their own objects
 * 
 */
class CPong : public CBase4618
{
private:

	ball_Params		_Ball;						///<
	paddle_Params	left_Paddle_Params;			///<
	paddle_Params	right_Paddle_Params;		///<
	screen_Params	_canvas_Screen_Params;		///<
	const cv::Scalar black_Canvas = { 0,0,0 };	///<

	/**
	 * @brief updates all of the values for each of the structs and 
	 * 
	 */
	void update();

	/**
	 * @brief 
	 * 
	 */
	void draw();

	/**
	 * @brief 
	 * 
	 */
	void reset_Screen_Parameters();

	/**
	 * @brief 
	 * 
	 * @return cv::Point 
	 */
	cv::Point CPong::vel_Gen();	

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

	/**
	 * @brief Destroy the CPong object
	 * 
	 */
	~CPong();

	/**
	 * @brief loops update() and draw() and handles the threading + timing
	 * 
	 */
	void run();
};
