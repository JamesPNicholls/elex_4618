#pragma once
#include "stdafx.h"
#include "CBase4618.h"
#include <vector>

#include "CMissle.h"
#include "CShip.h"
#include "CAsteroid.h"

/**
 * @brief Class used to manage all of the on screen objects in a game of Asteroids
 * 
 * Contains two vectors used to store each of the objects on screen \n
 * Adds and purges them from the vecotr as need
 */
using namespace std;
class CAsteroid_Game : CBase4618
{
private:
	
	/**
	 * @brief Update all of the parameters of CShip, CAsteroid, and CMissle type objects
	 * 
	 */
	void update();

	/**
	 * @brief Draws all of the updated objects on screen
	 * 
	 * Holds the program if a game over state is detected. ie game_Over_Flag = true;
	 */
	void draw();

	/**
	 * @brief Vector used to store all of the asteroid objects on screen
	 * 
	 */
	vector <CAsteroid>	asteroid_Vector;

	/**
	 * @brief Vector used to store all of the missle type objects on screen
	 * 
	 */
	vector <CMissle>	missle_Vector;

	/**
	 * @brief The ship to be drawn on screen and controlled by the user
	 * 
	 */
	CShip _ship;

	/**
	 * @brief The current score of the game, updates when a misslexAsteroid collision detected
	 * 
	 */
	int score;

	/**
	 * @brief Used as a paramter for get_button() in CControl
	 * 
	 */
	bool button_Flag;

	/**
	 * @brief Flag for a game over state
	 * True = game over \n
	 * False = continue
	 */
	bool game_Over_Flag;
	bool reset_Flag;
	bool quit_Flag;

public:
	/**
	 * @brief Construct a new casteroid game object
	 * 
	 */
	CAsteroid_Game();

	/**
	 * @brief Construct a new casteroid game object
	 * 
	 * @param _size 		Size of the canvas being drawn on
	 * @param comPort_Num 
	 */
	CAsteroid_Game(cv::Size _size, int comPort_Num);

	/**
	 * @brief Destroy the casteroid game object
	 * 
	 */
	~CAsteroid_Game();

	/**
	 * @brief Halts the game on a start menu and a key press to start/restart
	 * 
	 */
	void reset_Game();

	/**
	 * @brief Loops update() and draw() 
	 * 
	 */
	void run();
};
