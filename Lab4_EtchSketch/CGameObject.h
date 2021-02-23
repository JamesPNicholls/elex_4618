#pragma once

using namespace cv;
class CGameObject
{
protected:
	Point2f _position;
	Point2f _velocity;
	int _radius;
	int _lives;

public:
	void move();
	bool collide(CGameObject& obj);
	bool collide_wall(Size board);
	void hit();
	int get_lives() { return _lives; }
	void set_lives(int lives) { _lives = lives; }
	void set_pos(Point2f pos) { _position = pos; }
	Point2f get_pos() { return _position; }
	void draw(Mat& im);

};

