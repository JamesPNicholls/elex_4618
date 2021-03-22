#include "stdafx.h"
#include "CImage_Ex.h"

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

void CImage_Ex::on_trackbar(int, void*)
{
	//Used by cv::createTrackbars() to avoid global variables
}

void CImage_Ex::createTrackbars()
{
	//create window for trackbars


	namedWindow(trackbarWindowName, 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf(TrackbarName, "H_MIN", H_MIN);
	sprintf(TrackbarName, "H_MAX", H_MAX);
	sprintf(TrackbarName, "S_MIN", S_MIN);
	sprintf(TrackbarName, "S_MAX", S_MAX);
	sprintf(TrackbarName, "V_MIN", V_MIN);
	sprintf(TrackbarName, "V_MAX", V_MAX);
	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH),
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->
	createTrackbar("H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar);
	createTrackbar("H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar);
	createTrackbar("S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar);
	createTrackbar("S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar);
	createTrackbar("V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar);
	createTrackbar("V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar);
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

void  CImage_Ex::run()
{
	//Craig Sample Code

	cv::VideoCapture vid; //video object
	vid.open(0);
	vid.set(CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	vid.set(CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
	createTrackbars();

	bool is_Yellow, is_Blue, is_Green;

	if (vid.isOpened() == true)
	{
		do
		{
			cv::Mat camera, HSV, threshold;
			cv::Mat green, yellow, blue;

			vid.read(camera);
			cvtColor(camera, HSV, COLOR_BGR2HSV);

			inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
			morphOps(threshold);

			is_Yellow	= find_Colour(HSV, yellow,	H_MIN_Y, H_MAX_Y, S_MIN_Y, S_MAX_Y, V_MIN_Y, V_MAX_Y);
			is_Blue		= find_Colour(HSV, blue,	H_MIN_B, H_MAX_B, S_MIN_B, S_MAX_B, V_MIN_B, V_MAX_B);
			is_Green	= find_Colour(HSV, green,	H_MIN_G, H_MAX_G, S_MIN_G, S_MAX_G, V_MIN_G, V_MAX_G);

			if (camera.empty() == false)
			{
				imshow(windowName, camera);
				imshow(windowName1, HSV);
				imshow(windowName2, threshold);
				/*imshow(windowName3, blue);
				imshow(windowName4, green);
				imshow(windowName5, yellow);*/

			}
		} while (cv::waitKey(30) != ' ');
	}
}
