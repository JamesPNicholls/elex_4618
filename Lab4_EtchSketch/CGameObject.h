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

	/**
	 * @brief Postion of the object
	 * 
	 */
	Point2i _position;

	/**
	 * @brief Current velocity of object
	 * used by CAsteroid and CMissle
	 * 
	 */
	Point2f _velocity;

	/**
	 * @brief Radius of each object,
	 * All objects are spheres
	 * 
	 */
	int _radius;

	/**
	 * @brief Player lives
	 * Trigger a game over when 0
	 * 
	 */
	int _lives;

	/**
	 * @brief Colour of the each object
	 * 
	 */
	Scalar _colour;

	/**
	 * @brief Timing paramter used for position calculaions of the CMissle and CAteroid objects
	 * 
	 */
	float new_time;
	
	/**
	 * @brief Timing paramter used for position calculaions of the CMissle and CAteroid objects
	 * 
	 */
	float old_time;

public:

	/**
	 * @brief Update postion of CMissle and CAsteroid objects
	 * 
	 */
	void move();

	/**
	 * @brief Check of collision between objects
	 * 
	 * @param obj 		Object to be compared against
	 * @return true 	Objects are in collison distance, to be deleted
	 * @return false 	Nothing carry on
	 */
	bool collide(CGameObject& obj);

	/**
	 * @brief Check if missle or asteroid collides with the wall
	 * 
	 * @param board 	_canvas in this case, needed for the size of the screen
	 * @return true 	Object is out of bounds, to be deleted
	 * @return false 	Nothing Carry on
	 */
	bool collide_wall(Size board);

	/**
	 * @brief unused in my implementation
	 * 
	 */
	void hit();

	/**
	 * @brief Get the lives object
	 * 
	 * @return int the number of lives left on the ship
	 */
	int get_lives() { return _lives; }

	/**
	 * @brief Sets the lives of Ship
	 * 
	 * @param lives number of lives to be set, 10 by default
	 */
	void set_lives(int lives) { _lives = lives; }

	/**
	 * @brief Sets the position of the ship object to match the joystick inputs
	 * 
	 * @param pos the position to be set
	 */
	void set_pos(Point2f pos) { _position = pos; }

	/**
	 * @brief Gets the current position of the object
	 * 
	 * @return Point2f the current postion on screen as a cv::Point type
	 */
	Point2f get_pos();

	/**
	 * @brief Draws an object on the cv Image
	 * 
	 * @param im the image to be drawn on
	 */
	void draw(Mat& im);
};

