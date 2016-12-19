#include<iostream>
#include"CycleList.h"
using namespace std;
int main()
{
	CycleList<int> c;
	c.Push(1);
	c.Push(2);
	c.Show();
	system("pause");
	return 0;
}