#include "stdafx.h"
#include "CAsteroid_Game.h"

CAsteroid_Game::CAsteroid_Game()
{

}

CAsteroid_Game::CAsteroid_Game(cv::Size _size, int comPort_Num)
{
	_canvas = cv::Mat::zeros(_size, CV_8UC3); 	//type cv::Mat object in CBase4618
	_base.init_com(comPort_Num);				//type CControl object in CBase4618
	
}

CAsteroid_Game::~CAsteroid_Game()
{

}

void CAsteroid_Game::update()
{
	////update postion of Asteroids
	//if (rand() % 50 == 1)
	//{
	//	CAsteroid new_Astro;
	//	asteroid_Vector.push_back(new_Astro);
	//}

	//for (auto& asteroid_it : asteroid_Vector)
	//{
	//	asteroid_it.move();
	//}

	////Update Missle Postion
	//for (auto& missle_it : missle_Vector)
	//{
	//	;
	//}

	////Update Ship Position
	//Point2i new_Ship_Pos = _ship.get_pos();
	//_ship.set_pos(new_Ship_Pos);

}

void CAsteroid_Game::draw()
{	
	_canvas = CV_RGB(0, 0, 0); //Clear the screen

	//_ship.draw(_canvas);

	////Iterates through the vector, stolen from stackoverflow
	//for (auto& asteroid_it : asteroid_Vector)
	//{
	//	asteroid_it.draw(_canvas);
	//}

	//for (auto& missle_it : missle_Vector)
	//{

	//}
	//

	//cv::imshow("_canvas", _canvas);
}

void CAsteroid_Game::run()
{
	while (cv::waitKey(1) != 'q')
	{
		update();
		draw();
	}	

}