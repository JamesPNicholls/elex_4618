#include "stdafx.h"
#include "Serial.h"
#include "CControl.h"
#include <string>
#include <iomanip>


CControl::CControl() 
{
	
}

CControl::~CControl()
{

}

bool CControl::init_com()
{
	_com.open("COM3",115200);
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
    std::string type_String = std::to_string(type);
    std::string channel_String = std::to_string(channel);
    std::string command_String = "G " + type_String + " " + channel_String + "\n";

    std::string result_String;

    // temporary storage
    char buff[2];

    // Send command_String
    _com.write(command_String.c_str(), command_String.length());
    Sleep(10); // wait for ADC conversion, etc. May not be needed?

    std::string out_String = "";
    // start timeout count
    double start_time = cv::getTickCount();

    buff[0] = 0;
    // Read 1 byte and if an End Of Line then exit loop
    // Timeout after 1 second, if debugging step by step this will cause you to exit the loop
    while (buff[0] != '\n' && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 2.0)
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
   
    result = std::stoi(result_String);
    return true;
}

bool CControl::get_analog(int type, int channel)
{
    int y_result;
    int x_result;
    
    float x_percent;
    float y_percent; 

    int test = 0;

    std::cout << std::fixed;
    do
    {
        test = cv::waitKeyEx(100);
        std::cout << "Test: " << test << "\t";
        if (get_data(type, joyStick_X, x_result))
        {
            x_percent = (float)x_result / analog_Convesion_Factor * percentile_Factor;
            std::cout << "X: " << std::setw(4) << x_result;
            std::cout << std::setw(4) << std::setprecision(1) << "(" << x_percent << "%)";
        }
        else
        {
            return false;
        }

        
        if (get_data(type, joyStick_Y, y_result))
        {
            y_percent = (float)y_result / analog_Convesion_Factor * percentile_Factor;
            std::cout << "\tY: " << std::setw(4) << y_result;
            std::cout << std::setw(4) << std::setprecision(1) << "(" << y_percent << "%)" << std::endl;
        }
        else
        {
            return false;
        }
    } while (cv::waitKeyEx(1) < 1);

    return true;
}

bool CControl::set_data(int type, int channel, int val)
{
    std::string type_String     = std::to_string(type);
    std::string channel_String  = std::to_string(channel);
    std::string val_String      = std::to_string(val);
    
    std::string command_String       = "S " + type_String + " " + channel_String + " " + val_String + "\n";
    _com.write(command_String.c_str(), command_String.length());
    Sleep(1);

      return true;
}

bool CControl::get_button()
{
    int result;
    int index = 0;
    do
    {
        if (get_data(digital, push_Button2, result))
        {
            if (result == 0)
            {
                while (result != 1)
                {
                    get_data(digital, push_Button2, result);//interates when the button is unpressed
                }
                index++;
                std::cout << "\nButton Test: " << index;
            }
        }
        else
        {
            return false;
        }
    } while (cv::waitKey(0) < 0);
    return true;
}

bool CControl::get_data_poll(int type, int channel)
{
    int result = 0;
    while (cv::waitKey(0) < 0)
    {
        if (get_data(type, channel, result))
        {
            std::cout << "Push Button #1: " << result << std::endl;
            set_data(digital, RGBLED_BLU_PIN, !result);
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool CControl::set_servo()
{
    int servo_value;
    get_data(servo, 0, servo_value);
    while (cv::waitKey(1) < 1)
    {
        while (servo_value < 180)
        {
            set_data(servo, 0, servo_value);
            servo_value++;
            cv::waitKey(10);
        }
        while (servo_value > 0)
        {
            set_data(servo, 0, servo_value);
            servo_value--;
            cv::waitKey(10);
        }        
    }
    return true;
}

void CControl::control_Servo()
{
    char cmd = ' ';
    int servo_Value = 0;
    set_data(servo, 0, 89);
    bool dir = false;
    do
    {
        cv::waitKey(100);

         if (dir == false )
        {
            dir = true;
            set_data(servo, 0, 89);
        }
        else 
        {
            dir = false;
            set_data(servo, 0, 110);
        }
    } while (1);
}