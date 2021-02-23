#include "stdafx.h"
#include "CShip.h"

CShip::CShip()
{
	//random init values
	_position	= { 500,500 };
	_velocity	= { 10,10 };
	_radius		= 10;
	_lives		= 3;
	_colour 	= {0,150,0};
}

CShip::~CShip()
{

}