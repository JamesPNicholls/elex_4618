#pragma once
#include "stdafx.h"
#include "CControl.h"

#define CANVAS_WIDTH		800
#define CANVAS_HEIGHT		800
#define CANVAS_W_DRAW		1100
#define CANVAS_H_DRAW		1100

#define DRAW_CANVAS_OFFSET	150

#define COM_PORT		10
#define CIRCLE_RADIUS	10

/**
 *
 * @brief Class used to draw a line on a openv_HighGUI window, while tracking the position of joystick on an educational boosterpack
 *
 * Based off of Craigs 4618_Template. \n
 * Makes use of 'class CControl' and its methods, made in Lab_3\n
 *
 * @author James Nicholls
 *
 */
class CBase4618
{
protected:

	CControl _base;		///< CControl class used to handle I/O from the boosterpack
	cv::Mat _canvas;	///< openCV object 

	

	/**
	* @brief	Pure virtual member of parent class
	* @param	none
	* @return	none
	*/
	virtual void update() = 0;

	/**
	* @brief	Pure virtual member of parent class
	* @param	none
	* @return	none
	*/
	virtual void draw() = 0;

public:
	/**
	* @brief	default constructor
	* @param	none
	* @return	none
	*/
	CBase4618();

	/**
	* @brief	default destructor
	* @param	none
	* @return	none
	*/
	~CBase4618();
	
	/**
	* @brief	Turns off the three RGB LED's and turns on the LED in the default value of current_Colour()
	* @param	none
	* @return	none
	*/	
	void init_RGB_LED();

	/**
	* @brief	Loops update() and draw() and breaks if the user presses 'q'
	* @param	none
	* @return	none
	*/
	void run();

};
