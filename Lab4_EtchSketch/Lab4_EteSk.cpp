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

//Student defined classes
//	Inherited classed need to be included in the main
//	The base class is excluded as it is included in each of the child classes
#include "CPong.h"
#include "CSketch.h"
#include "CControl.h"

using namespace std;
int main(int argc, char* argv[])
{
	char cmd;
	do
	{
		cout << "*****************" << endl;
		cout << "  Select a Lab" << endl;
		cout << "****************" << endl;
		cout << " (4), Etch-e-Sketch" << endl;
		cout << " (5), Pong" << endl;
		cout << ">";
		cin >> cmd;

		switch (cmd)
		{
		case '4':
		{
			CSketch sketch(cv::Size(CANVAS_WIDTH, CANVAS_HEIGHT), COM_PORT);
			sketch.run();
			break;
		}
		case '5':
		{
			CPong pong(cv::Size(CANVAS_WIDTH, CANVAS_HEIGHT), COM_PORT);
			pong.run();
			break;
		}

		case 'q':
			return 0;
		}
	} while (1);
}
