#include<iostream>
#include"BinarySearch.h"
using namespace std;

int main(){
	char *a = "abcdefghi";
	cout << BinarySearch('a', a, strlen(a)) << endl;
	cout << BinarySearch('t', a, strlen(a));
	system("pause");
}