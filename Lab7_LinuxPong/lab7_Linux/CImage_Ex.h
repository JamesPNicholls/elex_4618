#pragma once
#include "CBase4618.h"
#include <string>
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

	bool camera_Thread_Flag;
	bool command_Thread_Flag;
	bool exit_Flag;

	//Green
	static const int H_MIN_G = 41;
	static const int H_MAX_G = 72;
	static const int S_MIN_G = 90;
	static const int S_MAX_G = 192;
	static const int V_MIN_G = 78;
	static const int V_MAX_G = 250;

	//Blue
	static const int H_MIN_B = 92;
	static const int H_MAX_B = 120;
	static const int S_MIN_B = 56;
	static const int S_MAX_B = 256;
	static const int V_MIN_B = 141;
	static const int V_MAX_B = 214;

	//Yellow
	static const int H_MIN_Y = 21;
	static const int H_MAX_Y = 48;
	static const int S_MIN_Y = 94;
	static const int S_MAX_Y = 256;
	static const int V_MIN_Y = 150;
	static const int V_MAX_Y = 256;

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
	const int MIN_OBJECT_AREA = 20 * 20;
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
	static void on_trackbar(int, void*);
    void createTrackbars();

	void start_Thread();
	static void camera_Thread(CImage_Ex* ptr);
	static void command_Thread(CImage_Ex* ptr);

    void process_Camera_Image();bool find_Colour(cv::Mat HSV, cv::Mat& colour, int H_MIN, int H_MAX, int S_MIN, int S_MAX, int V_MIN, int V_MAX);


	void morphOps(Mat& thresh);



};

