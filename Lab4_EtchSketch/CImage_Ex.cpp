#include "stdafx.h"
#include "CImage_Ex.h"

CImage_Ex::CImage_Ex()
{

}

CImage_Ex::~CImage_Ex()
{

}

void CImage_Ex::update()
{
}

void  CImage_Ex::draw()
{

}

void  CImage_Ex::run()
{
	//Craig Sample Code

	cv::VideoCapture vid; //video object
	vid.open(0);
	if (vid.isOpened() == TRUE)
	{
		do
		{
			cv::Mat frame, edges;
			vid >> frame;
			if (frame.empty() == false)
			{
				cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
				cv::GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);
				cv::Canny(edges, edges, 0, 30, 3);
		
				cv::imshow("edges", edges);
			}
		} while (cv::waitKey(10) != ' ');
	}
}