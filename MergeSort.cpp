#include<iostream>
#include<vector>
using namespace std;
int STEP = 0;
int N = 0;

void In(const int a[], const char* note) {
	cout << "lan" << ++STEP << ": (";
	for (int k = 0; k < N; ++k) {
		cout << a[k] << (k + 1 < N ? ' ' : '\0');
	}
	cout << ")  // " << note << "\n";
}
void merge(int a[], int l, int m, int r) {
	vector <int> x(a + l, a + m + 1);
	vector <int> y(a + m + 1, a + r + 1);
	int i = 0, j = 0;
	while (i < x.size() && j < y.size()) {
		if (x[i] <= y[j]) {
			a[l] = x[i]; ++l; ++i;
		}
		else {
			a[l] = y[j]; ++l; ++j;
		}
		In(a, "merge both");
		
	}
	while (i < x.size()) {
		a[l] = x[i]; ++l; ++i;
		In(a, "copy left tail");
		
	}
	while (j < y.size()) {
		a[l] = y[j]; ++l; ++j;
		In(a, "copy right tail");
	}
}
void mergeSort(int a[], int l, int r) {
	if (l >= r) return;
	int m = (l + r) / 2;
	mergeSort(a, l, m);
	mergeSort(a, m + 1, r);
	merge(a, l, m, r);
	
}
int main() {
	int n;
	cin >> n;
	N = n;
	int* a = new int[n];
	for (int i = 0; i < n; ++i) cin >> a[i];

	mergeSort(a, 0, n - 1);

	for (int i = 0; i < n; ++i) cout << a[i] << ' ';
	delete[] a;                       
	return 0;
}