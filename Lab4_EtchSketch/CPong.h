#pragma once
#include "stdafx.h"
#include "CBase4618.h"

#define BALL_X_START PONG_CANVAS_WIDTH/2
#define BALL_Y_START PONG_CANVAS_HEIGHT/2

#define BALL_RADIUS 8

#define PADDLE_LEFT_X 100
#define PADDLE_LEFT_Y PONG_CANVAS_HEIGHT/2

#define PADDLE_RIGHT_X PONG_CANVAS_WIDTH - PADDLE_LEFT_X
#define PADDKE_RIGHT_Y PONG_CANVAS_HEIGHT/2

#define PADDLE_WIDTH	10
#define PADDLE_HEIGHT	100

#define SCORE_TEXT_HEIGHT	80
#define LEFT_SCORE_POS_X	150
#define RIGHT_SCORE_POS_X	650

#define LINE_CENTER PONG_CANVAS_WIDTH/2

#define X_VELOCITY_OFFSET		1500
#define X_VELOCITY_BASE_VALUE	3000
#define Y_VELOCITY_OFFSET		600
#define Y_VELOCITY_BASE_VALUE	500

/**
 * @brief Struct used to hold the paramters for the left and righ paddles
 * 
 */
struct paddle_Params
{	
	cv::Point paddle_Point;	///< Marks the Top left corner of the paddle
	int width;				///< Width of the paddle, needed for cv::Rect()
	int height;				///< Length of the paddle, needed for cv::Rect()

	cv::Rect pl_rectangle;	///< Rect() for cv::rectangle(), will be form the visible paddle
	cv::Rect pl_Hit_Box; 	///< Rect() for cv::rectangle(), will form the invisible hit box for collision detection 
							///< follows pl_rectangle and extends behind it, a really bad way to deal with the collision 
							///< better way would be to track the postion of the ball and determine if it passed over the paddle in the past tick
	
	const cv::Scalar paddle_Colour = { 255,255,255 };//White, could use CV_RGB type
};
/**
 * @brief Struct used to hold the paramters for the ball
 * 
 */
struct ball_Params
{
	cv::Point ball_Cords; 	///< The center of the ball
	cv::Point ball_Vel;		///< Velocity of the ball
	cv::Point ball_Acc;		///< Acceleration of the ball, not used in this code

	double current_Time;	///< Compared to old_time for displacement calculations in update()
	double old_Time;		///< Used to determine the new postion of the _Ball 
};

/**
 * @brief 	Struct used to hold values for the unmoving objects of the screen \n
 * 			Player scores + location, FPS counter + location
 * 
 */
struct screen_Params
{
	int FPS;					///< The current frame rate, printed in the top right corner
	cv::Point fps_Point;		///< Location of the FPS counter

	int l_Score = 0;			///< Score of left and right players
	int r_Score = 0;			///< Score of left and right players
	 
	cv::String player_L_str;	///< "Player X: " + x_score, to be printed on the screen 
	cv::String player_R_str;	///< "Player X: " + x_score, to be printed on the scree
	cv::Point  player_L_Point;	///< Locations of where to draw the players score
	cv::Point  player_R_Point;	///< Locations of where to draw the players score
};

/**
 * @brief 	Child class of CBase4618 \n
 * 			Contains the structs of the different drawable polygons \n
 * 			I should make each of the paddles and balls their own objects 
 */
class CPong : public CBase4618
{
private:

	ball_Params		_Ball;						///< Parameters for the ball
	paddle_Params	left_Paddle_Params;			///< Parameters for the left paddle
	paddle_Params	right_Paddle_Params;		///< Parameters for the right paddle
	screen_Params	_canvas_Screen_Params;		///< Parameters for the non-moving objects on screen
	const cv::Scalar black_Canvas = { 0,0,0 };	///< Blank canvas to clear the screen on each reset

	/**
	 * @brief updates all of the values for each of the structs and 
	 * 
	 */
	void update();

	/**
	 * @brief clears _canvas and draws the new objects with the updated parameters
	 * 
	 */
	void draw();

	/**
	 * @brief clears the _canvas, resets all of the struct parameters to their default value, and calls vel_Gen()
	 * 
	 */
	void reset_Screen_Parameters();

	/**
	 * @brief 	Generates a new random value for the x&y velocity \n
	 *			Values were chosen rather arbitrarily until they looked nice \n
	 * 			 
	 * @return cv::Point	returns the new x&y velocity, can be positive or negative
	 */
	cv::Point CPong::vel_Gen();	

public:

	/**
	 * @brief Construct a new CPong object
	 * 
	 */
	CPong();

	/**
	 * @brief Constructor that initalizes the cv::Mat \n
	 * 			 and populates all the object structs with their default values
	 * 
	 * @param _Size 		size of _canvas to draw on
	 * @param comPort_Num 	com port for communicating with a MK2 launchpad/boosterpack
	 */
	CPong(cv::Size _Size, int comPort_Num);

	/**
	 * @brief Destroy the CPong object
	 * 
	 */
	~CPong();

	/**
	 * @brief loops update() and draw(), handles the threading + timing
	 * 
	 */
	void run();
};
