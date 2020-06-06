#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include "NN.h"

#pragma warning(disable:4996) // for time measurement with ctime

int Brush_Size = 1;

const string addr_base = "C:/Projekt_AI/Project_Contents/"; // enter here your project localization
const string addr_base_plus = addr_base + "data/";


void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
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

using namespace std;
using namespace cv;

void main()
{
	srand(time(NULL));

	double learn_coeff = 0.05; // learning coefficient
	NN our_network(addr_base_plus + "0_25.jpg", learn_coeff); // used as input in class constructor, uses example input image aswell
	our_network.Random_Wages();  // generate random wages for network before teaching it

	double beta = 1; // beta in sigmoidal function equation
	double threshold = 0.75; // max is 1.0, it's threshold for statistics recognition only, doesn't affect work of the network and learning

	our_network.Transfer(beta); // example transfer of input image
	our_network.Print_Between(); // shows transfered values between each layer
	our_network.Print_Between2();
	our_network.Print_Output();

	int in_num;
	while (true) {
		cout << "Enter:" << endl;
		cout << "1 - to display graphically wages of first layer" << endl;
		cout << "2 - to teach the network with examples" << endl;
		cout << "3 - to save wages" << endl;
		cout << "4 - to load saved wages" << endl;
		cout << "5 - to check the network by drawing and checking examples" << endl;
		cout << "6 - to run the statistics of network on selected examples" << endl;
		cout << "7 - to run massive statistics and teaching of network and save the output to .txt file" << endl;
		Sleep(50);
		cin >> in_num;
		if (in_num == 1) {
			while (true) {
				for (int i = 0; i < 26; i++) {
					our_network.Graphic_Wages(i);
					waitKey(0);
				}
			}
		}
		else if (in_num == 2) {
			int num;
			cout << "Enter number of examples ot learn: ";
			cin >> num;
			for (int i = 0; i < 1; i++) {
				cout << "Iteration: " << i << endl;
				our_network.Learn_All(num, beta, true);
			}
		}
		else if (in_num == 3) {
			our_network.Save_Wages();
		}
		else if (in_num == 4) {
			our_network.Load_Wages();
		}
		else if (in_num == 5) {
			while (true) {
				namedWindow("draw", WINDOW_NORMAL);
				Mat drawing(100, 75, CV_8UC3, Scalar(0, 0, 0));
				setMouseCallback("draw", CallBackFunc, &drawing);
				resizeWindow("draw", 750, 1000);
				imshow("draw", drawing);
				Brush_Size = rand() % 6;
				while (true) {
					imshow("draw", drawing);
					if (waitKey(1) > 0) {
						break;
					}
				}
				our_network.Check(&drawing, beta, threshold);
			}
		}
		else if (in_num == 6) {
			double proc = 0.0;
			string q;
			int num;
			cout << "Do you want to use in statistics original, independent examples(y), or the ones being taught(n)?";
			cin >> q;
			cout << "Number of examples to check: ";
			cin >> num;
			if (q == "y") {
				proc = our_network.Statistics(beta, num, true);
			}
			else {
				proc = our_network.Statistics(beta, num, false);
			}
			cout << "Efficiency of network is: " << proc << "%" << endl;
		}
		else if (in_num == 7) {
			ofstream dstx;
			string tim;
			cout << "Enter the name of .txt file: ";
			cin >> tim;
			dstx.open(addr_base + tim + ".txt");
			Sleep(10);
			double proc = 0.0;
			while (!dstx.is_open()) {}
			cout << "Created file: " << addr_base + tim + ".txt" << endl;
			int diff = 1000;
			int diff2 = 400;
			cout << "Examples to learn in one iteration: ";
			cin >> diff;
			cout << "Examples to check in one statistics: ";
			cin >> diff2;
			int iter = 0;
			cout << "Wanted threshold of efficiency to save wages(in %): ";
			cin >> proc;
			double maxx;
			maxx = proc;
			cout << "Additional in-file description: ";
			cin >> tim;
			dstx << "Description: " << tim << endl;
			dstx << "Measurements were made for beta(sigmoid func.): " << beta << " and coefficient of learning: " << learn_coeff << endl;
			dstx << "One iteration is equal to " << diff << " taught and "<< diff2 << " checked examples." << endl;
			dstx << "Efficiency: " << endl;
			for (iter = 0; iter < 100; iter++) {
				cout << "Iteration: " << iter << endl;
				proc = our_network.Statistics(beta, diff2, true);
				if (proc > maxx) {
					our_network.Save_Wages();
					maxx = proc;
				}
				dstx << "for " << iter << " iterations: " << proc << "%" << endl;
				cout << "for " << iter << " iterations: " << proc << "%" << endl;
				our_network.Learn_All(diff, beta, true); 
			}
			proc = 0.0;
			proc = our_network.Statistics(beta, diff2, true);
			dstx << "for " << iter << " iterations: " << proc << "%" << endl;
			cout << "for " << iter << " iterations: " << proc << "%" << endl;
			dstx.close();
			Sleep(50);
		}
		else {
			system("pause");
		}
	}
	waitKey(0);
}
