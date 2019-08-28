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

void SelectionSort(int A[], int n) {
	for (int i = 0; i < n - 1; ++i)
	{
		int min = i;
		for (int j = i + 1; j < n; j++) {
			if (A[j] < A[min]) {
				min = j;
			}
		}
		if (min != i)
			Swap(A, min, i);
	}
}

void InsertionSort(int A[], int n) {
	for (int i = 1; i < n; ++i) {
		int get = A[i];
		int j = i - 1;
		while (j >= 0 && A[j] > get) {
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = get;
	}
}

void ShellSort(int A[], int n) {
	int h = 0;
	while (h <= n) {
		h = 3 * h + 1;
	}

	while (h >= 1) {
		for (int i = h; i < n; ++i) {
			int j = i - h;
			int get = A[i];
			while (j >= 0 && A[j] > get) {
				A[j + h] = A[j];
				j = j - h;
			}
			A[j + h] = get;
		}
		h = (h - 1) / 3;
	}
}

void Merge(int A[], int left, int mid, int right) {
	int len = right - left + 1;
	int *temp = new int[len];
	int index = 0;
	int i = left;
	int j = mid + 1;
	while (i <= mid && j <= right) {
		temp[index++] = A[i] <= A[j] ? A[i++] : A[j++];
	}
	while (i <= mid) {
		temp[index++] = A[i++];
	}
	while (j <= right) {
		temp[index++] = A[j++];
	}
	for (int k = 0; k < len; ++k) {
		A[left++] = temp[k];
	}
}

void MergeSortRecursion(int A[], int left, int right) {
	if (left == right)
		return;
	int mid = (left + right) / 2;
	MergeSortRecursion(A, left, mid);
	MergeSortRecursion(A, mid + 1, right);
	Merge(A, left, mid, right);
}

void MergeSortIteration(int A[], int len) {
	int left, mid, right;
	for (int i = 1; i < len; i *= 2) {
		left = 0;
		while (left + i < len) {
			mid = left + i - 1;
			right = mid + i < len ? mid + i : len - 1;
			Merge(A, left, mid, right);
			left = right + 1;
		}
	}
}


int main() {
	int A[] = {6, 5, 3, 1, 8, 7, 2, 4};
	int n = sizeof(A) / sizeof(int);
	MergeSortIteration(A, n);
	for (int i = 0; i < n; ++i) {
		cout << A[i] << " ";
	}
	cout << endl;
	return 0;
}