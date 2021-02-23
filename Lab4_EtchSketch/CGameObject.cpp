#include "stdafx.h"
#include "CGameObject.h"
 
using namespace cv;

void CGameObject::move()
{
	Point2i temp = {rand()%10+1, rand()%10+1};
	_velocity = { 2*temp.x - temp.x, 2*temp.y - temp.y };// makes negative vels 
	_position += _velocity;	

}

bool CGameObject::collide(CGameObject& obj)
{
	return true;
}
bool CGameObject::collide_wall(Size board)
{
	return true;
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
	return Point2f(0,0);
}