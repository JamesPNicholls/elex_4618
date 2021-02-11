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
	CSketch sketch (cv::Size(CANVAS_WIDTH, CANVAS_HEIGHT), COM_PORT);
	sketch.run();
}
