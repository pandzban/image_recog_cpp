#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<ctime>
#include<windows.h>

using namespace std;
using namespace cv;

#define MAX_FILE_NAME_LENGTH 48;
int Kernel_Length = 6;  // degree of blur
int DELAY_BLUR = 10; // filter delay

int Index_Number = 0;

int Brush_Size = 1;

Mat save;

string Address_Base = "C:/Projekt AI/Projekt_Snbasi/";


map <int, string> Tags = { {0, "A"}, {1, "B"}, {2, "C"}, {3, "D"}, {4, "E"}, {5, "F"}, {6, "G"}, {7, "H"}, {8, "I"}, {9, "J"}, {10, "K"}, {11, "L"}, {12, "M"}, {13, "N"},   // { {0, "a"}, {1, "b"}, {2, "c"}, {3, "d"}, {4, "e"}, {5, "f"}, {6, "g"}, {7, "h"}, {8, "i"}, {9, "j"}, {10, "k"}, {11, "l"}, {12, "m"}, {13, "n"}, 
						   {14, "O"}, {15, "P"}, {16, "Q"}, {17, "R"}, {18, "S"}, {19, "T"}, {20, "U"}, {21, "V"}, {22, "W"}, {23, "X"}, {24, "Y"}, {25, "Z"} };  // {14, "o"}, {15, "p"}, {16, "q"}, {17, "r"}, {18, "s"}, {19, "t"}, {20, "u"}, {21, "v"}, {22, "w"}, {23, "x"}, {24, "y"}, {25, "z"} };

void CallBackFunc(int event, int x, int y, int flags, void* userdata) { // we can use events from mouse here(i.e. draw with brush)
	static bool Mousedown = false;
	if (event == EVENT_LBUTTONDOWN) {
		Mousedown = true;
	}
	else if (event == EVENT_RBUTTONDOWN) {
	}
	else if (event == EVENT_LBUTTONUP) {
		Mousedown = false;
	}
	else if (event == EVENT_MBUTTONDOWN) {
	} 
	else if ((event == EVENT_MOUSEMOVE) && Mousedown) {
			circle((*(Mat*)userdata), Point(x, y), 0, CV_RGB(255, 255, 255), Brush_Size);
	}
}

bool Write_to_assoc(void) {
	ofstream assoc_write(Address_Base + "data/assoc.txt");
	while (!(assoc_write.is_open())) {}
	if (assoc_write.is_open()) {
		assoc_write << "Index:" << Index_Number;
		assoc_write.close();
		return true;
	}
	else {
		return false;
	}
}

bool Write_to_Saved(string name) {
	ofstream saved_write(Address_Base + "data/saved.txt", ios_base::app);
	while (!(saved_write.is_open())) {}
	if (saved_write.is_open()) {
		saved_write << name << endl;
		saved_write.close();
		return true;
	}
	else {
		return false;
	}
}

void main()
{
	srand(time(NULL));
	int num;
	cout << "Write:" << endl;
	cout << "0 - to save as learning examples." << endl;
	cout << "1 - to save as statistics comparison example." << endl;
	cin >> num;
	if (num == 1) {
		Address_Base += "test/"; // if 1 writes to different folder
	}
	namedWindow("image", WINDOW_NORMAL);
	resizeWindow("image", 750, 1000);
	namedWindow("reference", WINDOW_NORMAL);
	ifstream assoc_read;
	Mat reference;
	assoc_read.open(Address_Base + "data/assoc.txt");
	Sleep(10);
	if (!assoc_read.is_open()) {
		cout << "Unable to open file";
		ofstream assoc_write(Address_Base + "data/assoc.txt");
		while (!(assoc_write.is_open())) {}
		if (assoc_write.is_open()) {
			assoc_write << "Index:" << Index_Number;
			cout << "Drawn index: " << Index_Number << endl;
			assoc_write.close();
		}
	}
	else {
		string line;
		string number;
		getline(assoc_read, line);
		for (int i = 0; i < line.length(); i++) {
			if(line[i] == ':'){
				for (int k = i + 1; line[k] != '\0'; k++) {
					number += line[k];
				}
				Index_Number = stoi(number);
				cout << "Loaded index: " << number << endl;
			}
		}
		assoc_read.close();
	}
	while (true) {
		int Tag_Num = rand() % Tags.size();
		Brush_Size = rand() % 6;
		cout << "Index: " << Index_Number << endl;
		Mat save(100, 75, CV_8UC3, Scalar(0, 0, 0));
		setMouseCallback("image", CallBackFunc, &save); // the painting function
		cout << "Please draw: " << Tags[Tag_Num] << endl;
		string graphic = Address_Base + "data/graphics/" + to_string(Tag_Num) + ".jpg";
		Mat reference = imread(graphic);
		resizeWindow("image", 250, 250);
		imshow("reference", reference);
		resizeWindow("image", 750, 1000);
		imshow("image", save);
		while (true) {
			imshow("image", save);
			if (waitKey(1) > 0) {
				break;
			}
		}
		Kernel_Length = (rand() % 8) + 3 ;
		for (int i = 1; i < Kernel_Length; i = i + 2)
		{
			GaussianBlur(save, save, Size(i, i), 0, 0);
			int c = waitKey(10); // DEALY BLUR = 10
			if (c >= 0) { break; }
		}
		namedWindow("image2", WINDOW_NORMAL);
		resizeWindow("image2", 750, 1000);
		imshow("image2", save);
		
		string name_str = to_string(Index_Number++);
		Write_to_assoc();
		name_str += "_" + to_string(Tag_Num);
		string address = Address_Base +"data/" + name_str + ".jpg";
		Write_to_Saved(name_str);
		imwrite(address, save);
	}
}

