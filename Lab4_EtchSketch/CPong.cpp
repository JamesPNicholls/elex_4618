#include "stdafx.h"
#include "CPong.h"
#include <chrono>
#include <string>
#include <thread>

CPong::CPong() : CBase4618()
{
}

CPong::CPong(cv::Size _Size, int comPort_Num)
{
	_canvas = cv::Mat::zeros(_Size, CV_8UC3); 	//type cv::Mat object in CBase4618
	_base.init_com(comPort_Num);				//type CControl object in CBase4618
	reset_Screen_Parameters();					//Initialize all of the param structs
}

CPong::~CPong()
{

}

void CPong::reset_Screen_Parameters()
{
	//Ball Parameters
	_Ball.ball_Cords = { BALL_X_START, BALL_Y_START}; //randomizses the balls start position
	_Ball.x_v = 13;
	_Ball.y_v = 7;
	_Ball.x_a = 0;
	_Ball.y_a = 0;

	//Left Paddle
	left_Paddle_Params.paddle_Point.x	= PADDLE_LEFT_X;
	left_Paddle_Params.paddle_Point.y	= PADDLE_LEFT_Y;
	left_Paddle_Params.width			= PADDLE_WIDTH;
	left_Paddle_Params.height			= PADDLE_HEIGHT;
	left_Paddle_Params.pl_rectangle		= { left_Paddle_Params.paddle_Point.x,
											left_Paddle_Params.paddle_Point.y,
											left_Paddle_Params.width,
											left_Paddle_Params.height };

	//Right Paddle
	right_Paddle_Params.paddle_Point.x	= PADDLE_RIGHT_X;
	right_Paddle_Params.paddle_Point.y	= PADDKE_RIGHT_Y;
	right_Paddle_Params.width			= PADDLE_WIDTH;
	right_Paddle_Params.height			= PADDLE_HEIGHT;
	right_Paddle_Params.pl_rectangle	= { right_Paddle_Params.paddle_Point.x,
											right_Paddle_Params.paddle_Point.y,
											right_Paddle_Params.width,
											right_Paddle_Params.height };

	//Screen Params
	_canvas_Screen_Params.FPS			= 0;
	_canvas_Screen_Params.l_Score		= 0;
	_canvas_Screen_Params.r_Score		= 0;
	_canvas_Screen_Params.player_L_str	= "Player 1: " + std::to_string(_canvas_Screen_Params.l_Score);
	_canvas_Screen_Params.player_R_str	= "Player 2: " + std::to_string(_canvas_Screen_Params.r_Score);
	_canvas_Screen_Params.player_L_Point = cv::Point(LEFT_SCORE_POS_X, SCORE_TEXT_HEIGHT);
	_canvas_Screen_Params.player_R_Point = cv::Point(RIGHT_SCORE_POS_X, SCORE_TEXT_HEIGHT);
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


	//Update the Left Paddles Y position
	cv::Point temp;
	_base.get_data(analog, joyStick_Y, temp.y);
	temp.y = temp.y * CANVAS_HEIGHT / analog_Convesion_Factor; // Scales the joy stick to fit the screen

	// Keep the paddle inbounds
	if ((temp.y) > CANVAS_HEIGHT)
	{
		temp.y = CANVAS_HEIGHT;
	}
	else if ((temp.y - PADDLE_HEIGHT) < 0)
	{
		temp.y = PADDLE_HEIGHT;
	}
	left_Paddle_Params.pl_rectangle.y = CANVAS_HEIGHT - temp.y;	//Y axis is iverted on the high_GUI

	//sets the Right paddle to track the ball
	right_Paddle_Params.pl_rectangle.y = _Ball.ball_Cords.y - PADDLE_HEIGHT/2;


	//Collision Detection
	cv::Point left_Collision_Point = { _Ball.ball_Cords.x - BALL_RADIUS, _Ball.ball_Cords.y }; // Left most position of the ball
	cv::Point right_Collision_Point = { _Ball.ball_Cords.x + BALL_RADIUS, _Ball.ball_Cords.y }; // Right most position of the ball
	if (left_Paddle_Params.pl_rectangle.contains(left_Collision_Point))
	{
		if (_Ball.x_v < 0)// turns the ball around if the ball is moving left, other wise ignore it
		{
			_Ball.x_v *= -1;
		}
	}
	else if (right_Paddle_Params.pl_rectangle.contains(right_Collision_Point))
	{
		if (_Ball.x_v > 0)// turns the ball around if the ball is moving right, other wise ignore it
		{
			_Ball.x_v *= -1;
		}
	}	

	//Get button is super slow like 20ms slow idk why yet
	if (_base.get_button(push_Button1))
	{
		reset_Screen_Parameters();
	}
}



void CPong::draw()
{	
	//Clear the screen and draws everything after update() has run
	
	_canvas = black_Canvas;

	//Vertical Center Line
	cv::line(		_canvas,
					cv::Point(LINE_CENTER, 0),
					cv::Point(LINE_CENTER, CANVAS_HEIGHT),
					cv::Scalar(255, 255, 255));

	//Left Paddle
	cv::rectangle(	_canvas,
					left_Paddle_Params.pl_rectangle,
					left_Paddle_Params.paddle_Colour,
					cv::FILLED);
	
	//Right Paddle
	cv::rectangle(	_canvas,
					right_Paddle_Params.pl_rectangle,
					right_Paddle_Params.paddle_Colour,
					cv::FILLED);

	//Da Ball
	cv::circle(		_canvas,
					_Ball.ball_Cords,
					BALL_RADIUS,
					cv::Scalar(255, 255, 255),
					cv::FILLED);
	
	//Left Player Score
	cv::putText(	_canvas,
					_canvas_Screen_Params.player_L_str,
					_canvas_Screen_Params.player_L_Point,
					cv::FONT_HERSHEY_SIMPLEX,
					1.0,
					cv::Scalar(255, 255, 255),
					2);

	//Right Player Score
	cv::putText(	_canvas,
					_canvas_Screen_Params.player_R_str,
					_canvas_Screen_Params.player_R_Point,
					cv::FONT_HERSHEY_SIMPLEX,
					1.0,
					cv::Scalar(255, 255, 255), 
					2);
	
	cv::imshow("_canvas", _canvas);
}

void CPong::run()
{	
	while (cv::waitKey(1) != 'q')
	{
		auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(33);// 30 Hz
		update();
		std::this_thread::sleep_until(end_time);
		draw();
		//std::cout  << "Update: " << std::setprecision(2) << update_end << "\tDraw: " << std::setprecision(4) << draw_end << std::endl;
	}
}