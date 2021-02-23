#include "stdafx.h"
#include "CAsteroid.h"

CAsteroid::CAsteroid()
{
	_position 	= { (rand() % 800),( rand() % 800 ) };
	_velocity 	= { 1,1 };
	_radius 	= (float)rand() / (float)RAND_MAX * 200+10;
	_lives 		= 0;
	_colour 	= {200,200,200};
	
}

CAsteroid::~CAsteroid()
{

}