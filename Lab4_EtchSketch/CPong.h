#pragma once
#include "stdafx.h"
#include "CBase4618.h"
class CPong : public CBase4618
{

private:
	void update();
	void draw();

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
	~CPong();

	void run();
};

