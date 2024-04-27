#include <iostream>
#include <immintrin.h> // For AVX intrinsic functions
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

const int MAX_SIZE = 2001;
double esp = 1e-6;

void initialize_matrix(vector<vector<double>>& f, int n) {
    __m256d zero = _mm256_setzero_pd(); // ʹ�� _mm256_setzero_pd() ��������ȫ��� AVX �Ĵ���
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j += 8) { // ÿ�δ��� 8 ��˫���ȸ�����
            _mm256_storeu_pd(&f[i][j], zero); // ��ȫ��Ĵ����洢���ڴ���
        }
    }
}

int solve(vector<vector<double>>& f, int n) {
    for (int i = 1; i <= n; i++) {
        int r = i;
        for (int k = i; k <= n; k++) {
            if (fabs(f[k][i]) > esp) { r = k; break; }
        }
        if (r != i) {
            swap(f[i], f[r]);
        }
        if (fabs(f[i][i]) < esp) {
            return 0;
        }
        double pivot = f[i][i];
        __m256d pivot_vec = _mm256_set1_pd(pivot); // ʹ�� _mm256_set1_pd() ��������һ����λ�ĸ���������
        for (int j = i; j <= n + 1; j += 8) { // ÿ�δ��� 8 ��˫���ȸ�����
            __m256d row_vec = _mm256_loadu_pd(&f[i][j]); // ʹ�� _mm256_loadu_pd() �������� 8 ��˫���ȸ�����
            __m256d result_vec = _mm256_div_pd(row_vec, pivot_vec); // ʹ�� _mm256_div_pd() �������г���
            _mm256_storeu_pd(&f[i][j], result_vec); // ������洢���ڴ���
        }
        for (int k = i + 1; k <= n; k++) {
            double scale = f[k][i];
            __m256d scale_vec = _mm256_set1_pd(scale); // ʹ�� _mm256_set1_pd() ��������һ����λ�ĸ���������
            for (int j = i; j <= n + 1; j += 8) { // ÿ�δ��� 8 ��˫���ȸ�����
                __m256d row_i_vec = _mm256_loadu_pd(&f[i][j]);
                __m256d row_k_vec = _mm256_loadu_pd(&f[k][j]);
                __m256d subtract_vec = _mm256_mul_pd(row_i_vec, scale_vec);
                __m256d result_vec = _mm256_sub_pd(row_k_vec, subtract_vec);
                _mm256_storeu_pd(&f[k][j], result_vec);
            }
        }
    }
    for (int k = n - 1; k >= 1; k--) {
        for (int j = n; j > k; j--) {
            f[k][n + 1] -= f[j][n + 1] * f[k][j];
        }
    }
    return 1;
}

int main() {
    int n;
    cin >> n;
    vector<vector<double>> f(MAX_SIZE, vector<double>(MAX_SIZE + 1, 0));
    initialize_matrix(f, n);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n + 1; j++) {
            if (j == i) f[i][j] = 1;
            else f[i][j] = 2;
        }
    }
    if (solve(f, n)) {
        for (int i = 1; i <= n; i++) {
            cout << fixed << setprecision(2) << f[i][n + 1] << endl;
        }
    }
    else {
        cout << "No Solution" << endl;
    }
    return 0;
}
