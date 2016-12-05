#include<iostream>
#include<cstdio>
#include"ArithmeticExpressionn.h"
#include"DealCharacter.h"
#include"Stack.h"


using namespace std;




int main()
{
	cout << "Please input the expression:" << endl;
	char *c = new char[50];
	while (cin >> c){
		ArithmeticExpression a(c);
		cout << "Here is the result." << endl;
		cout << a.Calculate() << endl;
		system("pause");
		system("cls");
		cout << "Please input the expression:" << endl;
	}
	
	return 0;
}