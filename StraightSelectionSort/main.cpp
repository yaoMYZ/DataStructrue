#include<iostream>
#include"StraightSelectionSort.h"

using namespace std;

int main(){
	int a[] = { 12, 3, 54, 6, 10 };
	StraightSelectionSort(5, a);
	for (size_t i = 0; i < 5; i++)
	{
		cout << a[i] << " ";
	}
	system("pause");
}