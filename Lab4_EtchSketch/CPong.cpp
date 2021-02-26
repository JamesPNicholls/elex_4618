#include "stdafx.h"
#include "CPong.h"
#include <chrono>
#include <string>
#include <thread>

using namespace std::chrono;

CPong::CPong() : CBase4618()
{
}

CPong::CPong(cv::Size _Size, int comPort_Num)
{
	_canvas = cv::Mat::zeros(_Size, CV_8UC3); 	//type cv::Mat object in CBase4618
	_base.init_com(comPort_Num);				//type CControl object in CBase4618
	reset_Screen_Parameters();					//Initialize all of the parameters of the polygon structs
	_Ball.ball_Vel = vel_Gen();					//Generates an initial velocity for the ball
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
	left_Paddle_Params.paddle_Point		= { PADDLE_LEFT_X, PADDLE_LEFT_Y };
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
	right_Paddle_Params.paddle_Point	= { PADDLE_RIGHT_X, PADDKE_RIGHT_Y };
	right_Paddle_Params.width			= PADDLE_WIDTH;
	right_Paddle_Params.height			= PADDLE_HEIGHT;
	right_Paddle_Params.pl_rectangle	= { right_Paddle_Params.paddle_Point.x,
											right_Paddle_Params.paddle_Point.y,
											right_Paddle_Params.width,
											right_Paddle_Params.height };

	//Hitbox for the right paddle
	right_Paddle_Params.pl_Hit_Box = { 	right_Paddle_Params.paddle_Point.x,
										right_Paddle_Params.paddle_Point.y,
										right_Paddle_Params.width + 35,
										right_Paddle_Params.height };

	//Screen Params
	_canvas_Screen_Params.FPS = 0;
	_canvas_Screen_Params.fps_Point = FPS_POS;
	_canvas_Screen_Params.player_L_str = "Player 1: " + std::to_string(_canvas_Screen_Params.l_Score);
	_canvas_Screen_Params.player_R_str = "Player 2: " + std::to_string(_canvas_Screen_Params.r_Score);
	_canvas_Screen_Params.player_L_Point = cv::Point(LEFT_SCORE_POS_X, SCORE_TEXT_HEIGHT);
	_canvas_Screen_Params.player_R_Point = cv::Point(RIGHT_SCORE_POS_X, SCORE_TEXT_HEIGHT);

	button_Flag = false;
}

void CPong::update()
{
	//Update Velocity and Acceleration of the ball
	_Ball.current_Time = cv::getTickCount();	
	double delta_Time = (_Ball.current_Time - _Ball.old_Time) / cv::getTickFrequency();

	_Ball.ball_Cords.x += _Ball.ball_Vel.x * delta_Time; //d = v*t
	_Ball.ball_Cords.y += _Ball.ball_Vel.y * delta_Time;

	//Update Position
	if (((_Ball.ball_Cords.x - BALL_RADIUS) < 1)) //If the ball hits left wall the right player gets a point
	{
		_canvas_Screen_Params.r_Score++;
		_Ball.ball_Vel = vel_Gen();			//Give the ball a new velovity
		reset_Screen_Parameters();			//reset the screen
	}
	if ((_Ball.ball_Cords.x + BALL_RADIUS) > PONG_CANVAS_WIDTH)
	{
		_canvas_Screen_Params.l_Score++;
		_Ball.ball_Vel = vel_Gen();
		reset_Screen_Parameters();
	}

	if (((_Ball.ball_Cords.y - BALL_RADIUS) < 0) || ((_Ball.ball_Cords.y + BALL_RADIUS) > PONG_CANVAS_HEIGHT))
	{
		_Ball.ball_Vel.y *= -1;
	}
	_Ball.old_Time = cv::getTickCount();

	if (_canvas_Screen_Params.l_Score == 5 || _canvas_Screen_Params.r_Score == 5)
	{
		reset_Screen_Parameters();
		_Ball.ball_Vel = vel_Gen();
		_canvas_Screen_Params.l_Score = 0;
		_canvas_Screen_Params.r_Score = 0;
		return;
	}

	//Update the Left Paddles Y position
	cv::Point temp = { 0,0 };
	_base.get_data(analog, joyStick_Y, temp.y);

	temp.y = temp.y * PONG_CANVAS_HEIGHT / analog_Convesion_Factor; // Scales the joy stick to fit the screen


	// Check if its out of bounds
	if ((temp.y) > PONG_CANVAS_HEIGHT)
	{
		temp.y = PONG_CANVAS_HEIGHT;
	}
	else if ((temp.y - PADDLE_HEIGHT) < 0)
	{
		temp.y = PADDLE_HEIGHT;
	}
	left_Paddle_Params.pl_rectangle.y = PONG_CANVAS_HEIGHT - temp.y;	//Y axis is iverted on the high_GUI
	left_Paddle_Params.pl_Hit_Box.y = PONG_CANVAS_HEIGHT - temp.y;		//Hit box follows the paddle


	//sets the Right paddle & hitbox to track the ball
	right_Paddle_Params.pl_rectangle.y = _Ball.ball_Cords.y - PADDLE_HEIGHT / 2;
	right_Paddle_Params.pl_Hit_Box.y = _Ball.ball_Cords.y - PADDLE_HEIGHT / 2;

	//Collision Detection
	if (left_Paddle_Params.pl_Hit_Box.contains(_Ball.ball_Cords))
	{
		if (_Ball.ball_Vel.x < 0)// turns the ball around if the ball is moving left, other wise ignore its
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

	//Reset the game if PB1 is pushed
	if (_base.get_button(push_Button1, button_Flag) == true)	//Get button is super slow like 20ms slow idk why yet
	{
		reset_Screen_Parameters();
		_Ball.ball_Vel = vel_Gen();
		_canvas_Screen_Params.l_Score = 1;
		_canvas_Screen_Params.r_Score = 0;
	}
}//void CPong::update

cv::Point CPong::vel_Gen()
{
	cv::Point value;
	srand(time(NULL));
	
	//Generate a random value to be added to the the x&y base values to add some randomness to the ball movement
	value = { rand() % X_VELOCITY_OFFSET , rand() % Y_VELOCITY_OFFSET }; 

	if((value.x % 2) == 0 )
	{
		//Adds the offset value to the base value 
		value.x = (X_VELOCITY_BASE_VALUE + value.x)*-1; //negative v if even
	}
	else
	{
		value.x = X_VELOCITY_BASE_VALUE + value.x;	//positive v if odd
	}

	if ((value.y % 2) == 0)
	{
		value.y = (Y_VELOCITY_BASE_VALUE + value.y)*-1;
	}
	else
	{
		value.y = Y_VELOCITY_BASE_VALUE + value.y;
	}
	return value;
}//cv::Point CPong::vel_Gen()

void CPong::draw()
{	
		long int freq_t, end_t, start_t;
		freq_t = cv::getTickFrequency();

		auto start = system_clock::now();
		auto end = start + milliseconds(5); //30 Hz

		//Clear the screen and draws everything after update() has run	
		_canvas = black_Canvas;
		cv::imshow("_canvas", _canvas);

		//Vertical Center Line
		cv::line(_canvas,
			cv::Point(LINE_CENTER, 0),
			cv::Point(LINE_CENTER, PONG_CANVAS_HEIGHT),
			cv::Scalar(255, 255, 255));

		//Left Paddle
		cv::rectangle(_canvas,
			left_Paddle_Params.pl_rectangle,
			left_Paddle_Params.paddle_Colour,
			cv::FILLED);


		//Right Paddle
		cv::rectangle(_canvas,
			//right_Paddle_Params.pl_Hit_Box, 	//<-hit box testing
			right_Paddle_Params.pl_rectangle,
			cv::Scalar(100, 0, 0),
			cv::FILLED);

		//Da Ball
		cv::circle(_canvas,
			_Ball.ball_Cords,
			BALL_RADIUS,
			cv::Scalar(255, 255, 255),
			cv::FILLED);

		//Left Player Score
		cv::putText(_canvas,
			_canvas_Screen_Params.player_L_str,
			_canvas_Screen_Params.player_L_Point,
			cv::FONT_HERSHEY_SIMPLEX,
			1.0,
			cv::Scalar(255, 255, 255),
			2);

		//Right Player Score 
		cv::putText(_canvas,
			_canvas_Screen_Params.player_R_str,
			_canvas_Screen_Params.player_R_Point,
			cv::FONT_HERSHEY_SIMPLEX,
			1.0,
			cv::Scalar(255, 255, 255),
			2);

		//FPS
		cv::putText(_canvas,
			std::to_string(_canvas_Screen_Params.FPS),
			_canvas_Screen_Params.fps_Point,
			cv::FONT_HERSHEY_SIMPLEX,
			1.0,
			cv::Scalar(255, 255, 255),
			2);

		
		cv::imshow("_canvas", _canvas);
		std::this_thread::sleep_until(end);		
		start_t = start.time_since_epoch().count(); //Converts the std::chrono time_point into a usable integer;
		end_t = end.time_since_epoch().count();
		_canvas_Screen_Params.FPS = freq_t / (end_t - start_t);

		if (cv::waitKey(1) == 'q')
		{
			exit_Flag = true;
		}

}//void CPong::draw()

void CPong::run()
{
	update_Thread_Exit_Flag = false; //thread flag gets set
	draw_Thread_Exit_Flag = false;
	exit_Flag = false;

	start_Thread();//completes update() and draw() threads
	while (exit_Flag == false)
	{
	}

	draw_Thread_Exit_Flag = true;
	update_Thread_Exit_Flag = true;

	std::this_thread::sleep_for(std::chrono::microseconds(300));
}//void CPong::run()

void CPong::start_Thread()
{	
	std::thread t1(&CPong::update_Thread, this);
	std::thread t2(&CPong::draw_Thread, this);
	
	t1.detach();
	t2.detach();
}

void CPong::update_Thread(CPong* ptr)
{
	while (ptr->update_Thread_Exit_Flag == false)
	{
		ptr->update();
	}
}

void CPong::draw_Thread(CPong* ptr)
{
	while (ptr->draw_Thread_Exit_Flag == false)
	{
		ptr->draw();
	}
}
