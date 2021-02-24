#include "stdafx.h"
#include "CMissle.h"

CMissle::CMissle()
{
    _velocity = {0,-300}; //shoots straight up
    _radius = 1;
    _colour = {255,255, 255};

    new_time = cv::getTickCount();
    old_time = cv::getTickCount();
}

CMissle::~CMissle()
{

}