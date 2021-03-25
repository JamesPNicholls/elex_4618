#include "stdafx.h"

#include <iostream>
#include <pigpio.h>
#include <opencv2/opencv.hpp>

#include "CBase4618.h"
#include "CControl.h"
#include "CPong.h"
#include "CImage_Ex.h"

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
            cout << "Press S to start, or Q to quit:\n >>:";
            cin >> cmd;

            switch(cmd)
            {
                case 's':
                {
                    cout << "Starting Cameras\n";
                    CImage_Ex Image_Ex;
                    Image_Ex.run();
                    break;
                }
                case 'q':
                    cout << "Ending program";
                    gpioTerminate();
                    return 0;
            }
        }while(cmd != '0');
    }

}

