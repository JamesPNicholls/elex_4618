#include "stdafx.h"
#include "CAsteroid_Game.h"

CAsteroid_Game::CAsteroid_Game()
{

}

CAsteroid_Game::CAsteroid_Game(cv::Size _size, int comPort_Num)
{
	_canvas = cv::Mat::zeros(_size, CV_8UC3); 	//type cv::Mat object in CBase4618
	_base.init_com(comPort_Num);				//type CControl object in CBase4618
	score = 0;
	game_Over_Flag = false;
}

CAsteroid_Game::~CAsteroid_Game()
{

}

void CAsteroid_Game::update()
{
	////update postion of Asteroids

	if (rand() % 10 == 1)
	{
		CAsteroid new_Astro;
		asteroid_Vector.push_back(new_Astro);
	}
	
	int i = 0;
	for (auto& asteroid_it : asteroid_Vector)//iterate through the asteroid vector
	{
		//update position of the vector
		asteroid_it.move();

		if (asteroid_it.collide_wall(_canvas.size()))//Check for wall collision
		{
			if (i >= asteroid_Vector.size())
			{
				break;
			}
			asteroid_Vector.erase(asteroid_Vector.begin() + i);
		}
		
		//Checks to see if the ship collides with an asteroid
		if (asteroid_it.collide(_ship))
		{
			//decrement the life count if hit
			_ship.set_lives(_ship.get_lives() - 1);
			if (i >= asteroid_Vector.size())
			{
				break;
			}
			asteroid_Vector.erase(asteroid_Vector.begin() + i);//delete the asteroid if it hits the ship
		}
		i++;// safety index to prevent the vector from accessing memory that was removed
	}

	int j = 0;
	for (auto& missle_it : missle_Vector)//iterate through the middle vector
	{
		//update missle position
		missle_it.move();
	
		int i = 0;
		for (auto& asteroid_it : asteroid_Vector)
		{
			if (asteroid_it.collide(missle_it))	//Checks to see if the missle collides with an asteroid
			{
				if (i >= asteroid_Vector.size())
				{
					break;
				}
				asteroid_Vector.erase(asteroid_Vector.begin() + i);//delete the asteroid if hits 
				score += 10;//add score

				if (j >= missle_Vector.size())
				{
					break;
				}
				missle_Vector.erase(missle_Vector.begin() + j);//delete missle as well
				

			}
			i++;
		}

		if (missle_it.collide_wall(_canvas.size()))
		{
			if (j >= missle_Vector.size())
			{
				break;
			}
			missle_Vector.erase(missle_Vector.begin() + j);//delete missle as well
		}
		j++;
		cout << j << "\n";
	}

	if (_base.get_button(push_Button1, button_Flag))
	{
		CMissle new_Missle;
		new_Missle.set_pos(_ship.get_pos()); //sets the position of the missle to center of the ship
		missle_Vector.push_back(new_Missle);
	}

	//if (_base.get_button(push_Button2, button_Flag))
	{
		//reset the screen
	}
	//Update Missle Postion

	//Update the ship position
	Point2i new_Ship_Pos;
	_base.get_data(analog, joyStick_X, new_Ship_Pos.x);
	_base.get_data(analog, joyStick_Y, new_Ship_Pos.y);
	new_Ship_Pos.y = ASTEROID_CANVAS_HEIGHT - new_Ship_Pos.y; //inverted y asxis

	_ship.set_pos(new_Ship_Pos);

	//Check for game over
	if (_ship.get_lives() == 0)
	{
		game_Over_Flag = true;				
	}

}

void CAsteroid_Game::draw()
{	
	_canvas = CV_RGB(0, 0, 0); //Clear the screen

	_ship.draw(_canvas);

	//Iterates through the vector, stolen from stackoverflow
	for (auto& asteroid_it : asteroid_Vector)
	{
		asteroid_it.draw(_canvas);
	}

	for (auto& missle_it : missle_Vector)
	{
		missle_it.draw(_canvas);
	}

	//Score
	putText(_canvas, "Score: " + to_string(score), Point2f(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 255, 255), 2);
	
	//Lives
	putText(_canvas, "Lives: " + to_string(_ship.get_lives()), Point2f(600, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 255, 255), 2);

	if (game_Over_Flag == true)
	{
		_canvas = Scalar(0, 0, 0);
		putText(_canvas, "GAME OVER", Point(125, 450), FONT_HERSHEY_SIMPLEX, 4.0, Scalar(0,0,200), 3);
		cv::imshow("_canvas", _canvas);
		
		while (waitKey(1) < 0)
		{
		};
		game_Over_Flag = false;
		
	}

	cv::imshow("_canvas", _canvas);
}

void CAsteroid_Game::run()
{
	while (cv::waitKey(1) != 'q')
	{
		update();
		draw();

	}	

}