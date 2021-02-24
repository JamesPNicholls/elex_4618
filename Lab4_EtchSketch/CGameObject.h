#pragma once
#include "stdafx.h"

#define X_VELOCITY_OFFSET 		200
#define X_VELOCITY_BASE_VALUE	80

#define Y_VELOCITY_OFFSET		200
#define Y_VELOCITY_BASE_VALUE	1

using namespace cv;

class CGameObject
{
protected:
	Point2i _position;
	Point2f _velocity;
	int _radius;
	int _lives;
	Scalar _colour;

	float new_time;
	float old_time;

public:

	void move();
	bool collide(CGameObject& obj);
	bool collide_wall(Size board);
	void hit();

	int get_lives() { return _lives; }
	void set_lives(int lives) { _lives = lives; }

	void set_pos(Point2f pos) { _position = pos; }
	Point2f get_pos();
	void draw(Mat& im);

};

