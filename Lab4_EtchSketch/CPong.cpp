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


}

CPong::~CPong()
{

}

void CPong::update()
{
}

void CPong::draw()
{	
	cv::imshow("_canvas", _canvas);
}

void CPong::run()
{
	while(cv::waitKey(1) < 0 )
	{
		std::cout << "Waiting..." << std::endl;
		draw(); 
	}
}