#pragma once
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

/**
 * @brief	Child class of CBase4618, inherits the draw() and update() virutal prototypes, makes an ektch-e-sketch
 *
 * Makes use of 'class CControl' and its methods, made in Lab_3\n
 *
 * @author James Nicholls
 *
 */
class CSketch : public CBase4618
{
private:
	/**
	* @brief	Checks if push buttons have been pressed									\n
	*			Push button 1 clears the screen, push button 2 cycles through the colours	\n
	*			Gets the current position of the joy stick on the BoosterPack				\n
	*			Scales the X & Y values to fit inside _canvas and reach every corner		\n						
	* 
	* @param	none
	* @return	none
	*/
	void update();

	/**
	* @brief	Takes the parameters updated in update(), and draws it to _canvas
	* @param	none
	* @return	none
	*/
	void draw();

	cv::Scalar current_Colour = { 255, 0, 0 };	///< Used to keep track of the current colour to be drawn onto _canvas
	cv::Point new_XY_Cords;						///< First of two co-ordinates used in cv::line() in draw();
	cv::Point current_XY_Cords;					///< Second of two co-ordinates used in cv::line() in draw();

public:

	/**
	* @brief	Overloaded constructor \n
	*			Preps an openCV image to size _Size and intialises the comport for CControl _base \n
	*			Calls init_RGB() \n
	*			Sets the default cursor position
	* 
	* @param	_Size			type cv::Size used to initalize the openCV image
	* @param	comPort_Num		the comport to be opened
	* 
	* @return none
	*/
	CSketch(cv::Size _Size, int comPort_Num);

	/**
	* @brief	Default destructor
	* @param	none
	* @return	none
	*/
	~CSketch();
};
