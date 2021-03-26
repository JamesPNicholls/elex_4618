#pragma once
#include "CBase4618.h"
#include <string>

#define TOP_SERVO           15
#define BOTTOM_SERVO        14
#define TOP_SERVO_REST_POS  1380
#define TOP_SERVO_OUT_POS   1600
#define BOTTOM_SERVO_PASS   1900
#define BOTTOM_SERVO_REJECT 1500
#define SORT_DELAY          100000

#define PASS_LED    16
#define REJECT_LED  20
#define ONOFFLED    21

using namespace cv;
using namespace std;


class CImage_Ex : public CBase4618
{

/** Todo
*	Make it talk to the camera
*	make it find an image on the camera
*	make it repsond to colour
*	port to linux
*
*/
public:
	CImage_Ex();
	~CImage_Ex();
	void run();

private:

	cv::VideoCapture vid;
	cv::Mat camera;

	bool camera_Thread_Flag;
	bool command_Thread_Flag;
	bool exit_Flag;

	//Yellow HSV Limites
	static const int H_MIN_Y = 25;
	static const int H_MAX_Y = 40;
	static const int S_MIN_Y = 50;
	static const int S_MAX_Y = 256;
	static const int V_MIN_Y = 30;
	static const int V_MAX_Y = 256;

    static const int H_MIN_H = 0;
	static const int H_MAX_H = 180;
	static const int S_MIN_H = 50;
	static const int S_MAX_H = 256;
	static const int V_MIN_H = 40;
	static const int V_MAX_H = 200;

	int H_MIN = 0;
	int H_MAX = 256;
	int S_MIN = 0;
	int S_MAX = 256;
	int V_MIN = 0;
	int V_MAX = 256;
	//default capture width and height
	//keep these values the same or the picture gets messed up
	const int FRAME_WIDTH = 640;
	const int FRAME_HEIGHT = 400;

	//max number of objects to be detected in frame
	const int MAX_NUM_OBJECTS = 50;

	//minimum and maximum object area
	const int min_Area = 35000;
	const int MAX_OBJECT_AREA = FRAME_HEIGHT * FRAME_WIDTH / 1.5;

	//names that will appear at the top of each window
	string windowName = "Original Image";
	string windowName1 = "HSV Image";
	string windowName2 = "Thresholded Image";
	string windowName3 = "Blue";
	string windowName4 = "Green";
	string windowName5 = "Yellow";
	string trackbarWindowName = "Trackbars";

	void update();
	void draw();

	void start_Thread();

	static void camera_Thread(CImage_Ex* ptr);
	static void command_Thread(CImage_Ex* ptr);

    void manual_Sort();
    void auto_Sort();

    //Stuff to Find a ball
    void process_Camera_Image(bool& is_Ball_There, bool& is_Ball_Yellow);
    void morphOps(Mat& thresh);
    bool find_Colour(cv::Mat HSV, cv::Mat& colour, int H_MIN, int H_MAX, int S_MIN, int S_MAX, int V_MIN, int V_MAX);
    bool find_Shape(cv::Mat grey_Scale, cv::Mat& threshold_Mat);
};
