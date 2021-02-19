#include "stdafx.h"
#include "CControl.h"
#include <string>
#include <iomanip>

using namespace std;
using namespace cv;

CControl::CControl() 
{
	
}

CControl::~CControl()
{

}

bool CControl::init_com(int com_Port_Num)
{
    string com_String = "COM" + to_string(com_Port_Num);
	_com.open(com_String, 115200);
    if (_com.is_open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CControl::get_data (int type, int channel, int& result)
{
    string type_String = to_string(type);
    string channel_String = to_string(channel);
    string command_String = "G " + type_String + " " + channel_String + "\n";

    string result_String;

    // temporary storage
    char buff[2];

    // Send command_String
    _com.write(command_String.c_str(), command_String.length());
    Sleep(1); //this is needed as at times it causes an exception throw in some of the get_data calls;
    string out_String = "";
    // start timeout count
    double start_time = getTickCount(); 

    buff[0] = 0;
    // Read 1 byte and if an End Of Line then exit loop
    // Timeout after 1 second, if debugging step by step this will cause you to exit the loop
    while (buff[0] != '\n' && (getTickCount() - start_time) / getTickFrequency() < 2.0)
    {
        if (_com.read(buff, 1) > 0)
        {
            result_String = result_String + buff[0];
        }
    }

    if (result_String == "") // blank value will cause an error and crash the program inside of throw.cpp
    {
        return false;
    }
   
    result = stoi(result_String);
    return true;
}

bool CControl::get_analog(int type, int channel)
{
    int y_result;
    int x_result;
    
    float x_percent;
    float y_percent;

    int test = 0;

    cout << fixed;

    test = waitKeyEx(100);
    cout << "Test: " << test << "\t";
    if (get_data(type, joyStick_X, x_result))
    {
        x_percent = (float)x_result / analog_Convesion_Factor * percentile_Factor;
        cout << "X: " << setw(4) << x_result;
        cout << setw(4) << setprecision(1) << "(" << x_percent << "%)";
    }
    else
    {
        return false;
    }

        
    if (get_data(type, joyStick_Y, y_result))
    {
        y_percent = (float)y_result / analog_Convesion_Factor * percentile_Factor;
        cout << "\tY: " << setw(4) << y_result;
        cout << setw(4) << setprecision(1) << "(" << y_percent << "%)" << endl;
    }
    else
    {
        return false;
    }
  

    return true;
}

bool CControl::set_data(int type, int channel, int val)
{
    string type_String     = to_string(type);
    string channel_String  = to_string(channel);
    string val_String      = to_string(val);
    
    string command_String       = "S " + type_String + " " + channel_String + " " + val_String + "\n";
    _com.write(command_String.c_str(), command_String.length());
    Sleep(1);

    return true;
}

bool CControl::get_button(int channel)
{
    int result;
    if (get_data(digital, channel, result))
    {
        if (result == 0)
        {
            do 
            {
                get_data(digital, channel, result);//interates when the button is unpressed
            } while (result != 1);
            return true;
        }
    }
    return false;    
}

bool CControl::get_data_poll(int type, int channel)
{
    int result = 0;
    while (waitKey(1) < 0)
    {
        if (get_data(type, channel, result))
        {
            cout << "Push Button #1: " << result << endl;
            set_data(digital, RGBLED_BLU_PIN, !result);
        }
        else
        {
            return false;
        }
    }
    return true;
}