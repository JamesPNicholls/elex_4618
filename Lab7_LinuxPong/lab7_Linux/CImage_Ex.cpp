#include "stdafx.h"
#include "CImage_Ex.h"
#include <thread>
#include <chrono>

using namespace cv;

CImage_Ex::CImage_Ex()
{
    gpioSetMode(PASS_LED, PI_OUTPUT);
    gpioSetMode(REJECT_LED, PI_OUTPUT);
    gpioSetMode(ONOFFLED, PI_OUTPUT);

    gpioWrite(PASS_LED, 1);
    gpioWrite(REJECT_LED, 1);
    gpioWrite(ONOFFLED, 1);
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

void CImage_Ex::start_Thread()
{
	std::thread t1(&CImage_Ex::camera_Thread, this);
	std::thread t2(&CImage_Ex::command_Thread, this);
	t1.detach();
	t2.detach();

}

void CImage_Ex::camera_Thread(CImage_Ex* ptr)
{
    bool temp1, temp2;
	while (ptr->camera_Thread_Flag == true)
	{
		if(ptr->vid.isOpened() == true)
		{
            ptr->vid.read(ptr->camera);
            ptr->process_Camera_Image(temp1, temp2);
            gpioDelay(100);

            imshow("Camera", ptr->camera);
            cv::waitKey(1);
		}
	}
	cout << "Camera Closed" << endl;
}

void CImage_Ex::command_Thread(CImage_Ex* ptr)
{
    char cmd;
    while(ptr->exit_Flag == true)
    {
        cout << "\n******" << endl;
        cout << " Sorting Mode " << endl;
        cout << "******" << endl;
        cout << " (M)anual Mode" << endl;
        cout << " (A)uto Mode" << endl;
        cout << " (Q)uit" << endl;
        cout << " >";
        cin >> cmd;
        switch(cmd)
        {
            case 'M':
                ptr->manual_Sort();
                break;

            case 'A':
                ptr->auto_Sort();
                break;

            case 'Q':
                ptr->exit_Flag = false;

                //wait 100ms so that the command_Thread_Flag has time to close
                auto end = std::chrono::steady_clock::now() + std::chrono::seconds(1);
                std::this_thread::sleep_until(end);

                break;
        }

    }
}

void CImage_Ex::manual_Sort()
{
    bool exit = true;
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
                gpioServo(BOTTOM_SERVO,BOTTOM_SERVO_PASS);//left
                gpioDelay(SORT_DELAY);
                gpioServo(TOP_SERVO,TOP_SERVO_OUT_POS);
                break;

            case 'N':
                gpioServo(BOTTOM_SERVO, BOTTOM_SERVO_REJECT);//rIGHT
                gpioDelay(SORT_DELAY);
                gpioServo(TOP_SERVO, TOP_SERVO_OUT_POS);
                break;

            case 'Q':
                exit = false;
                break;

            default:
                cout << "Please use only capital letters" << endl;
        }
        gpioDelay(SORT_DELAY);
        gpioServo(TOP_SERVO, TOP_SERVO_REST_POS);

    }while((exit_Flag == true) && (exit == true));

}

void CImage_Ex::auto_Sort()
{
    char fail_Index = 0;

    bool is_Ball_Yellow;
    bool is_Ball_There;

    do
    {
        gpioWrite(PASS_LED, 1);
        gpioWrite(REJECT_LED, 1);

        gpioServo(TOP_SERVO,TOP_SERVO_REST_POS);
        gpioDelay(1000000);

        process_Camera_Image(is_Ball_There, is_Ball_Yellow);
        gpioDelay(SORT_DELAY);

        if(is_Ball_There)
        {
            fail_Index = 0;
            if(is_Ball_Yellow)
            {
                gpioWrite(PASS_LED, 0);
                gpioServo(BOTTOM_SERVO,BOTTOM_SERVO_PASS);//left
                gpioDelay(SORT_DELAY);
                gpioServo(TOP_SERVO,TOP_SERVO_OUT_POS);
            }
            else
            {
                gpioWrite(REJECT_LED, 0);
                gpioServo(BOTTOM_SERVO, BOTTOM_SERVO_REJECT);//rIGHT
                gpioDelay(SORT_DELAY);
                gpioServo(TOP_SERVO, TOP_SERVO_OUT_POS);
            }
        }
        else
        {
            gpioDelay(SORT_DELAY);
            fail_Index++;

        }
        gpioDelay(SORT_DELAY);

    }while((fail_Index < 5));
    cout << "Please reload balls..." << endl;

}

bool CImage_Ex::find_Colour(Mat HSV, Mat& colour, int H_MIN_C, int H_MAX_C, int S_MIN_C, int S_MAX_C, int V_MIN_C, int V_MAX_C)
{
	bool result = false;
	int temp_Area = 0;

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

        if(r.area() > temp_Area)
        {
            temp_Area = r.area();
        }

	}
	if (temp_Area > min_Area)
	{
        putText(colour, to_string(temp_Area),Point(400,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,255,0));
		result = true;
    }

	return result;
}

void CImage_Ex::process_Camera_Image(bool& is_Ball_There, bool& is_Ball_Yellow)
{
	if (vid.isOpened() == true)
	{
        cv::Mat HSV, grey_Scale;
        cv::Mat yellow_Mat, ball_Mat;

		cvtColor(camera, HSV, COLOR_BGR2HSV);

        is_Ball_There =  find_Colour(HSV, ball_Mat, H_MIN_H, H_MAX_H, S_MIN_H, S_MAX_H, V_MIN_H, V_MAX_H);
        is_Ball_Yellow	= find_Colour(HSV, yellow_Mat, H_MIN_Y, H_MAX_Y, S_MIN_Y, S_MAX_Y, V_MIN_Y, V_MAX_Y);

        if(is_Ball_There == true)
        {
            putText(camera, "Ball is there",Point(0,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,255,0));

            if(is_Ball_Yellow == true)
            {
                putText(camera, "Ball is Yellow",Point(0,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,255,0));
            }
            else
            {
                putText(camera, "Ball is NOT Yellow",Point(0,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,255,0));
            }
        }
        else
        {
            putText(camera, "Ball is Not there",Point(0,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,255,0));
        }
    }
    else
    {
        cout << "No Camera Feed";
    }
}

void  CImage_Ex::run()
{
	vid.open(0);
	vid.set(CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	vid.set(CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

	camera_Thread_Flag = true;
	command_Thread_Flag = true;
	exit_Flag = true;

	start_Thread();

    gpioWrite(ONOFFLED, 0);
	while (exit_Flag == true)
	{
	}
    gpioWrite(ONOFFLED, 1);
	cout << "Closing Threads";

	camera_Thread_Flag  = false;
	command_Thread_Flag = false;

	std::this_thread::sleep_for(std::chrono::seconds(2));
	cv::destroyAllWindows();
}
