#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<math.h>
typedef long long LL;
using namespace std;
int N;
vector<vector<double> > f(2020, vector<double>(2020, 0));
double esp = 1e-6;

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = i; j <= N + 1; j++) {
			if (j == i)f[i][j] = 1;
			else f[i][j] = 2;
		}
	}
	return;
}
int solve() {
	for (int i = 1; i <= N; i++) {
		int r = i;
		for (int k = i; k <= N; k++) {
			if (fabs(f[k][i]) > esp) { r = k; break; }
		}
		if (r != i)(swap(f[i], f[r]));
		if (fabs(f[i][i]) < esp) { return 0; };
		for (int j = N + 1; j >= i; j--) {
			f[i][j] /= f[i][i];
		}
		for (int k = i + 1; k <= N; k++) {
			for (int j = N + 1; j >= i; j--) {
				f[k][j] -= f[k][i] * f[i][j];
			}
		}
	}
	for (int k = N - 1; k >= 1; k--) {
		for (int j = N; j > k; j--) {
			f[k][N + 1] -= f[j][N + 1] * f[k][j];
		}
	}
	return 1;
}
int main() {
	input();
	if (solve()) {
		for (int i = 1; i <= N; i++) {
			cout << fixed << setprecision(2) << f[i][N + 1] << endl;
		}
	}
	else {
		cout << "No Solution" << endl;
	}
	return 0;
}