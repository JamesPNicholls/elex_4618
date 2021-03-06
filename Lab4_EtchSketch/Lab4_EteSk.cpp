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
#include "CControl.h"
#include "CSketch.h"
#include "CPong.h"
#include "CAsteroid_Game.h"



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
		cout << " (6), Asteroids" << endl;
		cout << " >>";
		cin >> cmd;

		switch (cmd)
		{
		case '4': 
		{
			cout << "...Running lab 4, Etch-E-Sketch" << endl << endl;
			CSketch sketch(cv::Size(ETCH_CANVAS_WIDTH, ETCH_CANVAS_HEIGHT), COM_PORT);
			sketch.run();
			break;
		}
		case '5':
		{
			cout << "...Running lab 5, Pong" << endl << endl;
			CPong pong(cv::Size(PONG_CANVAS_WIDTH, PONG_CANVAS_HEIGHT), COM_PORT);
			pong.run();
			pong.~CPong();
			break;
		}

		case '6':
		{
			cout << "...Lab 6 is a work in process" << endl << endl;;
			CAsteroid_Game asteroid( cv::Size(ASTEROID_CANVAS_WIDTH, ASTEROID_CANVAS_HEIGHT), COM_PORT);			
			asteroid.run();
			break;
		}
			
		case 'q':
			return 0;

		default:
			cout << "Invalid..." << endl << endl;
		}
		cv::destroyAllWindows();
	} while (1);
}
