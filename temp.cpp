#include <iostream>
using namespace std;

void Swap(int A[], int i, int j) {
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

void BubbleSort(int A[], int n) {
	for (int j = 0; j < n - 1; ++j) {
		for (int i = 0; i < n - 1 - j; ++i) {
			if (A[i] > A[i + 1]) {
				Swap(A, i, i + 1);
			}
		}
	}
}

void CocktailSort(int A[], int n) {
	int left = 0;
	int right = n - 1;
	while (left < right) {
		for (int i = left; i < right; ++i) {
			if (A[i] > A[i + 1])
				Swap(A, i, i + 1);
		}
		right--;
		for (int i = right; i > left; --i) {
			if (A[i - 1] > A[i])
				Swap(A, i - 1, i);
		}
		left++;
	}
}

int main() {
	int A[] = {6, 5, 3, 1, 8, 7, 2, 4};
	int n = sizeof(A) / sizeof(int);
	CocktailSort(A, n);
	for (int i = 0; i < n; ++i) {
		cout << A[i] << " ";
	}
	cout << endl;
	return 0;
}