#include <iostream>
#include "List.h"
using namespace std;


int main(){

	List<int> aList;
	aList.Push(1);
	aList.Push(2);
	aList.Push(3);
	aList.Show();

	aList.Delete(3);
	aList.Show();
	aList.Reverse();
	aList.Show();
     
	aList.Insert(1, 6);
	aList.Member(2) = 7;
	aList.Show();
	cout << aList.Length() << endl;
	system("pause");
	return 0;
}