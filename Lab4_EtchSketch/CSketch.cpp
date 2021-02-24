#include "stdafx.h"
#include "CSketch.h"

/********************
	CSketch Methods
*********************/

CSketch::CSketch() : CBase4618()
{

}

CSketch::CSketch(cv::Size _Size, int commPort_Num) : CBase4618()
{
	_canvas = cv::Mat::zeros(_Size, CV_8UC3);
	_base.init_com(commPort_Num);
	init_RGB_LED();

	current_XY_Cords.x = new_XY_Cords.x = ETCH_CANVAS_WIDTH / 2;
	current_XY_Cords.x = new_XY_Cords.y = ETCH_CANVAS_WIDTH / 2;
}

CSketch::~CSketch()
{

}

void CSketch::update()
{
	bool is_Button_Pushed = _base.get_button(push_Button2);

	if (is_Button_Pushed == true)
	{
		if (current_Colour[0] != 0) //GRN On, BLU Off
		{
			current_Colour[1] = 255;
			current_Colour[0] = 0;

			_base.set_data(digital, RGBLED_BLU_PIN, RGB_OFF);
			_base.set_data(digital, RGBLED_GRN_PIN, RGB_ON);
		}
		else if (current_Colour[1] != 0)//RED On, GRN Off
		{
			current_Colour[2] = 255;
			current_Colour[1] = 0;

			_base.set_data(digital, RGBLED_RED_PIN, RGB_ON);
			_base.set_data(digital, RGBLED_GRN_PIN, RGB_OFF);
		}
		else if (current_Colour[2] != 0)//BLU On, RED Off
		{
			current_Colour[0] = 255;
			current_Colour[2] = 0;

			_base.set_data(digital, RGBLED_BLU_PIN, RGB_ON);
			_base.set_data(digital, RGBLED_RED_PIN, RGB_OFF);
		}
	}

	//Records the current XY Pos
	current_XY_Cords = new_XY_Cords;

	//retrieves the new analog coordinates
	_base.get_data(analog, joyStick_X, new_XY_Cords.x);
	_base.get_data(analog, joyStick_Y, new_XY_Cords.y);

	// In order to reach the corners of the screen the joy stick is mapped to a region that is larger than the space on _canvas
	// It than checks to make sure that coordinates are within the drawing space and wont allow them to go off screen.
	new_XY_Cords.x = new_XY_Cords.x * CANVAS_W_DRAW / analog_Convesion_Factor  - DRAW_CANVAS_OFFSET;
	new_XY_Cords.y = CANVAS_H_DRAW - (new_XY_Cords.y * CANVAS_H_DRAW / analog_Convesion_Factor ) - DRAW_CANVAS_OFFSET;

	if (new_XY_Cords.x < 0)
	{
		new_XY_Cords.x = 0;
	}
	else if (new_XY_Cords.x > ETCH_CANVAS_WIDTH)
	{
		new_XY_Cords.x = ETCH_CANVAS_WIDTH;
	}

	if (new_XY_Cords.y < 0)
	{
		new_XY_Cords.y = 0;
	}
	else if (new_XY_Cords.y > (ETCH_CANVAS_HEIGHT))
	{
		new_XY_Cords.y = ETCH_CANVAS_HEIGHT;
	}

	//Clears the screen if PB1 is pushed
	is_Button_Pushed = _base.get_button(push_Button1);
	if (is_Button_Pushed)
	{
		_canvas = cv::Scalar(0, 0, 0);
	}
}

void CSketch::draw()
{
	cv::line(_canvas, current_XY_Cords, new_XY_Cords, current_Colour, 2);
	cv::imshow("_canvas", _canvas);
}
/* CSketch Methods*/
