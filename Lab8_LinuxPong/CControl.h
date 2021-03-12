#pragma once
//#include "Serial.h"

/**
 *
 * @brief Class used to control serial communicaiton between a PC and MKII Educational BoosterPack
 *
 * Based off of Craigs 4618_Template,
 * Makes use of 'class Serial' and its methods
 *
 * @author James Nicholls
 *
 */
class CControl
{
private:
	//Serial _com;
	bool button_Flag;
public:

	CControl();
	~CControl();

/** @brief 	initialise the com port to be used returns false if
 *
 * @param   comm_Port_Num:	com port channel to be initialized
 *
 * @return  true if comp port succesfully opened, false if not
 */
bool init_com(int comm_Port_Num);

/** @brief 	Sends a command to Launchpad and reads the return value
 *
 * @param  	type: 		digital, analog or servo enum value for type of port the command is targeting
 * @param 	channel:	The channel value corresponding to the port on the launchpad
 * @param 	result:		The value of the port to be passed out to the calling function
 *
 * @return 	true if data was returned succesfully, false if a "" was returned
 */
bool get_data(int type, int channel, int& result);

/** @brief  sets a value to a desired port on the launchpad
 *
 * @param 	type:		digital, analog or servo enum value for type of port the command is targeting
 * @param 	channel:	The channel value corresponding to the port on the launchpad
 * @param 	val:		The value to be set to port
 *
* @return 	true if data was written succesfully, false if otherwise
 */
bool set_data(int type, int channel, int val);

/** @brief 	Polls get_data() to continuoisly read from the Launchpad
 *
 * @param 	type:		digital, analog or servo enum value for type of port the command is targeting
 * @param 	channel:	The channel value corresponding to the port on the launchpad
 *
 * @return 	true if data was written succesfully, false if otherwise
 */
bool get_data_poll(int type, int channel);

/** @brief Polls get_data() with an analog 'type' and returns analog values for th X&Y joystick on the launchpad
 *
 * @param 	type:		digital, analog or servo enum value for type of port the command is targeting
 * @param 	channel:	The channel value corresponding to the port on the launchpad
 *
 * @return 	true if data was written succesfully, false if otherwise
 */
bool get_analog(int type, int channel);

/** @brief 	Polls the get_data() with extra gates for a single incremented value
 *
 * @param 	none
 *
 * @return 	true if data was written succesfully, false if otherwise
 */
bool get_button(int channel);

bool set_servo();

void print_New_Menu();
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
	RGBLED_OFFSET  = 37,

	RGB_ON = 1,
	RGB_OFF = 0,

	analog_Convesion_Factor = 1024,
	percentile_Factor = 100,
};
