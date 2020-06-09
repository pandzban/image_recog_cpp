
#include "NN.h"

map <int, string> Tags = { {0, "A"}, {1, "B"}, {2, "C"}, {3, "D"}, {4, "E"}, {5, "F"}, {6, "G"}, {7, "H"}, {8, "I"}, {9, "J"}, {10, "K"}, {11, "L"}, {12, "M"}, {13, "N"},   // { {0, "a"}, {1, "b"}, {2, "c"}, {3, "d"}, {4, "e"}, {5, "f"}, {6, "g"}, {7, "h"}, {8, "i"}, {9, "j"}, {10, "k"}, {11, "l"}, {12, "m"}, {13, "n"}, 
						   {14, "O"}, {15, "P"}, {16, "Q"}, {17, "R"}, {18, "S"}, {19, "T"}, {20, "U"}, {21, "V"}, {22, "W"}, {23, "X"}, {24, "Y"}, {25, "Z"} };  // {14, "o"}, {15, "p"}, {16, "q"}, {17, "r"}, {18, "s"}, {19, "t"}, {20, "u"}, {21, "v"}, {22, "w"}, {23, "x"}, {24, "y"}, {25, "z"} };


NN::NN(string src_addr, double wsp_ucz) {
	Mat src = imread(src_addr);
	Num_of_Outputs = 26; // statycznie
	Num_of_Hidden_Neurons = 98;
	Num_of_Middle_Neurons = 64;
	for (int i = 0; i < Num_of_Outputs; i++) {
		Output.push_back(0.0);
	}
	for (int i = 0; i < Num_of_Middle_Neurons; i++) {
		Between2.push_back(0.0);
	}
	for (int i = 0; i < Num_of_Hidden_Neurons; i++) {
		Between.push_back(0.0);
	}
	delta = wsp_ucz;//0.1; // ew 0.02 albo 0.6
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
			x = src.at<unsigned char>(i, 3*k);
			xx = (double)(x);// int
			temp.push_back(xx/255.0);
			Input.push_back(xx/255.0);
		}
		Picture.push_back(temp);
		temp.clear();
	}
}

//NN::NN(Mat src) {
//	Num_of_Outputs = 26; // statycznie
//	for (int i = 0; i < Num_of_Outputs; i++) {
//		Output.push_back(0.0);
//	}
//	delta = 0.6; // ew 0.02 albo 0.6
//	Output_Declared = false;
//	Input_Img = src;
//	rows = src.rows;
//	cout << "rows: " << rows << endl;
//	cols = src.cols;
//	cout << "cols: " << cols << endl;
//	Num_of_Inputs = rows * cols;
//	vector<vector<double>> Matrix;
//	vector <double> temp2(75, 0.0);
//	for (int i = 0; i < 100; i++) {
//		Matrix.push_back(temp2);
//	}
//	unsigned char x;
//	double xx;
//	vector <double> temp;
//	for (int i = 0; i < rows; i++) {
//		for (int k = 0; k < cols; k++) {
//			x = src.at<uchar>(i, k);
//			xx = (double)(x);// int
//			temp.push_back(xx/255.0);
//			Matrix[i][k] = xx / 255.0;
//			Input.push_back(xx/255.0);
//		}
//		//Picture.push_back(temp);
//		temp.clear();
//	}
//	Picture = Matrix;
//}


NN::~NN() {}

void NN::Print_Input() {
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++) {
			cout << Picture[i][k] << " ";//static_cast<int>(Picture[i][k]) << " | ";  //static_cast<uint>(Picture[i][k]) << " ";
		}
		cout << endl;
	}

	cout << "Input: ";
	for (int i = 0; i < (cols * rows); i++) {
		cout << Input[i] << " ";
	}
}

void NN::Print_Between() {
	cout << "Hidden output: " << endl;
	for (int i = 0; i < Num_of_Hidden_Neurons; i++) {
		cout << Between[i] << " ";
	}
	cout << endl;
}

void NN::Print_Between2() {
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

void NN::Print_Wages() {  ////////// zrobione
	cout << "Hidden Layer Wages:" << endl;
	for (int i = 0; i < Num_of_Hidden_Neurons; i++) {
		for (int k = 0; k < Num_of_Inputs; k++) {
			cout << Hidden_Wages[i][k] << " ";//static_cast<int>(Picture[i][k]) << " | ";  //static_cast<uint>(Picture[i][k]) << " ";
		}
		cout << endl;
	}
	cout << "Middle Layer Wages: " << endl;
	for (int i = 0; i < Num_of_Middle_Neurons; i++) {
		for (int k = 0; k < Num_of_Hidden_Neurons; k++) {
			cout << Middle_Wages[i][k] << " ";//static_cast<int>(Picture[i][k]) << " | ";  //static_cast<uint>(Picture[i][k]) << " ";
		}
		cout << endl;
	}
	cout << "Output Wages:" << endl;
	for (int i = 0; i < Num_of_Outputs; i++) {
		for (int k = 0; k < Num_of_Middle_Neurons; k++) {
			cout << Output_Wages[i][k] << " ";//static_cast<int>(Picture[i][k]) << " | ";  //static_cast<uint>(Picture[i][k]) << " ";
		}
		cout << endl;
	}
}

void NN::Print_Wages(int Neruon) { // dla jednego neurona
	for (int i = 0; i < Num_of_Inputs; i++) {
		cout << Hidden_Wages[Neruon][i] << " ";
	}
	cout << endl;
	cout << "Wages.size() " << Hidden_Wages.size() << endl;
	cout << "Wages[0].size() " << Hidden_Wages[0].size() << endl;
}

void NN::Graphic_Wages(int Neruon) { // dla jednego neurona

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

void NN::Graphic_Input() { // dla jednego neurona

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
	//NN::Print_Vector(&nowy);
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

void NN::Graphic_Input2() { // dla jednego neurona

	Mat input2(100, 75, CV_8U, Scalar(0, 0, 0));
	int temp;
	vector <int> nowy;
	for (int i = 0; i < rows; i++ ){
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
	//NN::Print_Vector(&nowy);
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

bool NN::Load(string src_addr) {
	Mat src = imread(src_addr);

	//Picture
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

bool NN::Load(Mat* src) {

	//Picture
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

void NN::Set_Output_Num(int num) {
	Output_Num = num;
	Output_Declared = true;
}

void NN::Set_Guess_Output(int num) {
	Guess_Check = num;
	Guess_Check_Declared = true;
}

void NN::Random_Wages(){ // losowe wagi
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

bool NN::Trans(vector<vector<double>>* src, vector<vector<double>>* dst) { // transpozycja macierzy
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

bool NN::Matrix_Output_Wages_Add( vector<vector<double>>* src) {
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

bool NN::Matrix_Middle_Wages_Add(vector<vector<double>>* src) {
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

bool NN::Matrix_Hidden_Wages_Add(vector<vector<double>>* src) {
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
 

//double NN::Transfer(int output_num, double beta) {
//	double temp = 0.0;
//	for (int i = 0; i < Input.size(); i++) {
//		temp += (Output_Wages[output_num][i] * Input[i]);
//	}
//	temp = 1.0 / (1.0 + exp((-1.0) * (beta) * (temp)));
//	return temp;
//}



void NN::Save_Wages() {
	ofstream dst;
	cout << "Zapisuje" << endl;
	for (int i = 0; i < Num_of_Hidden_Neurons; i++) {       // zapis wag warstwy ukrytej
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
	cout << "Zapisano wagi do: " << addr_base_plus + "wages/wages(num).txt" << endl;
	for (int i = 0; i < Num_of_Middle_Neurons; i++) {                      // zapis wag warstwy wyjsciowej
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
	cout << "Zapisano wagi do: " << addr_base_plus + "wages/middle_wages(num).txt" << endl;
	for (int i = 0; i < Num_of_Outputs; i++) {                      // zapis wag warstwy wyjsciowej
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
	cout << "Zapisano wagi do: " << addr_base_plus + "wages/output_wages(num).txt" << endl;
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
	cout << "Pobrano wagi z " << addr_base_plus + "wages/middle_wages(num).txt" << endl;
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
	cout << "Pobrano wagi z " << addr_base_plus + "wages/wages(num).txt" << endl;
	for (int i = 0; i < Num_of_Outputs; i++) {
		src.open(addr_base_plus + "wages/output_wages" + to_string(i) +".txt");
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
	cout << "Pobrano wagi z " << addr_base_plus + "wages/output_wages(num).txt" << endl;
}


inline double NN::Func(double temp, double beta) {
	return (1.0 / (1.0 + exp((-1.0) * (beta) * (temp))));
}



void NN::Transfer(double beta) {
	double temp;
	for (int k = 0; k < Num_of_Hidden_Neurons; k++) {
		temp = 0.0;
		for (int i = 0; i < Input.size(); i++) {
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
		dw = Between2; // wartosci przed ta warstwa
		temp = Output[g]; // wyjscie tego neurona

		if (g == Output_Num) {
			D = 1.0;
		}
		else {
			D = 0.0;
		}
		D = (D - temp);// * (1 - temp) * temp; 
		Err.push_back(D);
		D = D * (1 - temp) * temp * 2;
		D = delta * D; // wsp. uczenia // delta * D;
		NN::Scalar_Vect_Mul(&dw, D);
		Wages_Modified.push_back(dw);
		dw.clear();
	} 
	for (int g = 0; g < Num_of_Middle_Neurons; g++) {
		temp = 0.0;
		D1 = 0.0;
		dw = Between;
		temp = Between2[g];
		for (int m = 0; m < Num_of_Outputs; m++) {
			D1 += Output_Wages[m][g] * Err[m];
		}
		Err2.push_back(D1);
		D1 = D1 * temp * (1 - temp) * 2;
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
		D2 = D2 *temp* (1 - temp) * 2;
		D2 = delta * D2;
		NN::Scalar_Vect_Mul(&dw, D2);
		Wages_Modified2.push_back(dw);
		dw.clear(); 
	}
	Err.clear();
	Err2.clear();
	NN::Matrix_Output_Wages_Add(&Wages_Modified);
	Wages_Modified.clear();
	NN::Matrix_Middle_Wages_Add(&Wages_Modified1);
	Wages_Modified1.clear();
	NN::Matrix_Hidden_Wages_Add(&Wages_Modified2);
	Wages_Modified2.clear();
	return true;
}

void NN::Learn_All(int max, double beta, bool printx) {
	ifstream source;
	source.open(addr_base + "data/saved.txt");
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
		cout << "Rozpoczynam nauke!" << endl;
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
			Learn( beta );
			if (printx && ((number_learned % 10) == 0)) {
				cout << "\r" << "Przyklad: " << index;
			}
			number_learned++;
		}
		source.close();
		if (printx) {
			cout << endl;
			cout << "Nauczono " << number_learned << " przykladow!" << endl;
		}
	}
}

double NN::Statistics(double beta, int max_iter) {
	ifstream source;
	source.open(addr_base + "data/saved.txt");
	Sleep(10);
	while (!source.is_open()) {}
	if (source.is_open()) {
		string line;
		string number;
		string index;
		int trys = 0;
		int hit = 0;
		double statistic = 0;
		int index_i;
		int number_i;
		string Address = addr_base + "data/";
		string G_Address;
		cout << "Rozpoczynam statystyke!" << endl;
		while(true){
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
				cout << "\r" <<  "Przyklad: " << index;
			}
 			G_Address = Address + index + "_" + number + ".jpg";
			Load(G_Address);
			Transfer(beta);
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
		cout << endl;
		source.close();
		statistic = (1.0 * hit) / (1.0 * trys) * 100.0;
		return statistic;
	}
	return 999;
}

int NN::Check(Mat* src, double beta, double prog) {
	Load(src);
	cout << " ZALADOWANO " << endl;
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
	cout << "SPRAWDZONO" << endl;
	for (int g = 0; g < Num_of_Outputs; g++) {
		cout << Output[g] * 100.0 <<"%" << endl;
		if (Output[g] > prog) {
			num++;
			outputs_idx.push_back(g);
		}
	}
	cout << "num = " << num << endl;
	if (num == 1) {
		temp = Output[outputs_idx[0]] * 100.0;
		cout << "Rozpoznano " << Tags[outputs_idx[0]] << " z prawdopodobienstwem: " << temp << "%" << endl;
		temp = outputs_idx[0];
		outputs_idx.clear();
		return temp;
	}
	else if (num < 4 && num > 0) {
		for (int i = 0; i < num; i++) {
			temp = Output[outputs_idx[i]] * 100.0;
			cout << "Prawdopodobienstwo dla " << Tags[outputs_idx[i]] << " wynosi: " << temp << "%" << endl;
		}
	}
	else {
		temp = max * 100.0;
		cout << "Najprawdopodobniej to: "<< Tags[max_ind]<< " z prawdopodobienstwem: " << temp << "%" << endl;
	}
	outputs_idx.clear();
	return 99;
}