#include "stdafx.h"
#include "CPong.h"
#include <string>

CPong::CPong() : CBase4618()
{
}

CPong::CPong(cv::Size _Size, int comPort_Num)
{
	_canvas = cv::Mat::zeros(_Size, CV_8UC3); 	//type cv::Mat object in CBase4618
	_base.init_com(comPort_Num);				//type CControl object in CBase4618
 
	//Initialize Ball Parameters
	_Ball.ball_Cords = { BALL_X_START, BALL_Y_START-100 };	 
	_Ball.x_v = -10;
	_Ball.y_v = 1;
	_Ball.x_a = 0;
	_Ball.y_a = 0;

	//Initalise Left Paddle
	paddle_L_Params.pl_Point.x		= PADDLE_LEFT_X;
	paddle_L_Params.pl_Point.y		= PADDLE_LEFT_Y;
	paddle_L_Params.width			= PADDLE_WIDTH;
	paddle_L_Params.height			= PADDLE_HEIGHT;
	paddle_L_Params.pl_rectangle	= cv::Rect(paddle_L_Params.pl_Point.x, paddle_L_Params.pl_Point.y, paddle_L_Params.width, paddle_L_Params.height);

	//Initialize Right Paddle
	paddle_R_Params.pl_Point.x		= PADDLE_RIGHT_X;
	paddle_R_Params.pl_Point.y		= PADDKE_RIGHT_Y;
	paddle_R_Params.width			= PADDLE_WIDTH;
	paddle_R_Params.height			= PADDLE_HEIGHT;
	paddle_R_Params.pl_rectangle	= cv::Rect(paddle_R_Params.pl_Point.x, paddle_R_Params.pl_Point.y, paddle_R_Params.width, paddle_R_Params.height);

	//Initialize Screen Params

	_canvas_Screen_Params.FPS			= 0;
	_canvas_Screen_Params.l_Score		= 0;
	_canvas_Screen_Params.r_Score		= 0;
	_canvas_Screen_Params.player_L_str	= "Player 1: " + std::to_string(_canvas_Screen_Params.l_Score);
	_canvas_Screen_Params.player_R_str	= "Player 2: " + std::to_string(_canvas_Screen_Params.r_Score);
	_canvas_Screen_Params.player_L_Point = cv::Point(150, 80);
	_canvas_Screen_Params.player_R_Point = cv::Point(650, 80);
}

CPong::~CPong()
{
}

void CPong::update()
{
	//Update the ball posistion
	if (( (_Ball.ball_Cords.x - BALL_RADIUS) < 1) || (_Ball.ball_Cords.x + BALL_RADIUS > CANVAS_WIDTH ))
	{		
		_Ball.x_v *= -1;
		//make a score keeping function
			/*
			IF(hit left wall right gets a point)
			else(right left gets a point)
			*/
	}

	if ((_Ball.ball_Cords.y - BALL_RADIUS < 1) || (_Ball.ball_Cords.y + BALL_RADIUS > CANVAS_HEIGHT))
	{
		_Ball.y_v *= -1;
	}


	//need to factor in time
	_Ball.ball_Cords.x += _Ball.x_v + _Ball.x_a;
	_Ball.ball_Cords.y += _Ball.y_v + _Ball.y_a;

	//Update the Paddles Y position
	cv::Point temp;
	_base.get_data(analog, joyStick_Y, temp.y);
	temp.y = (float)temp.y / analog_Convesion_Factor * CANVAS_HEIGHT; // Scales the joy stick to fit the screen

	// Keep the paddle inbounds
	if ((temp.y) > CANVAS_HEIGHT)
	{
		temp.y = CANVAS_HEIGHT;
	}
	else if ((temp.y - PADDLE_HEIGHT) < 0)
	{
		temp.y = PADDLE_HEIGHT;
	}
	paddle_L_Params.pl_rectangle.y = CANVAS_HEIGHT - temp.y;	//Y axis is iverted on the high_GUI

	cv::Point l_Collision_Point = { _Ball.ball_Cords.x - BALL_RADIUS, _Ball.ball_Cords.y }; // Left most position of the ball
	cv::Point r_Collision_Point = { _Ball.ball_Cords.x + BALL_RADIUS, _Ball.ball_Cords.y }; // Right most position of the ball
	if (paddle_L_Params.pl_rectangle.contains(l_Collision_Point))
	{
		if (_Ball.x_v < 0)// turns the ball around if the ball is moving left, other wise ignore it
		{
			_Ball.x_v *= -1;
		}
	}
	else if (paddle_R_Params.pl_rectangle.contains(r_Collision_Point))
	{
		if (_Ball.x_v > 0)// turns the ball around if the ball is moving right, other wise ignore it
		{
			_Ball.x_v *= -1;
		}
	}
}

void CPong::draw()
{	
	//Clear the screen and draws everything after update() has run
	_canvas = cv::Mat::zeros(cv::Size(CANVAS_WIDTH, CANVAS_HEIGHT), CV_8UC3);

	const cv::String test_string = "test";




	//Vertical Center Line
	cv::line(_canvas, cv::Point(LINE_CENTER, 0) , cv::Point(LINE_CENTER, CANVAS_HEIGHT), cv::Scalar(255, 255, 255));

	//Paddle_L
	cv::rectangle(	_canvas,
					paddle_L_Params.pl_rectangle,
					paddle_L_Params.paddle_Colour,
					cv::FILLED);
	
	//Paddle_R
	cv::rectangle(	_canvas, 
					paddle_R_Params.pl_rectangle, 
					paddle_R_Params.paddle_Colour, 
					cv::FILLED);

	//Da Ball
	cv::circle(		_canvas, 
					_Ball.ball_Cords, 
					BALL_RADIUS, 
					cv::Scalar(255, 255, 255), cv::FILLED);
	
	//Score P1/L
	cv::putText(	_canvas,
					_canvas_Screen_Params.player_L_str,
					_canvas_Screen_Params.player_L_Point,
					cv::FONT_HERSHEY_SIMPLEX,
					1.0,
					cv::Scalar(255, 255, 255),2);

	//Score P2/R
	cv::putText(	_canvas,
					_canvas_Screen_Params.player_R_str,
					_canvas_Screen_Params.player_R_Point,
					cv::FONT_HERSHEY_SIMPLEX,
					1.0,
					cv::Scalar(255, 255, 255), 2);
	
					cv::imshow("_canvas", _canvas);
}

void CPong::run()
{

	while (cv::waitKey(1) < 1)
	{
		update();
		draw();
		
		//debug pring
		std:: cout << "X: " << _Ball.ball_Cords.x << "\tY: " << _Ball.ball_Cords.y << std::endl;

	}
}