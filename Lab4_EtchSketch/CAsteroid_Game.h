#pragma once
#include "stdafx.h"
#include "CBase4618.h"
#include <vector>

#include "CMissle.h"
#include "CShip.h"
#include "CAsteroid.h"

/** Stuff to do
*	Draw ship
*		Control ship with joy
*		Dir controls, for movement
*		stay in bounds
*		die
*	
*	Draw Asteroid
*		make them appear at random
*		make them move at random
*		make them explode from projectile
*		kill ship
*		
*	Shoot Missle
*		spawn from ship
*		destroy asteroid
*			gain score
* 
*/

using namespace std;
class CAsteroid_Game : CBase4618
{
private:
	void update();
	void draw();

	//vector <CAsteroid>	asteroid_Vector;
	//vector <CMissle>	missle_Vector;

	CShip test;

public:
	CAsteroid_Game();
	CAsteroid_Game(cv::Size _size, int comPort_Num);
	~CAsteroid_Game();
	void run();
};
