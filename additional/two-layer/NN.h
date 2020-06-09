#pragma once

#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<map>
#include<ctime>
#include<chrono>
#include<windows.h>
 
using namespace std;
using namespace cv;

const extern string addr_base;
const extern string addr_base_plus;

class NN {
private:
	vector <vector <double>> Picture;
	vector <double> Input;
	vector <double> Between;
	vector <double> Output;
	Mat Input_Img;
	vector <vector<double>> Hidden_Wages;
	vector <vector<double>> Output_Wages; // Neurons x length(Input) for fully connected
	int rows;
	int cols;
	int Num_of_Inputs; // sizeof(Input)
	int Num_of_Hidden_Neurons;
	int Num_of_Outputs;
	double delta; // wsp. uczenia
	int Output_Num;
	int Guess_Check;
	bool Output_Declared;
	bool Guess_Check_Declared;
public:
	NN(string src_addr, double wsp_ucz);
	~NN();

	void Print_Input();
	void Print_Between();
	void Print_Between2();
	void Print_Output();
	void Print_Wages();
	void Print_Wages(int Neuron);
	bool Load(string src_addr);
	bool Load(Mat* src);
	void Set_Output_Num(int num);
	void Set_Guess_Output(int num);
	void Graphic_Input();
	void Graphic_Input2();
	void Random_Wages();
	void Graphic_Wages(int Neuron);
	void Print_Input2();
	static inline double Func(double temp, double beta);
	static void Create_Matrix(vector<vector<double>>* src, int rows, int cols, int opcode);
	static void Print_Matrix(vector<vector<double>>* src);
	static bool Trans(vector<vector<double>>* src, vector<vector<double>>* dst);
	static bool Create_Matrix_from_Vector(vector<vector<double>>* dst, int rows, int cols, vector<double>* src);
	static bool Scalar_Vect_Mul(vector <double>* src, double scalar);
	static void Print_Vector(vector <int>* src);
	static void Print_Vector(vector <double>* src);
	static bool Vector_Add(vector<double>* dst, vector<double>* src, bool minus);
	bool Matrix_Output_Wages_Add(vector<vector<double>>* src);
	bool Matrix_Middle_Wages_Add(vector<vector<double>>* src);
	bool Matrix_Hidden_Wages_Add(vector<vector<double>>* src);
	void Transfer(double beta);
	bool Learn(double beta);
	void Learn_All(int max, double beta, bool printx);
	int Check(Mat* src, double beta, double prog);
	void Save_Wages(void);
	double Statistics(double beta, int max_iter, bool original);
	void Load_Wages();

};
