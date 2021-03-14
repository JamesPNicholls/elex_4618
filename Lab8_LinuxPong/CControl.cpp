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
    //string com_String = "COM" + to_string(com_Port_Num);
	//_com.open(com_String, 115200);
	gpioSetMode(19, PI_INPUT);  // PB1
	gpioSetMode(26, PI_INPUT);  // PB2
    gpioSetMode(21, PI_OUTPUT); //servo



    return true;
}

bool CControl::get_data (int type, int channel, int& result)
{
    bool state = false;
    if(type == digital)
    {
        switch(channel)
        {
            case push_Button1 :
                channel = 19;
                break;
            case push_Button2 :
                channel = 26;
                break;
        }
        result = gpioRead(channel);

        state = true;
    }

    if(type == analog)
    {
        unsigned char inBuf[3];
        char cmd[] = { 1,channel, 0 }; // 0b1XXX0000 where XXX=channel 0
        int handle = spiOpen(0, 200000, 3); // Mode 0, 200kHz

        spiXfer(handle, cmd, (char*) inBuf, 3); // Transfer 3 bytes
        result = ((inBuf[1] & 3) << 8) | inBuf[2]; // Format 10 bits
        spiClose(handle); // Close SPI system

        state = true;
    }

    gpioDelay(1000);
    return state;
}

bool CControl::get_analog(int type, int channel)
{
    int y_result;
    int x_result;

    float x_percent;
    float y_percent;

    cout << fixed;
    uint32_t start_Time = gpioTick();
    do
    {
        if (get_data(type, 128, x_result))
        {
            x_percent = (float)x_result / analog_Convesion_Factor * percentile_Factor;
            cout << "X: " << setw(4) << x_result;
            cout << setw(4) << setprecision(1) << "(" << x_percent << "%)";
        }
        else
        {
            return false;
        }


        if (get_data(type, 144, y_result))
        {
            y_percent = (float)y_result / analog_Convesion_Factor * percentile_Factor;
            cout << "\tY: " << setw(4) << y_result;
            cout << setw(4) << setprecision(1) << "(" << y_percent << "%)" << endl;
        }
        else
        {
            return false;
        }
    }while((gpioTick() - start_Time) < 10000000);

    return true;
}

bool CControl::set_data(int type, int channel, int val)
{
    return true;
}

bool CControl::get_button(int channel)
{
    float start = cv::getTickCount();
    int result;
    if (get_data(digital, channel, result))
    {
        if (result == 0)
        {
            cv::waitKey(3);
            if (button_Flag == true)
            {
                return false;
            }
            else
            {
                button_Flag = true;
                return true;
            }
        }
        else if (result == 1)
        {
            button_Flag = false;
            return false;
        }
    }
    return false;
}

bool CControl::get_data_poll(int type, int channel)
{
    int result = 0;
    uint32_t start_Time = gpioTick();
    while ((gpioTick() - start_Time) < 10000000)
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

bool CControl::set_servo()
{
    int servo_value = 500;
    uint32_t start_Time = gpioTick();

    while ((gpioTick() - start_Time) < 2000000)
    {
        while (servo_value < 2500)
        {
            gpioServo(21, servo_value);
            servo_value++;
            gpioDelay(1000);
        }
        while (servo_value > 500)
        {
            gpioServo(21,servo_value);
            servo_value--;
            gpioDelay(1000);
        }
    }
    return true;
}

void CControl::print_New_Menu()
{
    std::cout << "\n**********************************************";
    std::cout << "\n* ELEX4618 Lab 8-Linux Port, By James Nicholls";
    std::cout << "\n**********************************************";
    std::cout << "\n(1) Analog Joy Stick";
    std::cout << "\n(2) Digital Button";
    std::cout << "\n(3) Digital Button + Debounce";
    std::cout << "\n(4) Servo Swing";
    std::cout << "\n(5) Pong Port";
    std::cout << "\n(0) Exit";
    std::cout << "\nCMD> ";
}

