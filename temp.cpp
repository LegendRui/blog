int f(int *const p)
{
	return *p + 1;
}

int main()
{
	int a = 3;
	f(&a);
	return 0;
}