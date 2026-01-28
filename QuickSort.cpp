#include<iostream>
using namespace std;
int STEP = 0;
int N = 0;
// do phuc tap O(n^2)
void In(int a[], const char* note, int pivot, int i, int j) {
	cout << "lan" << ++STEP << ": (";
	for (int k = 0; k < N; ++k) {
		cout << a[k];
		if (k + 1 < N) cout << ' ';
	}
	cout << ")";
	if (note) cout << "  // " << note << ", pivot=" << pivot << ", i=" << i << ", j=" << j;
	cout << "\n";
}
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
int partition(int a[], int l, int r) {
	int pivot = a[l];
	int i = l + 1, j = r;
	while (1) {
		while (a[i] < pivot && i <= r) i++;
		while (a[j] > pivot && j >= l) j--;
		if (i >= j) break;
		swap(a[i], a[j]); ++i; --j;
	}
	swap(a[l], a[j]);
	In(a, "QS: ket thuc partition, p = j", pivot, i, j);
	return j;
}


void quicksort(int a[], int l, int r) {
	if (l >= r) return;
	int p = partition(a, l, r);
	quicksort(a, l, p - 1);
	quicksort(a, p + 1, r);
	
} 
int main() {
	int a[1000], n;
	cin >> n;
	N = n;                     
	for (int i = 0; i < n; i++) cin >> a[i];

	quicksort(a, 0, n - 1);

	for (int i = 0; i < n; i++) cout << a[i] << " ";
	return 0;
}
