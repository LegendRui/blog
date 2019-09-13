#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int interval, M;
		cin >> interval >> M;
		vector<int> coffeedays(M);
		if (M != 0) {
			for (int j = 0; j < M; ++j) {
				cin >> coffeedays[j];
			}
			int drinkDays = 0;
			int lastDrinkDay = -1;
			for (int j = 1, k = 0; j <= 30; j++) {
				if (j == coffeedays[k]) {
					drinkDays++;
					lastDrinkDay = j;
					++k;
					if (k == M)
						k--;
				} else if (j <= coffeedays[k] && j - lastDrinkDay >= interval + 1 && coffeedays[k] - j >= interval) {
					drinkDays++;
					lastDrinkDay = j;
				} else if (j > coffeedays[k] && j - lastDrinkDay >= interval + 1) {
					drinkDays++;
					lastDrinkDay = j;
				}
			}
			cout << drinkDays << endl;
		} else {
			int drinkDays = 0;
			int lastDrinkDay = -1;
			for (int j = 1, k = 0; j <= 30; j++) {
				if (j - lastDrinkDay >= interval + 1) {
					drinkDays++;
					lastDrinkDay = j;
				}
			}
			cout << drinkDays << endl;
		}
		// cout << drinkDays << endl;
	}
	return 0;
}
