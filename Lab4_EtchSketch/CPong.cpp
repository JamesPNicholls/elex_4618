#include "stdafx.h"
#include "CPong.h"

CPong::CPong() : CBase4618()
{
	// Stuff to make
	// The ball
	// Two paddles

}

CPong::CPong(cv::Size _Size, int comPort_Num)
{
	_canvas = cv::Mat::zeros(_Size, CV_8UC3); 	//type cv::Mat object in CBase4618
	_base.init_com(comPort_Num);				//type CControl object in CBase4618
 
	//initalising the parameters for the ball and paddles
	_Ball.ball_Cords = { BALL_X_START, BALL_Y_START-100 };
	
	_Ball.x_v = 1;
	_Ball.y_v = 1;

	_Ball.x_a = 0;
	_Ball.y_a = 0;

	// Initialising the paddle coordinates
	//paddle_L.point_1 = { 40, 450 };
	//paddle_L.point_2 = { 50, 550 };
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
	}

	if ((_Ball.ball_Cords.y - BALL_RADIUS < 1) || (_Ball.ball_Cords.y + BALL_RADIUS > CANVAS_HEIGHT))
	{
		_Ball.y_v *= -1;
	}

	_Ball.ball_Cords.x += _Ball.x_v + _Ball.x_a;
	_Ball.ball_Cords.y += _Ball.y_v + _Ball.y_a;

	//Update the Paddle position

	_base.get_data(analog, joyStick_Y, paddle_L.pl_Point.y);
	
}

void CPong::draw()
{	
	//Clear the screen and draws everything after update() has run
	_canvas = cv::Mat::zeros(cv::Size(CANVAS_WIDTH, CANVAS_HEIGHT), CV_8UC3);

	//Vertical Center Line
	cv::line(_canvas, cv::Point(LINE_CENTER, 0) , cv::Point(LINE_CENTER, CANVAS_HEIGHT), cv::Scalar(255, 255, 255));
	
	//Text


	//Paddle_L	
	cv::rectangle(_canvas, cv::Rect(paddle_L.pl_Point.x, paddle_L.pl_Point.y, paddle_L.width, paddle_L.height), cv::Scalar(255, 255, 255), cv::FILLED);
	
	//Paddle_R

	//Da Ball
	cv::circle(_canvas, _Ball.ball_Cords, BALL_RADIUS, cv::Scalar(255, 255, 255), cv::FILLED);
	cv::imshow("_canvas", _canvas);
}

void CPong::run()
{

	while (cv::waitKey() < 1)
	{
		update();
		draw();
		
		//debug pring
		std:: cout << "X: " << _Ball.ball_Cords.x << "\tY: " << _Ball.ball_Cords.y << std::endl;

	}
}