#include <immintrin.h> // AVX指令集
#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>
#include<fstream>
#include <fstream>  // 用于文件输入输出
#include <string>   // 用于字符串处
#include<sstream>
using namespace std;
const int N = 400;
const int Len = 255;
vector<vector<int> > a(5, vector<int>(90000, 0));//消元子
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
		if (load == "D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//res2.txt")
			fil << endl;
		return;
	}
	fil << endl;
	fil.close();
	return;
}
vector<int> xiaoyuan(const vector<int>& s, const vector<int>& q) {
	vector<int> result(s.size(), 0);
	for (size_t i = 0; i < s.size(); i += 8) { // 每次处理8个32位整数
		__m256i s_vec = _mm256_loadu_si256((__m256i*) & s[i]); // 加载AVX向量
		__m256i q_vec = _mm256_loadu_si256((__m256i*) & q[i]);
		__m256i result_vec = _mm256_xor_si256(s_vec, q_vec); // 执行按位异或
		_mm256_storeu_si256((__m256i*) & result[i], result_vec); // 存储结果
	}
	return result;
}
int  signal[2];
void get_duijiaoxian(int s[]) {

}
void get_xyz() {

}
int main() {

	//文件的初始化
	std::ofstream ofs1("D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//res1.txt", std::ios::trunc); // 使用 std::ios::trunc 标志来清空文件
	ofs1.close(); // 关闭文件流
	std::ofstream ofs2("D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//res0.txt", std::ios::trunc); // 使用 std::ios::trunc 标志来清空文件
	ofs2.close(); // 关闭文件流
	std::ofstream ofs3("D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//res2.txt", std::ios::trunc); // 使用 std::ios::trunc 标志来清空文件
	ofs3.close(); // 关闭文件流

	std::string sourceFile = "D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//被消元行.txt";
	// 目标文件路径
	std::string targetFile = "D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//res1.txt";
	// 打开源文件进行读取
	std::ifstream source(sourceFile, std::ios::binary);
	// 打开目标文件进行写入（如果不存在会创建，存在则覆盖）
	std::ofstream target(targetFile, std::ios::binary);
	// 检查文件是否成功打开
	if (!source.is_open() || !target.is_open()) {
		std::cerr << "Error: Could not open files." << std::endl;
		return 1;
	}
	// 使用流的拷贝操作，将源文件内容复制到目标文件
	target << source.rdbuf();
	// 关闭文件流
	source.close();
	target.close();



	ifstream file("D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//消元子 - 副本.txt");
	string line;
	int i = 0;
	int curfile = 1;
	string curFile = "res" + int_to_String(curfile) + ".txt";
	ofstream fileoutres;//最终的结果。
	fileoutres.open("D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//res2.txt", ios::app);
	ifstream fileout("D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//res1.txt");  //被消元
	ifstream fileout1("D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//res0.txt");
	bool flagg = true;
	while (flagg) {
		ifstream fileout("D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//res1.txt");  //被消元
		ifstream fileout1("D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//res0.txt");
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

		while (getline(curfile == 1 ? fileout : fileout1, line)) {// 从文件中读取一行
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
				b[String_to_int(str)] = 1;  //读取被消元素
			}
			flag = false;
			for (int i = 0; i < a.size(); i++) {
				if (start > reca[i]) {
					flag = true;
					a.insert(a.begin() + i, b);
					reca.insert(reca.begin() + i, start);
					inFile("D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//res2.txt", b);
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
				inFile("D://Gusee//Groebner//测试样例2 矩阵列数254，非零消元子106，被消元行53//" + curF, b);
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