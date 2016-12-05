#ifndef AE
#define AE
#include<string.h>
#include<iostream>
#include"Stack.h"
#include"DealCharacter.h"

using namespace std;
//struct Information
//{
//	int Type;
//	union Value{
//		char c;//Type=0
//		double v;//Type=1;
//	}value;
//
//	friend ostream& operator<<(ostream &out, Information i);
//};
//
//ostream& operator<<(ostream &out, Information i){
//	if (i.Type = 0)
//		out << i.value.c;
//	else
//		out << i.value.v;
//	return out;
//}

class ArithmeticExpression
{
private:
	Stack<char> Temp;//template stack of character
	Stack<double> VTemp;//temeplate stack of double
	char *Inffix;
	char*Suffix;

	bool ChangeToSuffix();
	int GetPriority(char);
	
public:
	ArithmeticExpression(char *c){
		Inffix = c;
		Suffix = new char[50];
		Temp.Push('@');
	}
	char* GetSuffix(){
		ChangeToSuffix();
		return Suffix;
	}
	double Calculate();
};

bool ArithmeticExpression::ChangeToSuffix(){
	int len = strlen(Inffix);
	if (len > 50){
		cout << "the length of the expression is out of range!" << endl;
		return false;
	}
	int reg = 0;//record the indexof Suffix
	for (int i = 0; i < len; i++){
		//Number
		if (Inffix[i] >= 48 && Inffix[i] <= 57){
			Suffix[reg++] = Inffix[i++];
			while ((Inffix[i] >= 48 && Inffix[i] <= 57) || Inffix[i] == 46)
				Suffix[reg++] = Inffix[i++];
			Suffix[reg++] = ' ';
		}
		if (Inffix[i] == '\0')
			break;
		if (Inffix[i] == ' ')
			continue;
		else{//other character
			if (Inffix[i] == '('){
				Temp.Push(Inffix[i]);
				continue;
			}
			if (Inffix[i] == ')'){
				while (Temp.GetTop() != '('){
					Suffix[reg++] = Temp.Pop();
				}
				Temp.Pop();//remove '(' from stack Temp
				continue;
			}
			if (GetPriority(Inffix[i])>GetPriority(Temp.GetTop())){
				Temp.Push(Inffix[i]);//if the priority of Inffix[i] is bigger than the top element of Temp's push Inffix[i] into Temp.
			}
			else{
				Suffix[reg++] = Temp.Pop();
				Temp.Push(Inffix[i]);
			}
		}
	}
	//get all the characters tha still in the Temp stack
	while (Temp.GetTop() != '@'){
		Suffix[reg++] = Temp.Pop();
	}
	//add the end symbol
	Suffix[reg++] = '\0';
	return true;
}

int ArithmeticExpression::GetPriority(char c){
	switch (c)
	{
	case '@':
		return -1;
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		cout << "You input the wrong character." << endl;
		system("pause");
		exit(0);
		break;
	}
}


double ArithmeticExpression::Calculate(){
	bool jude = ChangeToSuffix();
	if (!jude){
		cout << "You input an unexpected expression!" << endl;
		return 0;
	}
	int len = strlen(Suffix);
	for (int i = 0; i < len; i++){
		//Number
		if (Suffix[i] >= 48 && Suffix[i] <= 57){
			char *charValue = new char[20];
		    int reg = 0;
			while ((Suffix[i] >= 48 && Suffix[i] <= 57) || Suffix[i] == 46)
				charValue[reg++] = Suffix[i++];
			charValue[reg++] = '\0';
			double value = CharacterToValue(charValue);
			VTemp.Push(value);
			//delete characters
			delete [] charValue;
		}
		if (Suffix[i] == ' ')
			continue;
		else{
			double right = VTemp.Pop();
			double left = VTemp.Pop();
			double value = 0;
			switch (Suffix[i])
			{
			case '+':
				value = left + right;
				VTemp.Push(value);
				break;
			case '-':
			    value = left - right;
				VTemp.Push(value);
				break;
			case '/':
				value = left / right;
				VTemp.Push(value);
				break;
			case '*':
				value = left*right;
				VTemp.Push(value);
				break;
			default:
				break;
			}
		}
	}
	return VTemp.Pop();
}
#endif