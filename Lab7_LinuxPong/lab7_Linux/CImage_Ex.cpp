#include "stdafx.h"
#include "CImage_Ex.h"
#include <thread>
#include <chrono>

using namespace cv;

CImage_Ex::CImage_Ex()
{
}

CImage_Ex::~CImage_Ex()
{

}

void CImage_Ex::update()
{
}

void  CImage_Ex::draw()
{

}

void CImage_Ex::morphOps(Mat& thresh)
{
	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);


	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);
}

bool CImage_Ex::find_Colour(Mat HSV, Mat& colour, int H_MIN_C, int H_MAX_C, int S_MIN_C, int S_MAX_C, int V_MIN_C, int V_MAX_C)
{
	bool result = false;

	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours;
	vector<Point> contour;

	inRange(HSV, Scalar(H_MIN_C, S_MIN_C, V_MIN_C), Scalar(H_MAX_C, S_MAX_C, V_MAX_C), colour);
	morphOps(colour);

	findContours(colour, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (unsigned int i = 0; i < contours.size(); i++)
	{
		Rect r = boundingRect(contours.at(i));
		drawContours(colour, contours, i, Scalar(255, 255, 255), cv::FILLED, 8, hierarchy);

		rectangle(colour, r, Scalar(255, 0, 0));
		if (r.area() > 30000)
		{
			result = true;
		}
	}
	return result;
}

void CImage_Ex::start_Thread()
{
	std::thread t1(&CImage_Ex::camera_Thread, this);
	std::thread t2(&CImage_Ex::command_Thread, this);
	t1.detach();
	t2.detach();

}

void CImage_Ex::camera_Thread(CImage_Ex* ptr)
{
	while (ptr->camera_Thread_Flag == true)
	{
		ptr->process_Camera_Image();
		auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
		std::this_thread::sleep_until(end);
	}
	cout << "Camera Closed" << endl;
}

void manual_Sort()
{
    char cmd;
    cout << "**********" << endl;
    cout << " Controls " << endl;
    cout << "**********" << endl;
    cout << " (Y) Correct Colour" << endl;
    cout << " (N) Wrong Colour" << endl;
    cout << " (Q) Quit";
    do
    {
        cout << "\n CMD>";
        cin >> cmd;
        switch(cmd)
        {
            case 'Y':
                gpioServo(15,2000);
                gpioServo(14,2000);
                break;

            case 'N':
                gpioServo(15, 1500);
                gpioServo(14, 1500);
                break;

            case 'Q':
                break;

            default:
                cout << "Please use only capital letters" << endl;
        }

    }while(cmd != 'Q');

}

void auto_Sort()
{


}

void CImage_Ex::command_Thread(CImage_Ex* ptr)
{
    char cmd;
    while(ptr->command_Thread_Flag = true)
    {
        cout << "\n******" << endl;
        cout << " Sorting Mode " << endl;
        cout << "******" << endl;
        cout << " (M)anual Mode" << endl;
        cout << " (A)uto Mode" << endl;
        cout << " (Q)uit" << endl;
        cout << " >";
        switch(cmd)
        {
            case 'M':
                manual_Sort();
                break;
            case 'A':
                //auto_Sort();
                break;
            case 'Q':
                //ptr->command_Thread_Flag = false;//wait 100ms so that the command_Thread_Flag has time to close
                auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(100);
                std::this_thread::sleep_until(end);

                break;
        }

    }
}

void CImage_Ex::process_Camera_Image()
{
	bool is_Yellow, is_Blue, is_Green;
	if (vid.isOpened() == true)
	{
		do
		{
			cv::Mat camera, HSV, threshold;
			cv::Mat green, yellow, blue;

			vid.read(camera);
			cvtColor(camera, HSV, COLOR_BGR2HSV);

			is_Yellow	= find_Colour(HSV, yellow, H_MIN_Y, H_MAX_Y, S_MIN_Y, S_MAX_Y, V_MIN_Y, V_MAX_Y);
			//is_Blue		= find_Colour(HSV, blue, H_MIN_B, H_MAX_B, S_MIN_B, S_MAX_B, V_MIN_B, V_MAX_B);
			//is_Green	= find_Colour(HSV, green, H_MIN_G, H_MAX_G, S_MIN_G, S_MAX_G, V_MIN_G, V_MAX_G);

			if (camera.empty() == false)
			{
				imshow("Camera Feed", camera);
				//imshow(windowName1, HSV);
				//imshow(windowName2, threshold);
				//imshow(windowName3, blue);
				//imshow(windowName4, green);
				//imshow(windowName5, yellow);

			}
			else
			{
                exit_Flag = false;
			}
		} while ((cv::waitKey(1) != 'q') && (camera_Thread_Flag == true));
		exit_Flag = false;
	}
}



void  CImage_Ex::run()
{
    char cmd;
	vid.open(0);
	vid.set(CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	vid.set(CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

	camera_Thread_Flag = true;
	command_Thread_Flag = true;
	exit_Flag = true;

	start_Thread();

	while (exit_Flag == true)
	{
	}

	cout << "Closing Threads";

	camera_Thread_Flag  = false;
	command_Thread_Flag = false;

	std::this_thread::sleep_for(std::chrono::seconds(2));
	cv::destroyAllWindows();
}
