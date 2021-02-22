#pragma once
#include "CBase4618.h"

class CAsteroid_Game : public CBase4618
{
private:
	void update();
	void draw();

public:
	CAsteroid_Game();
	~CAsteroid_Game();
	void run();
};
 