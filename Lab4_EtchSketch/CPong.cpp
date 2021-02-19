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
	_Ball.ball_Vel = vel_Gen();
}

CPong::~CPong()
{

}

void CPong::reset_Screen_Parameters()
{
	//Ball Parameters, can add some randomness in here for the start velocities
	_Ball.ball_Cords	= { BALL_X_START, BALL_Y_START};
	_Ball.current_Time	= cv::getTickCount();
	_Ball.old_Time		= cv::getTickCount();
	
	//Left Paddle
	left_Paddle_Params.paddle_Point.x	= PADDLE_LEFT_X;
	left_Paddle_Params.paddle_Point.y	= PADDLE_LEFT_Y;
	left_Paddle_Params.width			= PADDLE_WIDTH;
	left_Paddle_Params.height			= PADDLE_HEIGHT;
	left_Paddle_Params.pl_rectangle		= { left_Paddle_Params.paddle_Point.x,
											left_Paddle_Params.paddle_Point.y,
											left_Paddle_Params.width,
											left_Paddle_Params.height };

	//hitbox for the left paddle
	left_Paddle_Params.pl_Hit_Box		= { left_Paddle_Params.paddle_Point.x-30,
											left_Paddle_Params.paddle_Point.y,
											left_Paddle_Params.width + 25,
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

	//Hitbox for the right paddle
	right_Paddle_Params.pl_Hit_Box = { right_Paddle_Params.paddle_Point.x,
										right_Paddle_Params.paddle_Point.y,
										right_Paddle_Params.width + 35,
										right_Paddle_Params.height };


	//Screen Params
	_canvas_Screen_Params.FPS = 0;
	_canvas_Screen_Params.player_L_str = "Player 1: " + std::to_string(_canvas_Screen_Params.l_Score);
	_canvas_Screen_Params.player_R_str = "Player 2: " + std::to_string(_canvas_Screen_Params.r_Score);
	_canvas_Screen_Params.player_L_Point = cv::Point(LEFT_SCORE_POS_X, SCORE_TEXT_HEIGHT);
	_canvas_Screen_Params.player_R_Point = cv::Point(RIGHT_SCORE_POS_X, SCORE_TEXT_HEIGHT);
}

void CPong::update()
{

	//Update Velocity and Acceleration of the ball
	_Ball.current_Time = cv::getTickCount();
	double delta_Time = (_Ball.current_Time - _Ball.old_Time) / cv::getTickFrequency();

	if (((_Ball.ball_Cords.x - BALL_RADIUS) < 1))
	{
		_canvas_Screen_Params.r_Score++;
		_Ball.ball_Vel = vel_Gen();
		reset_Screen_Parameters();
	}
	if (_Ball.ball_Cords.x + BALL_RADIUS > PONG_CANVAS_WIDTH)
	{
		_canvas_Screen_Params.l_Score++;
		_Ball.ball_Vel = vel_Gen();
		reset_Screen_Parameters();
	}

	if (((_Ball.ball_Cords.y - BALL_RADIUS) < 0) || ((_Ball.ball_Cords.y + BALL_RADIUS) > PONG_CANVAS_HEIGHT))
	{
		_Ball.ball_Vel.y *= -1;
	}

	//Update the ball posistion
	_Ball.ball_Cords.x += _Ball.ball_Vel.x * delta_Time;
	_Ball.ball_Cords.y += _Ball.ball_Vel.y * delta_Time;


	//Update the Left Paddles Y position
	cv::Point temp = { 0,0 };
	_base.get_data(analog, joyStick_Y, temp.y);
	temp.y = temp.y * PONG_CANVAS_HEIGHT / analog_Convesion_Factor; // Scales the joy stick to fit the screen

	// Keep the paddle inbounds
	if ((temp.y) > PONG_CANVAS_HEIGHT)
	{
		temp.y = PONG_CANVAS_HEIGHT;
	}
	else if ((temp.y - PADDLE_HEIGHT) < 0)
	{
		temp.y = PADDLE_HEIGHT;
	}
	left_Paddle_Params.pl_rectangle.y = PONG_CANVAS_HEIGHT - temp.y;
	left_Paddle_Params.pl_Hit_Box.y = PONG_CANVAS_HEIGHT - temp.y;	//Y axis is iverted on the high_GUI


	//sets the Right paddle to track the ball
	right_Paddle_Params.pl_rectangle.y = _Ball.ball_Cords.y - PADDLE_HEIGHT / 2;
	right_Paddle_Params.pl_Hit_Box.y = _Ball.ball_Cords.y - PADDLE_HEIGHT / 2;

	//Collision Detection
	if (left_Paddle_Params.pl_Hit_Box.contains(_Ball.ball_Cords))
	{
		if (_Ball.ball_Vel.x < 0)// turns the ball around if the ball is moving left, other wise ignore it
		{
			_Ball.ball_Vel.x *= -1;
		}
	}
	else if (right_Paddle_Params.pl_Hit_Box.contains(_Ball.ball_Cords))
	{
		if (_Ball.ball_Vel.x > 0)// turns the ball around if the ball is moving right, other wise ignore it
		{
			_Ball.ball_Vel.x *= -1;
		}
	}

	////Get button is super slow like 20ms slow idk why yet
	if (_base.get_button(push_Button1))
	{
		reset_Screen_Parameters();
		_Ball.ball_Vel = vel_Gen();
	}
	_Ball.old_Time = cv::getTickCount();
}

cv::Point CPong::vel_Gen()
{
	cv::Point value;
	srand(time(NULL));
	value.x = rand() % 600;
	value.y = rand() % 150;

	if((value.x % 2) == 0 )
	{
		value.x = (1300 + value.x)*-1; //negative if even
	}
	else
	{
		value.x = 1300 + value.x;	//positive if odd
	}

	if ((value.y % 2) == 0)
	{
		value.y = (300 + value.y)*-1;
	}
	else
	{
		value.y = 300 + value.y;
	}
	return value;
}
void CPong::draw()
{	
	//Clear the screen and draws everything after update() has run
	
	_canvas = black_Canvas;

	//Vertical Center Line
	cv::line(		_canvas,
					cv::Point(LINE_CENTER, 0),
					cv::Point(LINE_CENTER, PONG_CANVAS_HEIGHT),
					cv::Scalar(255, 255, 255));

	//Left Paddle
	cv::rectangle(	_canvas,
					left_Paddle_Params.pl_rectangle,
					left_Paddle_Params.paddle_Colour,
					cv::FILLED);

	
	//Right Paddle
	cv::rectangle(	_canvas,
					//right_Paddle_Params.pl_Hit_Box,  hit box testing
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
	//FPS
	//cv::putText(	_canvas,
	//				_canvas_Screen
	//
	cv::imshow("_canvas", _canvas);
}

void CPong::run()
{
	float start, end, freq;
	freq = cv::getTickFrequency();
	while (cv::waitKey(1) != 'q')
	{
		start = cv::getTickCount();
		auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(33);// 30 Hz
		update();
		std::this_thread::sleep_until(end_time);
		
		draw();
		end = cv::getTickCount();
		_canvas_Screen_Params.FPS = 1 / ((end - start) / freq);
	}
}