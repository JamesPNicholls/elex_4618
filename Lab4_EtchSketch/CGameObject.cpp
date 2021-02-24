#include "stdafx.h"
#include "CGameObject.h"
#include <chrono>
#include <math.h>

using namespace cv;

void CGameObject::move()
{
	//Generate a random value to be added to the the x&y base values to add some randomness to the ball 
	new_time = getTickCount();
	double delta_t = (new_time - old_time) / cv::getTickFrequency();
	old_time = getTickCount();
	
	_position.x += _velocity.x * delta_t;
	_position.y += _velocity.y * delta_t;
}

bool CGameObject::collide(CGameObject& obj)
{
	bool result = false;
	Point2i distance_From_Center = obj._position - _position; 
	int radius_Sum = obj._radius + _radius;

	//distance between the two centers
	int mag = hypot(distance_From_Center.x, distance_From_Center.y);
	
	if( radius_Sum > mag)
	{
		result = true;
		std::cout << "hit\n";
	}

	return result;
}
bool CGameObject::collide_wall(Size board)
{
	bool result = false;
	if (_position.x < 0 || _position.x > board.width || _position.y < 0 || _position.y > board.height)
	{
		result = true;
	}
	return result;
}

void CGameObject::hit()
{

}

void CGameObject::draw(Mat& im)
{
	circle(im, _position, _radius, _colour, 1, 1);
}

Point2f CGameObject::get_pos()
{
	return _position;
}