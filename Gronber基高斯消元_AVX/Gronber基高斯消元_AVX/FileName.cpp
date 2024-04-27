#include <immintrin.h> // AVXָ�
#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>
#include<fstream>
#include <fstream>  // �����ļ��������
#include <string>   // �����ַ�����
#include<sstream>
using namespace std;
const int N = 400;
const int Len = 255;
vector<vector<int> > a(5, vector<int>(90000, 0));//��Ԫ��
int c[90000];
int String_to_int(string a) {
	int i = 0;
	int res = 0;
	for (i; i < a.length(); i++) {
		res *= 10;
		res += a[i] - '0';
	}
	return res;
}
string int_to_String(int a) {
	ostringstream os;
	os << a;
	return os.str();
}
vector<int> reca(5, 0);
void input(istringstream s, vector<int> q) {
	string st;
	while (s >> st) {
		q[String_to_int(st)] = 1;
	}
	return;
}
void inFile(string load, vector<int> s) {
	ofstream fil;
	fil.open(load, ios::app);
	bool flag = false;
	for (int i = Len; i >= 0; i--) {
		if (s[i]) {
			if (!flag)   c[i] = 1;
			flag = true;
			fil << int_to_String(i) << " ";
		}
	}

	if (!flag) {
		if (load == "D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//res2.txt")
			fil << endl;
		return;
	}
	fil << endl;
	fil.close();
	return;
}
vector<int> xiaoyuan(const vector<int>& s, const vector<int>& q) {
	vector<int> result(s.size(), 0);
	for (size_t i = 0; i < s.size(); i += 8) { // ÿ�δ���8��32λ����
		__m256i s_vec = _mm256_loadu_si256((__m256i*) & s[i]); // ����AVX����
		__m256i q_vec = _mm256_loadu_si256((__m256i*) & q[i]);
		__m256i result_vec = _mm256_xor_si256(s_vec, q_vec); // ִ�а�λ���
		_mm256_storeu_si256((__m256i*) & result[i], result_vec); // �洢���
	}
	return result;
}
int  signal[2];
void get_duijiaoxian(int s[]) {

}
void get_xyz() {

}
int main() {

	//�ļ��ĳ�ʼ��
	std::ofstream ofs1("D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//res1.txt", std::ios::trunc); // ʹ�� std::ios::trunc ��־������ļ�
	ofs1.close(); // �ر��ļ���
	std::ofstream ofs2("D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//res0.txt", std::ios::trunc); // ʹ�� std::ios::trunc ��־������ļ�
	ofs2.close(); // �ر��ļ���
	std::ofstream ofs3("D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//res2.txt", std::ios::trunc); // ʹ�� std::ios::trunc ��־������ļ�
	ofs3.close(); // �ر��ļ���

	std::string sourceFile = "D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//����Ԫ��.txt";
	// Ŀ���ļ�·��
	std::string targetFile = "D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//res1.txt";
	// ��Դ�ļ����ж�ȡ
	std::ifstream source(sourceFile, std::ios::binary);
	// ��Ŀ���ļ�����д�루��������ڻᴴ���������򸲸ǣ�
	std::ofstream target(targetFile, std::ios::binary);
	// ����ļ��Ƿ�ɹ���
	if (!source.is_open() || !target.is_open()) {
		std::cerr << "Error: Could not open files." << std::endl;
		return 1;
	}
	// ʹ�����Ŀ�����������Դ�ļ����ݸ��Ƶ�Ŀ���ļ�
	target << source.rdbuf();
	// �ر��ļ���
	source.close();
	target.close();



	ifstream file("D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//��Ԫ�� - ����.txt");
	string line;
	int i = 0;
	int curfile = 1;
	string curFile = "res" + int_to_String(curfile) + ".txt";
	ofstream fileoutres;//���յĽ����
	fileoutres.open("D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//res2.txt", ios::app);
	ifstream fileout("D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//res1.txt");  //����Ԫ
	ifstream fileout1("D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//res0.txt");
	bool flagg = true;
	while (flagg) {
		ifstream fileout("D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//res1.txt");  //����Ԫ
		ifstream fileout1("D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//res0.txt");
		int num = 0;
		int num1 = 0;
		flagg = true;
		int needle = 0;
		while (a.size() > 5) {
			a.pop_back();
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j <= Len; j++) {
				a[i][j] = 0;
			}
		}
		while (needle < 5 && getline(file, line)) {
			string str;
			istringstream stream(line);
			int flag = false;
			while (stream >> str) {
				if (!flag) {
					reca[needle] = String_to_int(str);
					flag = true;
				}
				a[needle][String_to_int(str)] = 1;
			}
			needle++;
		}
		int p = 0;
		while (p < signal[curfile]) {
			getline(curfile == 1 ? fileout : fileout1, line);
			p++;
		}

		while (getline(curfile == 1 ? fileout : fileout1, line)) {// ���ļ��ж�ȡһ��
			signal[curfile]++;
			flagg = false;
			int start = 0;
			string str;
			istringstream stream(line);
			vector<int> b(90000, 0);
			bool flag = true;
			while (stream >> str) {
				if (flag) {
					start = String_to_int(str);
					flag = false;
				}
				b[String_to_int(str)] = 1;  //��ȡ����Ԫ��
			}
			flag = false;
			for (int i = 0; i < a.size(); i++) {
				if (start > reca[i]) {
					flag = true;
					a.insert(a.begin() + i, b);
					reca.insert(reca.begin() + i, start);
					inFile("D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//res2.txt", b);
					break;
				}
				else if (start < reca[i]) {
					continue;
				}
				else if (start == reca[i]) {
					b = xiaoyuan(b, a[i]);
					for (start; start >= 0; start--) {
						if (b[start]) {
							break;
						}
					}
					continue;
				}
			}
			if (!flag) {
				num1++;
				string curF = "res" + int_to_String(curfile ^ 1) + ".txt";
				inFile("D://Gusee//Groebner//��������2 ��������254��������Ԫ��106������Ԫ��53//" + curF, b);
			}
		}
		curfile = curfile ^ 1;
		if (flagg) {
			break;
		}
		fileout.close();
		fileout1.close();
		flagg = true;
	}
	fileout.close();
	fileout1.close();
	fileoutres.close();
	return 0;
}