////////////////////////////////////////////////////////////////
// ELEX 4618 Template project for BCIT
// Created Oct 5, 2016 by Craig Hennessey
// Last updated December 30, 2020
////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

#include "Client.h"
#include "Server.h"
// Must include Windows.h after Winsock2.h, so Serial must include after Client/Server
#include "Serial.h"
#include "CControl.h"

void process_msg()
{
  MSG msg;
  while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }
}

void print_New_Menu()
{
    std::cout << "\n****************************************";
    std::cout << "\n* ELEX4618 Lab 3-ESC, By James Nicholls";
    std::cout << "\n*****************************************";
    std::cout << "\n(1) Analog Joy Stick";
    std::cout << "\n(2) Digital Button";
    std::cout << "\n(3) Digital Button + Debounce"; 
    std::cout << "\n(4) Servo Swing";
    std::cout << "\n(0) Exit";
    std::cout << "\nCMD> ";
}

int main(int argc, char* argv[])
{
    int result = 0;
	int cmd = -1;
    bool com_Passed = true;

    CControl boosterPack;
    if (boosterPack.init_com())
    {
        do
        {
            print_New_Menu();
            std::cin >> cmd;
            switch (cmd)
            {
            case 1:  com_Passed = boosterPack.get_analog(analog, joyStick_X);       break;  //Joy Stick
            case 2:  com_Passed = boosterPack.get_data_poll(digital, push_Button1); break;  //Push Button + LED
            case 3:  com_Passed = boosterPack.get_button();                         break;  //Push Button + Debouce + Count
            case 4:  boosterPack.set_servo();              break;  //Servo Sweep, Filler values
            }

            if (com_Passed == false)
            {
                std::cout << "ERROR: Failed to return data" << std::endl;
            }

        } while (cmd != 0);
    }
    else
    {
        std::cout << "ERROR: init_com() failed to open port...";
    }

}
