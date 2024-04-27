#include <immintrin.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

typedef long long LL;
using namespace std;

const int MAX_SIZE = 2000;
double esp = 1e-6;

// �������ľ���
struct AlignedMatrix {
    alignas(32) double data[MAX_SIZE][MAX_SIZE + 1];
};

void initialize_matrix(AlignedMatrix& f, int n) {
    __m256d zero = _mm256_set1_pd(0.0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j += 4) {  // 4��˫���ȸ������Ŀ�
            _mm256_storeu_pd(&f.data[i][j], zero); // �洢4��0
        }
    }
}

int solve(AlignedMatrix& f, int n) {
    for (int i = 1; i <= n; i++) {
        int r = i;
        for (int k = i; k <= n; k++) {
            if (fabs(f.data[k][i]) > esp) {
                r = k;
                break;
            }
        }

        if (r != i) {
            std::swap(f.data[i], f.data[r]);
        }

        if (fabs(f.data[i][i]) < esp) {
            return 0; // �޽�
        }

        double pivot = f.data[i][i];
        __m256d pivot_vec = _mm256_set1_pd(pivot);

        for (int j = i; j <= n + 1; j += 4) {
            __m256d row_vec = _mm256_loadu_pd(&f.data[i][j]); // ����4��ֵ
            __m256d result_vec = _mm256_div_pd(row_vec, pivot_vec); // ����pivot
            _mm256_storeu_pd(&f.data[i][j], result_vec); // �洢���
        }

        for (int k = i + 1; k <= n; k++) {
            double scale = f.data[k][i];
            __m256d scale_vec = _mm256_set1_pd(scale);

            for (int j = i; j <= n + 1; j += 4) {
                __m256d row_i_vec = _mm256_loadu_pd(&f.data[i][j]);
                __m256d row_k_vec = _mm256_loadu_pd(&f.data[k][j]);
                __m256d subtract_vec = _mm256_mul_pd(row_i_vec, scale_vec); // ����scale
                __m256d result_vec = _mm256_sub_pd(row_k_vec, subtract_vec); // ��ȥ
                _mm256_storeu_pd(&f.data[k][j], result_vec); // �洢
            }
        }
    }

    // �ش�����
    for (int k = n - 1; k >= 1; k--) {
        for (int j = n; j > k; j--) {
            f.data[k][n + 1] -= f.data[j][n + 1] * f.data[k][j];
        }
    }

    return 1; // �ҵ���
}
AlignedMatrix f;
int main() {
    int n;
    std::cin >> n;
 // �����������
    initialize_matrix(f, n);

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n + 1; j++) {
            if (i == j)f.data[i][j] = 1;
            else f.data[i][j] = 2;
        }
    }

    if (solve(f, n)) {
        for (int i = 1; i <= n; i++) {
            std::cout << std::fixed << std::setprecision(2) << f.data[i][n + 1] << std::endl;
        }
    }
    else {
        std::cout << "No Solution" << std::endl;
    }

    return 0;
}
