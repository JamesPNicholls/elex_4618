#pragma once
#include "stdafx.h"
#include "CBase4618.h"

#include "CAsteroid.h"
#include "CMissle.h"
#include "CShip.h"

#include <vector>

using namespace std;
class CAsteroid_Game : public CBase4618
{
private:
	void update();
	void draw();
	
	vector <CAsteroid>	asteroid_Vector;
	vector <CMissle>	missle_Vector;
	CShip				_ship;

public:
	CAsteroid_Game();
	~CAsteroid_Game();
	void run();
};
 