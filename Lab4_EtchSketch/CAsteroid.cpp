#include "stdafx.h"
#include "CAsteroid.h"

CAsteroid::CAsteroid()
{

	//TLDR of what this does
	// spawn an asteroid on the end of the screen 
	// if on left move right
	//	 give a random up down
	// if on the top move down
		//give a random left right
	//the do not spawn on the right or bottom edge
	
	if (rand() % 2 == 1)
	{
		_position = { rand() % 900 + 100, 0 };
		_velocity.y = rand() % Y_VELOCITY_BASE_VALUE + Y_VELOCITY_OFFSET;
		_velocity.x = rand() % X_VELOCITY_BASE_VALUE + X_VELOCITY_OFFSET;
		if ((int)_velocity.x % 2 == 0)
		{
			_velocity.x *= -1;
		}
	}
	else
	{
		_position = { 0 , rand() % 900 + 100};
		_velocity.x = rand() % X_VELOCITY_BASE_VALUE + X_VELOCITY_OFFSET;
		_velocity.y = rand() % Y_VELOCITY_BASE_VALUE + Y_VELOCITY_OFFSET;
		if (((int)_velocity.y % 2) == 0)
		{
			_velocity.y *= -1;
		}
	}//Gives the asteroid a fixed random  velocity because simulating the travel path is too hard

	_radius 	= (float)rand() / (float) RAND_MAX * 50+10;
	_lives 		= 1;
	_colour 	= {200,200,200};

	//Initialize the times otherwise it goes crazy
	new_time = cv::getTickCount();
	old_time = cv::getTickCount();
	
}

CAsteroid::~CAsteroid()
{

}