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

// 定义对齐的矩阵
struct AlignedMatrix {
    alignas(32) double data[MAX_SIZE][MAX_SIZE + 1];
};

void initialize_matrix(AlignedMatrix& f, int n) {
    __m256d zero = _mm256_set1_pd(0.0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j += 4) {  // 4个双精度浮点数的块
            _mm256_storeu_pd(&f.data[i][j], zero); // 存储4个0
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
            return 0; // 无解
        }

        double pivot = f.data[i][i];
        __m256d pivot_vec = _mm256_set1_pd(pivot);

        for (int j = i; j <= n + 1; j += 4) {
            __m256d row_vec = _mm256_loadu_pd(&f.data[i][j]); // 加载4个值
            __m256d result_vec = _mm256_div_pd(row_vec, pivot_vec); // 除以pivot
            _mm256_storeu_pd(&f.data[i][j], result_vec); // 存储结果
        }

        for (int k = i + 1; k <= n; k++) {
            double scale = f.data[k][i];
            __m256d scale_vec = _mm256_set1_pd(scale);

            for (int j = i; j <= n + 1; j += 4) {
                __m256d row_i_vec = _mm256_loadu_pd(&f.data[i][j]);
                __m256d row_k_vec = _mm256_loadu_pd(&f.data[k][j]);
                __m256d subtract_vec = _mm256_mul_pd(row_i_vec, scale_vec); // 乘以scale
                __m256d result_vec = _mm256_sub_pd(row_k_vec, subtract_vec); // 减去
                _mm256_storeu_pd(&f.data[k][j], result_vec); // 存储
            }
        }
    }

    // 回代过程
    for (int k = n - 1; k >= 1; k--) {
        for (int j = n; j > k; j--) {
            f.data[k][n + 1] -= f.data[j][n + 1] * f.data[k][j];
        }
    }

    return 1; // 找到解
}
AlignedMatrix f;
int main() {
    int n;
    std::cin >> n;
 // 创建对齐矩阵
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
