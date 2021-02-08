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
#include "CBase4618.h"

int main(int argc, char* argv[])
{
	cv::Size sketch_Size;
	sketch_Size.height = CANVAS_HEIGHT;
	sketch_Size.width = CANVAS_WIDTH;

	CSketch sketch (sketch_Size, COM_PORT);		
	sketch.run();
}
