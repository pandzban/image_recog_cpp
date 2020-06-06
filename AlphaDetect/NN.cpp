
#include "NN.h"

map <int, string> Tags = { {0, "A"}, {1, "B"}, {2, "C"}, {3, "D"}, {4, "E"}, {5, "F"}, {6, "G"}, {7, "H"}, {8, "I"}, {9, "J"}, {10, "K"}, {11, "L"}, {12, "M"}, {13, "N"},   // { {0, "a"}, {1, "b"}, {2, "c"}, {3, "d"}, {4, "e"}, {5, "f"}, {6, "g"}, {7, "h"}, {8, "i"}, {9, "j"}, {10, "k"}, {11, "l"}, {12, "m"}, {13, "n"}, 
						   {14, "O"}, {15, "P"}, {16, "Q"}, {17, "R"}, {18, "S"}, {19, "T"}, {20, "U"}, {21, "V"}, {22, "W"}, {23, "X"}, {24, "Y"}, {25, "Z"} };  // {14, "o"}, {15, "p"}, {16, "q"}, {17, "r"}, {18, "s"}, {19, "t"}, {20, "u"}, {21, "v"}, {22, "w"}, {23, "x"}, {24, "y"}, {25, "z"} };


NN::NN(string src_addr, double learn_coeff) {
	Mat src = imread(src_addr);
	Num_of_Outputs = 26; // enter here number of outputs(neurons in last layer)
	Num_of_Hidden_Neurons = 64;  // number of neurons in 1 layer
	Num_of_Middle_Neurons = 48;  // number of neurons in middle layer
	for (int i = 0; i < Num_of_Outputs; i++) {
		Output.push_back(0.0);
	}
	for (int i = 0; i < Num_of_Middle_Neurons; i++) {
		Between2.push_back(0.0);
	}
	for (int i = 0; i < Num_of_Hidden_Neurons; i++) {
		Between.push_back(0.0);
	}
	delta = learn_coeff;
	Output_Declared = false;
	Input_Img = src;
	rows = src.rows;
	cols = src.cols;
	Num_of_Inputs = rows * cols;
	unsigned char x;
	unsigned int xx;
	vector <double> temp;
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++) {
			x = src.at<unsigned char>(i, 3 * k);
			xx = (double)(x);// int
			temp.push_back(xx / 255.0);
			Input.push_back(xx / 255.0);
		}
		Picture.push_back(temp);
		temp.clear();
	}
}

NN::~NN() {}

void NN::Print_Input() { // values before first layer
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++) {
			cout << Picture[i][k] << " ";
		}
		cout << endl;
	}

	cout << "Input: ";
	for (int i = 0; i < (cols * rows); i++) {
		cout << Input[i] << " ";
	}
}

void NN::Print_Between() { // values between first two layers
	cout << "Hidden output: " << endl;
	for (int i = 0; i < Num_of_Hidden_Neurons; i++) {
		cout << Between[i] << " ";
	}
	cout << endl;
}

void NN::Print_Between2() { // values between middle and last layer
	cout << "Hidden output: " << endl;
	for (int i = 0; i < Num_of_Middle_Neurons; i++) {
		cout << Between2[i] << " ";
	}
	cout << endl;
}

void NN::Print_Output() { 
	cout << "Net output: " << endl;
	for (int i = 0; i < Num_of_Outputs; i++) {
		cout << Output[i] << " ";
	}
	cout << endl;
}

void NN::Print_Wages() {  // prints text
	cout << "Hidden Layer Wages:" << endl;
	for (int i = 0; i < Num_of_Hidden_Neurons; i++) {
		for (int k = 0; k < Num_of_Inputs; k++) {
			cout << Hidden_Wages[i][k] << " ";
		}
		cout << endl;
	}
	cout << "Middle Layer Wages: " << endl;
	for (int i = 0; i < Num_of_Middle_Neurons; i++) {
		for (int k = 0; k < Num_of_Hidden_Neurons; k++) {
			cout << Middle_Wages[i][k] << " ";
		}
		cout << endl;
	}
	cout << "Output Wages:" << endl;
	for (int i = 0; i < Num_of_Outputs; i++) {
		for (int k = 0; k < Num_of_Middle_Neurons; k++) {
			cout << Output_Wages[i][k] << " ";
		}
		cout << endl;
	}
}

void NN::Print_Wages(int Neruon) { // for one neuron
	for (int i = 0; i < Num_of_Inputs; i++) {
		cout << Hidden_Wages[Neruon][i] << " ";
	}
	cout << endl;
	cout << "Wages.size() " << Hidden_Wages.size() << endl;
	cout << "Wages[0].size() " << Hidden_Wages[0].size() << endl;
}

void NN::Graphic_Wages(int Neruon) { // for one neuron as graphic

	Mat wages(100, 75, CV_8U, Scalar(0, 0, 0));
	int temp;
	vector <int> nowy;
	for (int i = 0; i < Num_of_Inputs; i++) {
		temp = 0;
		temp = 255.0 * Hidden_Wages[Neruon][i];
		if (temp > 255) {
			temp = 255;
		}
		else if (temp < 0) {
			temp = 0;
		}
		nowy.push_back(temp);
	}
	for (int i = 0; i < wages.rows; i++) {
		for (int k = 0; k < wages.cols; k++) {
			wages.at<uchar>(i, k) = nowy[k + (i * wages.cols)];
		}
	}
	nowy.clear();
	namedWindow("wages", WINDOW_NORMAL);
	resizeWindow("wages", 750, 1000);
	imshow("wages", wages);
	resizeWindow("wages", 750, 1000);
}

void NN::Graphic_Input() { 

	Mat input(100, 75, CV_8U, Scalar(0));
	int temp;
	vector <int> nowy;
	for (int i = 0; i < Num_of_Inputs; i++) {
		temp = 0;
		temp = 255.0 * Input[i];
		if (temp > 255) {
			temp = 255;
		}
		else if (temp < 0) {
			temp = 0;
		}
		nowy.push_back(temp);
	}
	for (int i = 0; i < input.rows; i++) {
		for (int k = 0; k < input.cols; k++) {
			input.at<uchar>(i, k) = nowy[k + (i * input.cols)];
		}
	}
	namedWindow("input", WINDOW_NORMAL);
	resizeWindow("input", 750, 1000);
	imshow("input", input);
	resizeWindow("input", 750, 1000);
}

void NN::Graphic_Input2() { // for one neuron

	Mat input2(100, 75, CV_8U, Scalar(0, 0, 0));
	int temp;
	vector <int> nowy;
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++) {
			temp = 0;
			temp = 255.0 * Picture[i][k];
			if (temp > 255) {
				temp = 255;
			}
			else if (temp < 0) {
				temp = 0;
			}
			nowy.push_back(temp);
		}
	}
	for (int i = 0; i < input2.rows; i++) {
		for (int k = 0; k < input2.cols; k++) {
			input2.at<uchar>(i, k) = nowy[k + (i * input2.cols)];
		}
	}
	namedWindow("input2", WINDOW_NORMAL);
	resizeWindow("input2", 750, 1000);
	imshow("input2", input2);
	cout << "Wbudowana" << endl;
	print(input2);
	resizeWindow("input2", 750, 1000);
}

void NN::Print_Vector(vector <int>* src) {
	for (int i = 0; i < src->size(); i++) {
		cout << src->at(i) << " ";
	}
	cout << endl;
}

void NN::Print_Vector(vector <double>* src) {
	for (int i = 0; i < src->size(); i++) {
		cout << src->at(i) << " ";
	}
	cout << endl;
}

void NN::Print_Input2() {
	cout << "Input print: " << endl;
	for (int i = 0; i < Input.size(); i++) {
		cout << Input[i] << " ";
	}
	cout << endl;
}

bool NN::Load(string src_addr) { // loads openCV image on input, using source address
	Mat src = imread(src_addr);
	if (rows == src.rows && cols == src.cols) {
		Picture.clear();
		Input_Img = src;
		Input.clear();
		rows = src.rows;
		cols = src.cols;
		Num_of_Inputs = rows * cols;
		unsigned char x;
		unsigned int xx;
		vector <double> temp;
		for (int i = 0; i < rows; i++) {
			for (int k = 0; k < cols; k++) {
				x = src.at<unsigned char>(i, 3 * k);
				xx = (double)(x);// int
				temp.push_back(xx / 255.0);
				Input.push_back(xx / 255.0);
			}
			Picture.push_back(temp);
			temp.clear();
		}
		Between.clear();
		for (int i = 0; i < Num_of_Hidden_Neurons; i++) {
			Between.push_back(0.0);
		}
		Output.clear();
		for (int i = 0; i < Num_of_Outputs; i++) {
			Output.push_back(0.0);
		}
		Output_Declared = false;
		return true;
	}
	return false;
}

bool NN::Load(Mat* src) { // loads openCV image as input 
	if (rows == src->rows && cols == src->cols) {
		Picture.clear();
		Input_Img = *src;
		Input.clear();
		rows = src->rows;
		cols = src->cols;
		Num_of_Inputs = rows * cols;
		unsigned char x;
		unsigned int xx;
		vector <double> temp;
		for (int i = 0; i < rows; i++) {
			for (int k = 0; k < cols; k++) {
				x = src->at<unsigned char>(i, 3 * k);
				xx = (double)(x);// int
				temp.push_back(xx / 255.0);
				Input.push_back(xx / 255.0);
			}
			Picture.push_back(temp);
			temp.clear();
		}
		Between.clear();
		for (int i = 0; i < Num_of_Hidden_Neurons; i++) {
			Between.push_back(0.0);
		}
		Output.clear();
		for (int i = 0; i < Num_of_Outputs; i++) {
			Output.push_back(0.0);
		}
		Output_Declared = false;
		return true;
	}
	return false;
}

void NN::Set_Output_Num(int num) { // define correct output
	Output_Num = num;
	Output_Declared = true;
}

void NN::Set_Guess_Output(int num) { // set guessed output
	Guess_Check = num;
	Guess_Check_Declared = true;
}

void NN::Random_Wages() { // generate random wages
	vector <double> temp;
	double temp_rand;
	Hidden_Wages.clear();
	Middle_Wages.clear();
	Output_Wages.clear();
	for (int i = 0; i < Num_of_Hidden_Neurons; i++) {
		for (int k = 0; k < Num_of_Inputs; k++) {
			temp_rand = rand() % 1000;
			temp_rand -= 500;
			temp_rand = (temp_rand * 0.0001);
			temp.push_back(temp_rand);
		}
		Hidden_Wages.push_back(temp);
		temp.clear();
	}
	for (int i = 0; i < Num_of_Middle_Neurons; i++) {
		for (int k = 0; k < Num_of_Hidden_Neurons; k++) {
			temp_rand = rand() % 1000;
			temp_rand -= 500;
			temp_rand = (temp_rand * 0.0001);
			temp.push_back(temp_rand);
		}
		Middle_Wages.push_back(temp);
		temp.clear();
	}
	for (int i = 0; i < Num_of_Outputs; i++) {
		for (int k = 0; k < Num_of_Middle_Neurons; k++) {
			temp_rand = rand() % 1000;
			temp_rand -= 500;
			temp_rand = (temp_rand * 0.0001);
			temp.push_back(temp_rand);
		}
		Output_Wages.push_back(temp);
		temp.clear();
	}
}

void NN::Print_Matrix(vector<vector<double>>* src) {
	int cols_src = src->at(0).size();
	int rows_src = src->size();
	for (int i = 0; i < rows_src; i++) {
		for (int k = 0; k < cols_src; k++) {
			cout << src->at(i)[k] << " ";
		}
		cout << endl;
	}
}

bool NN::Trans(vector<vector<double>>* src, vector<vector<double>>* dst) { // matrix transpose
	int cols_src = src->at(0).size();
	int rows_src = src->size();
	int cols_dst = dst->at(0).size();
	int rows_dst = dst->size();
	if ((cols_src == rows_dst) && (rows_src == cols_dst)) {
		for (int i = 0; i < rows_dst; i++) {
			for (int k = 0; k < cols_dst; k++) {
				dst->at(i)[k] = src->at(k)[i];
			}
		}
		return true;
	}
	return false;
}

void NN::Create_Matrix(vector<vector<double>>* src, int rows, int cols, int opcode) {
	vector <double> temp;
	if (opcode == 0) {
		for (int i = 0; i < rows; i++) {
			for (int k = 0; k < cols; k++) {
				temp.push_back(0);
			}
			src->push_back(temp);
			temp.clear();
		}
	}
	else if (opcode == 1) {
		for (int i = 0; i < rows; i++) {
			for (int k = 0; k < cols; k++) {
				temp.push_back(k + (i * cols));
			}
			src->push_back(temp);
			temp.clear();
		}
	}
}

bool NN::Scalar_Vect_Mul(vector <double>* src, double scalar) {
	int size = src->size();
	for (int i = 0; i < size; i++) {
		src->at(i) *= scalar;
	}
	return true;
}

bool NN::Vector_Add(vector<double>* dst, vector<double>* src, bool minus) {
	if (dst->size() == src->size()) {
		int size = dst->size();
		for (int i = 0; i < size; i++) {
			if (minus) {
				dst->at(i) -= src->at(i);
			}
			else {
				dst->at(i) += src->at(i);
			}
		}
	}
	return true;
}

bool NN::Matrix_Output_Wages_Add(vector<vector<double>>* src) { // actualize output wages
	int size = Output_Wages.size();
	int size2 = Output_Wages[0].size();
	if ((size2 == src->at(0).size()) && (size == src->size())) {
		for (int i = 0; i < size; i++) {
			for (int k = 0; k < size2; k++) {
				Output_Wages[i][k] += src->at(i)[k];
			}
		}
	}
	else {
		cout << "ERROR" << endl;
	}
	return true;
}

bool NN::Matrix_Middle_Wages_Add(vector<vector<double>>* src) { // actualize middle wages
	int size = Middle_Wages.size();
	int size2 = Middle_Wages[0].size();
	if ((size2 == src->at(0).size()) && (size == src->size())) {
		for (int i = 0; i < size; i++) {
			for (int k = 0; k < size2; k++) {
				Middle_Wages[i][k] += src->at(i)[k];
			}
		}
	}
	else {
		cout << "ERROR" << endl;
	}
	return true;
}

bool NN::Matrix_Hidden_Wages_Add(vector<vector<double>>* src) { //actualize first layer wages
	int size = Hidden_Wages.size();
	int size2 = Hidden_Wages[0].size();
	if ((size2 == src->at(0).size()) && (size == src->size())) {
		for (int i = 0; i < size; i++) {
			for (int k = 0; k < size2; k++) {
				Hidden_Wages[i][k] += src->at(i)[k];
			}
		}
	}
	else {
		cout << "ERROR" << endl;
	}
	return true;
}

bool NN::Create_Matrix_from_Vector(vector<vector<double>>* dst, int rows, int cols, vector<double>* src) {
	vector <double> temp;
	if (src->size() == rows * cols) {
		for (int i = 0; i < rows; i++) {
			for (int k = 0; k < cols; k++) {
				temp.push_back(src->at(k + (i * cols)));
			}
			dst->push_back(temp);
			temp.clear();
		}
		return true;
	}
	return false;
}

void NN::Save_Wages() {
	ofstream dst;
	cout << "Saving wages..." << endl;
	for (int i = 0; i < Num_of_Hidden_Neurons; i++) {     
		dst.open(addr_base_plus + "wages/wages" + to_string(i) + ".txt");
		Sleep(2);
		while (!dst.is_open()) {}
		if (dst.is_open()) {
			for (int k = 0; k < rows * cols; k++) {
				dst << Hidden_Wages[i][k] << endl;
			}
		}
		dst.close();
	}
	cout << "Saved wages to: " << addr_base_plus + "wages/wages(num).txt" << endl;
	for (int i = 0; i < Num_of_Middle_Neurons; i++) {        
		dst.open(addr_base_plus + "wages/middle_wages" + to_string(i) + ".txt");
		Sleep(2);
		while (!dst.is_open()) {}
		if (dst.is_open()) {
			for (int k = 0; k < Num_of_Hidden_Neurons; k++) {
				dst << Middle_Wages[i][k] << endl;
			}
		}
		dst.close();
	}
	cout << "Saved wages to: " << addr_base_plus + "wages/middle_wages(num).txt" << endl;
	for (int i = 0; i < Num_of_Outputs; i++) {          
		dst.open(addr_base_plus + "wages/output_wages" + to_string(i) + ".txt");
		Sleep(2);
		while (!dst.is_open()) {}
		if (dst.is_open()) {
			for (int k = 0; k < Num_of_Middle_Neurons; k++) {
				dst << Output_Wages[i][k] << endl;
			}
		}
		dst.close();
	}
	cout << "Saved wages to: " << addr_base_plus + "wages/output_wages(num).txt" << endl;
}



void NN::Load_Wages() {
	ifstream src;
	for (int i = 0; i < Num_of_Hidden_Neurons; i++) {
		src.open(addr_base_plus + "wages/wages" + to_string(i) + ".txt");
		string temp;
		double tempor;
		Sleep(2);
		while (!src.is_open()) {}
		if (src.is_open()) {
			for (int k = 0; k < cols * rows; k++) {
				getline(src, temp);
				if (src.eof()) {
					break;
				}
				tempor = stod(temp);
				Hidden_Wages[i][k] = tempor;
			}
			if (src.eof()) {
				break;
			}
		}
		src.close();
	}
	cout << "Wages loaded from " << addr_base_plus + "wages/middle_wages(num).txt" << endl;
	for (int i = 0; i < Num_of_Middle_Neurons; i++) {
		src.open(addr_base_plus + "wages/middle_wages" + to_string(i) + ".txt");
		string temp;
		double tempor;
		Sleep(2);
		while (!src.is_open()) {}
		if (src.is_open()) {
			for (int k = 0; k < Num_of_Hidden_Neurons; k++) {
				getline(src, temp);
				if (src.eof()) {
					break;
				}
				tempor = stod(temp);
				Middle_Wages[i][k] = tempor;
			}
			if (src.eof()) {
				break;
			}
		}
		src.close();
	}
	cout << "Wages loaded from " << addr_base_plus + "wages/wages(num).txt" << endl;
	for (int i = 0; i < Num_of_Outputs; i++) {
		src.open(addr_base_plus + "wages/output_wages" + to_string(i) + ".txt");
		string temp;
		double tempor;
		Sleep(2);
		while (!src.is_open()) {}
		if (src.is_open()) {
			for (int k = 0; k < Num_of_Middle_Neurons; k++) {
				getline(src, temp);
				if (src.eof()) {
					break;
				}
				tempor = stod(temp);
				Output_Wages[i][k] = tempor;
			}
			if (src.eof()) {
				break;
			}
		}
		src.close();
	}
	cout << "Wages loaded from " << addr_base_plus + "wages/output_wages(num).txt" << endl;
}


inline double NN::Func(double temp, double beta) { // activation function
	return (1.0 / (1.0 + exp((-1.0) * (beta) * (temp))));
}



void NN::Transfer(double beta) { // transfers input throughout the network
	double temp;
	for (int k = 0; k < Num_of_Hidden_Neurons; k++) { 
		temp = 0.0;
		for (int i = 0; i < Num_of_Inputs; i++) {
			temp += (Hidden_Wages[k][i] * Input[i]);
		}
		Between[k] = NN::Func(temp, beta);
	}
	for (int k = 0; k < Num_of_Middle_Neurons; k++) {
		temp = 0.0;
		for (int i = 0; i < Num_of_Hidden_Neurons; i++) {
			temp += (Middle_Wages[k][i] * Between[i]);
		}
		Between2[k] = NN::Func(temp, beta);
	}
	for (int k = 0; k < Num_of_Outputs; k++) {
		temp = 0.0;
		for (int i = 0; i < Num_of_Middle_Neurons; i++) {
			temp += (Output_Wages[k][i] * Between2[i]);
		}
		Output[k] = NN::Func(temp, beta);
	}
	Output_Declared = true;
}

bool NN::Learn(double beta) {
	vector<vector<double>> Wages_Modified;
	vector<vector<double>> Wages_Modified1;
	vector<vector<double>> Wages_Modified2;
	double temp = 0.0;
	double D = 0.0;
	double D1 = 0.0;
	double D2 = 0.0;
	vector <double> dw;
	Transfer(beta);
	vector <double> Err;
	vector <double> Err2;
	for (int g = 0; g < Num_of_Outputs; g++) {
		temp = 0.0;
		D = 0.0;
		dw = Between2; // values before this layer
		temp = Output[g]; // output of this neuron
		if (g == Output_Num) {
			D = 1.0; // if it is declared output
		}
		else {
			D = 0.0;
		}
		D = (D - temp);
		Err.push_back(D); // error of neuron
		D = D * (1 - temp) * temp; // multiply by derivative of activ. function(sigmoid)
		D = delta * D; // learning coefficient
		NN::Scalar_Vect_Mul(&dw, D);   // multiply by input of this layer
		Wages_Modified.push_back(dw);   // stack wages
		dw.clear();
	}
	for (int g = 0; g < Num_of_Middle_Neurons; g++) {
		temp = 0.0;
		D1 = 0.0;
		dw = Between;
		temp = Between2[g];
		for (int m = 0; m < Num_of_Outputs; m++) {
			D1 += Output_Wages[m][g] * Err[m];  // sum of all output wages of this neuron times error from later neurons
		}
		Err2.push_back(D1); // error if this neuron
		D1 = D1 * temp * (1 - temp);
		D1 = delta * D1;
		NN::Scalar_Vect_Mul(&dw, D1);
		Wages_Modified1.push_back(dw);
		dw.clear();
	}
	for (int g = 0; g < Num_of_Hidden_Neurons; g++) {
		temp = 0.0;
		D2 = 0.0;
		dw = Input;
		temp = Between[g];
		for (int m = 0; m < Num_of_Middle_Neurons; m++) {
			D2 += Middle_Wages[m][g] * Err2[m];
		}
		D2 = D2 * temp * (1 - temp);
		D2 = delta * D2;
		NN::Scalar_Vect_Mul(&dw, D2);
		Wages_Modified2.push_back(dw);
		dw.clear();
	}
	Err.clear();
	Err2.clear();
	NN::Matrix_Output_Wages_Add(&Wages_Modified); // after calculating errors, modify wages
	Wages_Modified.clear();
	NN::Matrix_Middle_Wages_Add(&Wages_Modified1);
	Wages_Modified1.clear();
	NN::Matrix_Hidden_Wages_Add(&Wages_Modified2);
	Wages_Modified2.clear();
	return true;
}

void NN::Learn_All(int max, double beta, bool printx) { // learn set of examples
	ifstream source;
	source.open(addr_base + "data/saved.txt");
	vector <double> timex;
	double timex_sum;
	double timex_diff;
	Sleep(10);
	while (!source.is_open()) {}
	if (source.is_open()) {
		string line;
		string number;
		string index;
		int index_i;
		int number_i;
		string Address = addr_base + "data/";
		string G_Address;
		int number_learned = 0;
		cout << "Beggining learning!" << endl;
		for (int i = 0; i < max; i++) {
			getline(source, line);
			if (source.eof()) {
				break;
			}
			bool start_write = false;
			number = "";
			index = "";
			for (char p : line) {
				if (p == '\n') {
					start_write = false;
					break;
				}
				if (start_write) {
					number += p;
				}
				if (p == '_') {
					start_write = true;
				}
				if (!start_write) {
					index += p;
				}
			}
			number_i = stoi(number);
			G_Address = Address + index + "_" + number + ".jpg";
			Load(G_Address);
			Set_Output_Num(number_i);
			auto start = chrono::system_clock::now();
			Learn(beta);
			auto end = chrono::system_clock::now();              //
			chrono::duration<double> elapsed = end - start;
			timex.push_back(elapsed.count());
			if (printx && ((number_learned % 10) == 0)) {
				cout << "\r" << "Przyklad: " << index;
			}
			number_learned++;
		}
		source.close();
		if (printx) {
			cout << "\r" << "Nauczono " << number_learned << " przykladow!" << endl;
			timex_sum = 0.0;
			for (int i = 0; i < timex.size(); i++) {     // uncomment all of these if you want to measure learn time
				timex_sum += timex[i];
			}
			timex_sum /= timex.size();
			timex_diff = 0.0;
			for (int i = 0; i < timex.size(); i++) {
				timex_diff += pow((timex[i] - timex_sum), 2);
			}
			timex_diff = sqrt(timex_diff/(timex.size()-1));
			cout << "Average time of learning of one example is: " << timex_sum << "s, with standard deviation equal: " << timex_diff <<"s." << endl;
			timex.clear();
		}

	}
}

double NN::Statistics(double beta, int max_iter, bool original) { // chceck set of examples
	ifstream source;
	if (original == true) {
		source.open(addr_base + "test/data/saved.txt");
	}
	else {
		source.open(addr_base + "data/saved.txt");
	}
	Sleep(10);
	while (!source.is_open()) {}
	if (source.is_open()) {
		string line;
		string number;
		string index;
		int trys = 0;
		int hit = 0;
		double statistic = 0;
		vector <double> timex;
		double timex_sum;
		double timex_diff;
		int index_i;
		int number_i;
		string Address;
		if (original == true) {
			Address = addr_base + "test/data/";
		}
		else {
			Address = addr_base + "data/";
		}
		string G_Address;
		cout << "Running statistics!" << endl;
		while (true) {
			getline(source, line);
			if (source.eof() || trys == max_iter) {
				break;
			}
			bool start_write = false;
			number = "";
			index = "";
			for (char p : line) {
				if (p == '\n') {
					start_write = false;
					break;
				}
				if (start_write) {
					number += p;
				}
				if (p == '_') {
					start_write = true;
				}
				if (!start_write) {
					index += p;
				}
			}
			number_i = stoi(number);
			if ((trys % 10) == 0) {
				cout << "\r" << "Example: " << index;
			}
			G_Address = Address + index + "_" + number + ".jpg";
			Load(G_Address);
			auto start = chrono::system_clock::now();
			Transfer(beta);
			auto end = chrono::system_clock::now();
			chrono::duration<double> elapsed = end - start;
			timex.push_back(elapsed.count());
			double max = 0;
			int max_idx = 9999;
			for (int i = 0; i < Num_of_Outputs; i++) {
				if (Output[i] > max) {
					max = Output[i];
					max_idx = i;
				}
			}
			if (max_idx == number_i) {
				hit++;
			}
			trys++;
		}
		cout << "\r" << "Checked " << trys << " examples!" << endl;
		source.close();
		statistic = (1.0 * hit) / (1.0 * trys) * 100.0;
		timex_sum = 0.0;
		for (int i = 0; i < timex.size(); i++) {
			timex_sum += timex[i];
		}
		timex_sum /= timex.size();
		timex_diff = 0.0;
		for (int i = 0; i < timex.size(); i++) {
			timex_diff += pow((timex[i] - timex_sum), 2);
		}
		timex_diff = sqrt(timex_diff / (timex.size() - 1));
		cout << "Average time of transfer of one example through network is equal: " << timex_sum << "s, with standard deviation: " << timex_diff << "s." << endl;
		timex.clear();
		return statistic;
	}
	return 999;
}

int NN::Check(Mat* src, double beta, double prog) { // check single example
	Load(src);
	int num = 0;
	vector <int> outputs_idx;
	double temp = 0.0;
	double max = 0.0;
	int max_ind;
	Transfer(beta);
	for (int g = 0; g < Num_of_Outputs; g++) {
		temp = Output[g];
		if (temp > max) {
			max = temp;
			max_ind = g;
		}
	}
	for (int g = 0; g < Num_of_Outputs; g++) {
		cout << Output[g] * 100.0 << "%" << endl;
		if (Output[g] > prog) {
			num++;
			outputs_idx.push_back(g);
		}
	}
	if (num == 1) {
		temp = Output[outputs_idx[0]] * 100.0;
		cout << "Recognized: " << Tags[outputs_idx[0]] << " with probability: " << temp << "%" << endl;
		temp = outputs_idx[0];
		outputs_idx.clear();
		return temp;
	}
	else if (num < 4 && num > 0) {
		for (int i = 0; i < num; i++) {
			temp = Output[outputs_idx[i]] * 100.0;
			cout << "Probability for: " << Tags[outputs_idx[i]] << " is: " << temp << "%" << endl;
		}
	}
	else {
		temp = max * 100.0;
		cout << "Most likely it is: " << Tags[max_ind] << " with probability: " << temp << "%" << endl;
	}
	outputs_idx.clear();
	return 99;
}