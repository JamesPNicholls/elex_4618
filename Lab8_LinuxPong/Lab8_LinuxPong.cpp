#include "stdafx.h"

#include <iostream>
#include <pigpio.h>
#include <opencv2/opencv.hpp>

#include "CBase4618.h"
#include "CControl.h"
#include "CPong.h"

using namespace std;
int main()
{
    int result = 0;
    char cmd = 0;
    bool passed = false;

    if(gpioInitialise() < 0)
    {
        cout << "GPIO Init failed";
    }
    else
    {
        do
        {
            CControl demo;
            demo.print_New_Menu();
            cin >> cmd;

            switch(cmd)
            {
            case '1': passed = demo.get_analog(analog, joyStick_X);       break;
            case '2': passed = demo.get_data_poll(digital, push_Button1); break;
            case '3': passed = demo.get_button(push_Button1);              break;
            case '4': passed = demo.set_servo();                          break;
            case '6':
                {
                    CPong pong(cv::Size(PONG_CANVAS_WIDTH, PONG_CANVAS_HEIGHT), 0);
                    pong.run();
                    break;
                }
            case 'q':
                gpioTerminate();
                return 0;
                break;

            }
        }while(cmd != 'q');





    }

}

