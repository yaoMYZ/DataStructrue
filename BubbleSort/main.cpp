#include<iostream>
#include"BubbleSort.h"

using namespace std;

int main(){
	int a[] = { 12, 23, 4, 6, 30, 5 };
	BubbleSort(6, a);
	for (size_t i = 0; i < 6; i++){
		cout << a[i] << " ";
	}
	system("pause");
	return 0;
}