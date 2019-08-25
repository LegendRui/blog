#include <iostream>
using namespace std;

struct A {
	char a;
	int b;
	short c;
	double e;
};
struct B {
	char a;
	short b;
	int c;
	float e;
};
int main()  {
	cout << sizeof(A) << " " << sizeof (B);
	return 0;
}