template<class T>
int Quite1(T a[], int left, int right)
{
	int x = a[right];
	int left1 = left - 1;
	for (int moveleft = left; moveleft<right; moveleft++)
	{
		if (a[moveleft]<x)
		{
			left1++;
			int temp = a[left1];
			a[left1] = a[moveleft];
			a[moveleft] = temp;
		}
	}
	int temp1 = a[left1 + 1];
	a[left1 + 1] = a[right];
	a[right] = temp1;
	return left1 + 1;
}

template<class T>
void Quitesort(T a[], int p, int r)
{
	if (p<r)
	{
		int q = Quite1(a, p, r);
		Quitesort(a, p, q - 1);
		Quitesort(a, q + 1, r);
	}
}