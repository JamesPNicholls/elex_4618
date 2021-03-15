#pragma once
#include "CBase4618.h"
class CImage_Ex : public CBase4618
{

/** Todo
*	Make it talk to the camera
*	make it find an image on the camera
*	make it repsond to colour
*	port to linux
* 
*/
public:
	CImage_Ex();
	~CImage_Ex();
	void run();

private:
	void update();
	void draw();
};

