//#include "stdafx.h"
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
	while (cv::waitKey(1) != 'q')
	{
		update();
		draw();
	}
}

void CBase4618::init_RGB_LED()
{
	for (int i = 0; i < 3; i++)
	{
		_base.set_data(digital, RGBLED_OFFSET + i, RGB_OFF);
	}
	_base.set_data(digital, RGBLED_BLU_PIN, RGB_ON);
}
