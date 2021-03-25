#pragma once

/**
 * 
 * @brief Class used to control serial communicaiton between a PC and MKII Educational BoosterPack
 * 
 * Based off of Craigs 4618_Template, makes use of 'class Serial' and its methods
 * 
 * @author James Nicholls 
 * 
 */ 
class CControl
{
private:
	Serial _com;
public:

/**
* @brief	Default constructor
* @param	none
* @return	none
*/
	CControl();
	~CControl();

/**  
 * @brief 	initialise the com port to be used returns false if
 * 
 * @param   none
 * 
 * @return  true if comp port succesfully opened, false if not
 */
bool init_com();

/** 
 * @brief 	Sends a command to Launchpad and reads the return value
 * 
 * @param  	type: 		digital, analog or servo enum value for type of port the command is targeting
 * @param 	channel:	The channel value corresponding to the port on the launchpad
 * @param 	result:		The value of the port to be passed out to the calling function
 * 			 
 * @return 	true if data was returned succesfully, false if a "" was returned
 */
bool get_data(int type, int channel, int& result);

/**
 * @brief  sets a value to a desired port on the launchpad 
 * 
 * @param 	type:		digital, analog or servo enum value for type of port the command is targeting
 * @param 	channel:	The channel value corresponding to the port on the launchpad
 * @param 	val:		The value to be set to port
 * 
* @return 	true if data was written succesfully, false if otherwise
 */
bool set_data(int type, int channel, int val);

/**
 * @brief 	Polls get_data() to continuoisly read from the Launchpad
 * 
 * @param 	type:		digital, analog or servo enum value for type of port the command is targeting
 * @param 	channel:	The channel value corresponding to the port on the launchpad
 * 
 * @return 	true if data was written succesfully, false if otherwise
 */
bool get_data_poll(int type, int channel);
	
/**
 * @brief Polls get_data() with an analog 'type' and returns analog values for th X&Y joystick on the launchpad 
 * 
 * @param 	type:		digital, analog or servo enum value for type of port the command is targeting
 * @param 	channel:	The channel value corresponding to the port on the launchpad
 * 
 * @return 	true if data was written succesfully, false if otherwise
 */
bool get_analog(int type, int channel);

/** 
 * @brief 	Polls the get_data() with extra gates for a single incremented value 
 * @param 	none 
 * @return 	true if data was written succesfully, false if otherwise
 */
bool get_button();

/**
* @brief	Sends a value between 0 and 180 to the BP and manipulates a servo using servo.h methods.
* @param	none
* @return	true if data was written succesfully, false if otherwise
*/
bool set_servo();

void control_Servo();
};


enum type {
	digital, 
	analog,  
	servo     
};

enum channel_ {
	push_Button1 = 33,
	push_Button2 = 32,
	joyStick_X = 15,
	joyStick_Y = 9,
	RGBLED_RED_PIN = 39,
	RGBLED_GRN_PIN = 38,
	RGBLED_BLU_PIN = 37,

	analog_Convesion_Factor = 1024,
	percentile_Factor = 100,
};
