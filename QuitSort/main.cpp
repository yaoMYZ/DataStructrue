#include<iostream>
#include"QuitSort.h"
using namespace std;

int main(){
	int a[] = { 34, 342, 3, 34, 59, 9, 10 };
	int A[] = { 1, 2, 3, 4, 5, 6, 7 };
	int aa[] = { 7, 6, 5, 4, 3, 2, 1 };
	QuitSort(0, 6, A);
	for (size_t i = 0; i < 7; i++){
		cout << aa[i] << " ";
	}
	system("pause");
	return 0;
}