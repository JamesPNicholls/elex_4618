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
	//Green
	int H_MIN_G = 41;
	int H_MAX_G = 72;
	int S_MIN_G = 90;
	int S_MAX_G = 192;
	int V_MIN_G = 78;
	int V_MAX_G = 250;

	//Blue
	int H_MIN_B = 92;
	int H_MAX_B = 120;
	int S_MIN_B = 56;
	int S_MAX_B = 256;
	int V_MIN_B = 141;
	int V_MAX_B = 214;

	//Yellow
	int H_MIN_Y = 21;
	int H_MAX_Y = 48;
	int S_MIN_Y = 94;
	int S_MAX_Y = 256;
	int V_MIN_Y = 150;
	int V_MAX_Y = 256;

	int H_MIN = 0;
	int H_MAX = 256;
	int S_MIN = 0;
	int S_MAX = 256;
	int V_MIN = 0;
	int V_MAX = 256;
	//default capture width and height
	const int FRAME_WIDTH = 640;
	const int FRAME_HEIGHT = 480;
	//max number of objects to be detected in frame
	const int MAX_NUM_OBJECTS = 50;
	//minimum and maximum object area
	const int MIN_OBJECT_AREA = 20 * 20;
	const int MAX_OBJECT_AREA = FRAME_HEIGHT * FRAME_WIDTH / 1.5;
	//names that will appear at the top of each window
	const string windowName = "Original Image";
	const string windowName1 = "HSV Image";
	const string windowName2 = "Thresholded Image";
	const string windowName3 = "Blue";
	const string windowName4 = "Green";
	const string windowName5 = "Yellow";
	const string trackbarWindowName = "Trackbars";

	void update();
	void draw();
	static void on_trackbar(int, void*);
	void createTrackbars();

	bool find_Colour(cv::Mat HSV, cv::Mat& colour, int H_MIN, int H_MAX, int S_MIN, int S_MAX, int V_MIN, int V_MAX);
	bool object_Found();
	
	void morphOps(Mat& thresh);
	


};

