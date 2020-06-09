
#include "NN.h"

map <int, string> Tags = { {0, "A"}, {1, "B"}, {2, "C"}, {3, "D"}, {4, "E"}, {5, "F"}, {6, "G"}, {7, "H"}, {8, "I"}, {9, "J"}, {10, "K"}, {11, "L"}, {12, "M"}, {13, "N"},   // { {0, "a"}, {1, "b"}, {2, "c"}, {3, "d"}, {4, "e"}, {5, "f"}, {6, "g"}, {7, "h"}, {8, "i"}, {9, "j"}, {10, "k"}, {11, "l"}, {12, "m"}, {13, "n"}, 
						   {14, "O"}, {15, "P"}, {16, "Q"}, {17, "R"}, {18, "S"}, {19, "T"}, {20, "U"}, {21, "V"}, {22, "W"}, {23, "X"}, {24, "Y"}, {25, "Z"} };  // {14, "o"}, {15, "p"}, {16, "q"}, {17, "r"}, {18, "s"}, {19, "t"}, {20, "u"}, {21, "v"}, {22, "w"}, {23, "x"}, {24, "y"}, {25, "z"} };


NN::NN(string src_addr, double wsp_ucz) {
	Mat src = imread(src_addr);
	Num_of_Outputs = 26; // statycznie
	for (int i = 0; i < Num_of_Outputs; i++) {
		Output.push_back(0.0);
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
			x = src.at<unsigned char>(i, 3 * k);
			xx = (double)(x);// int
			temp.push_back(xx / 255.0);
			Input.push_back(xx / 255.0);
		}
		Picture.push_back(temp);
		temp.clear();
	}
	for (int i = 0; i < Num_of_Outputs; i++) {
		Output.push_back(0.0);
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

void NN::Print_Output() {
	for (int i = 0; i < Num_of_Outputs; i++) {
		cout << Output[i] << " ";
	}
	cout << endl;
}

void NN::Print_Wages() {
	for (int i = 0; i < Num_of_Outputs; i++) {
		for (int k = 0; k < Num_of_Inputs; k++) {
			cout << Wages[i][k] << " ";//static_cast<int>(Picture[i][k]) << " | ";  //static_cast<uint>(Picture[i][k]) << " ";
		}
		cout << endl;
	}
}

void NN::Print_Wages(int Neruon) { // dla jednego neurona
	for (int i = 0; i < Num_of_Inputs; i++) {
		cout << Wages[Neruon][i] << " ";
	}
	cout << endl;
	cout << "Wages.size() " << Wages.size() << endl;
	cout << "Wages[0].size() " << Wages[0].size() << endl;
}

void NN::Graphic_Wages(int Neruon) { // dla jednego neurona

	Mat wages(100, 75, CV_8U, Scalar(0, 0, 0));
	int temp;
	vector <int> nowy;
	for (int i = 0; i < Num_of_Inputs; i++) {
		temp = 0;
		temp = 255.0 * Wages[Neruon][i];
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
		Output.clear();
		for (int i = 0; i < Num_of_Outputs; i++) {
			Output.push_back(0.0);
		}
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
		Output.clear();
		for (int i = 0; i < Num_of_Outputs; i++) {
			Output.push_back(0.0);
		}
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

void NN::Random_Wages() {
	vector <double> temp;
	double temp_rand;
	for (int i = 0; i < Num_of_Outputs; i++) {
		for (int k = 0; k < Num_of_Inputs; k++) {
			temp_rand = rand() % 100000;
			temp_rand = (temp_rand * 0.000002) - 0.1;
			temp.push_back(temp_rand);
		}
		Wages.push_back(temp);
		temp.clear();
	}
	cout << "Zrandomizowano" << endl;
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

bool NN::Matrix_Output_Wages_Add(vector<vector<double>>* src) {
	if ((Wages[0].size() == src->at(0).size()) && (Wages.size() == src->size())) {
		int size = Wages.size();
		int size2 = Wages[0].size();
		for (int i = 0; i < size; i++) {
			for (int k = 0; k < size2; k++) {
				Wages[i][k] += src->at(i)[k];
			}
		}
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
	string Address_Base = "C:/Projekt AI/Projekt_Snbasi/data/";
	ofstream dst;
	for (int i = 0; i < Num_of_Outputs; i++) {
		dst.open(Address_Base + "wages/wages" + to_string(i) + ".txt");
		Sleep(10);
		while (!dst.is_open()) {}
		if (dst.is_open()) {
			for (int k = 0; k < cols * rows; k++) {
				dst << Wages[i][k] << endl;
			}
		}
		dst.close();
	}
	cout << "Zapisano wagi do: " << Address_Base + "wages/wages(num).txt" << endl;
}



void NN::Load_Wages() {
	string Address_Base = "C:/Projekt AI/Projekt_Snbasi/data/";
	ifstream src;
	for (int i = 0; i < Num_of_Outputs; i++) {
		src.open(Address_Base + "wages/wages" + to_string(i) + ".txt");
		string temp;
		double tempor;
		Sleep(10);
		while (!src.is_open()) {}
		if (src.is_open()) {
			for (int k = 0; k < cols * rows; k++) {
				getline(src, temp);
				if (src.eof()) {
					break;
				}
				tempor = stod(temp);
				Wages[i][k] = tempor;
			}
			if (src.eof()) {
				break;
			}
		}
		src.close();
	}
	cout << "Pobrano wagi z " << Address_Base + "wages/wages(num).txt" << endl;
}


inline double NN::Func(double temp, double beta) {
	return (1.0 / (1.0 + exp((-1.0) * (beta) * (temp))));
}



void NN::Transfer(double beta) {
	double temp;
	for (int k = 0; k < Num_of_Outputs; k++) {
		temp = 0.0;
		for (int i = 0; i < Num_of_Inputs; i++) {
			temp += (Wages[k][i] * Input[i]);
		}
		Output[k] = NN::Func(temp, beta);
	}
	Output_Declared = true;
}

bool NN::Learn(double beta) {
	vector<vector<double>> Wages_Modified;
	double temp = 0.0;
	double D = 0.0;
	double D2 = 0.0;
	vector <double> dw;
	Transfer(beta);
	vector <double> Err;
	for (int g = 0; g < Num_of_Outputs; g++) {
		temp = 0.0;
		D = 0.0;
		dw = Input; // wartosci przed ta warstwa
		temp = Output[g]; // wyjscie tego neurona

		if (g == Output_Num) {
			D = 1.0;
		}
		else {
			D = 0.0;
		}
		D = (D - temp);// * (1 - temp) * temp; 
		D = D * (1 - temp) * temp;
		D = delta * D; // wsp. uczenia // delta * D;
		NN::Scalar_Vect_Mul(&dw, D);
		Wages_Modified.push_back(dw);
		dw.clear();
	}
	NN::Matrix_Output_Wages_Add(&Wages_Modified);
	Wages_Modified.clear();
	return true;
}

void NN::Learn_All(int max, double beta, bool printx) {
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
			auto start = chrono::system_clock::now();
			Learn( beta );
			auto end = chrono::system_clock::now();
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
			for (int i = 0; i < timex.size(); i++) {
				timex_sum += timex[i];
			}
			timex_sum /= timex.size();
			timex_diff = 0.0;
			for (int i = 0; i < timex.size(); i++) {
				timex_diff += pow((timex[i] - timex_sum), 2);
			}
			timex_diff = sqrt(timex_diff/(timex.size()-1));
			cout << "Sredni czas nauki jednego przykladu: " << timex_sum << "s, z odchyleniem standardowym: " << timex_diff <<"s." << endl;
			timex.clear();
		}
		
	}
}

double NN::Statistics(double beta, int max_iter, bool original) {
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
		cout << "\r" << "Sprawdzono " << trys << " przykladow!" << endl;
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
		cout << "Sredni czas jednego transferu przykladu przez siec to: " << timex_sum << "s, z odchyleniem standardowym: " << timex_diff << "s." << endl;
		timex.clear();
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