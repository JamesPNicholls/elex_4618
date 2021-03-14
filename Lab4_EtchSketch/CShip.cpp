#include "stdafx.h"
#include "CShip.h"

CShip::CShip()
{
	//random init values
	_position	= { 100,100 };
	_velocity	= { 10,10 };
	_radius		= 25;
	_lives		= 1;
	_colour 	= {0,150,0};

}

CShip::~CShip()
{

}