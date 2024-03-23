#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;
using namespace cv;

string pixelToASCII(int pixel_intensity)
{
	const string ASCII_CHARS = "@%&#!*+=-. ";
	const string Reverse_ASCII_CHARS = " .-=+*!#&%@";
	string s = string(1, ASCII_CHARS[pixel_intensity * ASCII_CHARS.length() / 256]);
	//string s = string(1, Reverse_ASCII_CHARS[pixel_intensity * Reverse_ASCII_CHARS.length() / 256]);
	return s;
}

int main()
{
	// 비디오 넣는 주소
	String VideoPath = "/Project/Test/Video2.mp4";
	VideoCapture VideoCaptures(VideoPath);

	double fps = VideoCaptures.get(cv::CAP_PROP_FPS);

	cout << fps << endl;

	int frame_duration_ms = 1000 / fps;

	int width = 150;
	int height = 50;

	int frame_width = VideoCaptures.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = VideoCaptures.get(CAP_PROP_FRAME_HEIGHT);
	// 화질 계산
	// 1920	1080
	//4096 2160
	
	//		84
	// 903 550
	//     476 
	//height = (width * frame_height / frame_width) * 0.8654;

	Mat frame, greyframe, resize_frame;

	while (true)
	{
		VideoCaptures >> frame;
		if (frame.empty()) break;

		cv::cvtColor(frame, greyframe, cv::COLOR_BGR2GRAY);
		resize(greyframe, resize_frame, Size(width, height), 0, 0, INTER_CUBIC);

		string ascii_frame;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				ascii_frame += pixelToASCII(resize_frame.at<uchar>(i, j));
			}
			ascii_frame += "\n";
		}

		//system("cls");
		cout << "\033[H";
		cout << ascii_frame;
		cout.flush();
		std::this_thread::sleep_for(std::chrono::milliseconds(frame_duration_ms-10));
	}

	return 0;
}