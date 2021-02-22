#include "stdafx.h"
#include "CGameObject.h"

void CGameObject::move()
{

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

}