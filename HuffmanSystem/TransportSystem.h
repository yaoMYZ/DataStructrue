#ifndef TRANSPORTSYSTEM
#define TRANSPORTSYSTEM

#include"HuffmanTree.h"
#include<fstream>
using namespace std;

template<class T>
class TransportSystem
{
private:
	HuffmanTree<T> ht;
public:
	void menu();
	void create();
	void coding();
	void encoding();
	void printCode();
	void printHuffTree();
};


template<class T>
void TransportSystem<T>::menu(){
	system("cls");
	int choose = 0;
	cout << "-----------------------------�ļ�����ϵͳ-----------------------------" << endl;
	cout << "                  ��1��ʼ��(Initializetion)" << endl;
	cout << "                  ��2����(Encoding)" << endl;
	cout << "                  ��3����(Coding)" << endl;
	cout << "                  ��4����(Clear Screen)" << endl;
	cout << "                  ��5��ӡ�����ļ�" << endl;
	cout << "                  ��6��ӡ��������" << endl;
	cout << "                  ��0�˳�ϵͳ" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << endl << endl << endl << "���������֣���ѡ���ܣ�";
	cin >> choose;
	switch (choose)
	{
	case 0:
		exit(0);
	case 1:
		system("cls");
		create();
		system("pause");
		menu();
		break;
	case 2:
		system("cls");
		coding();
		system("pause");
		menu();
		break;
	case 3:
		system("cls");
		encoding();
		system("pause");
		menu();
		break;
	case 4:
		menu();
		break;
	case 5:
		system("cls");
		printCode();
		system("pause");
		menu();
		break;
	case 6:
		system("cls");
		printHuffTree();
		system("pause");
		menu();
		break;
	default:
		cout << "����������������룡";
		system("pause");
		menu();
		break;
	}
}



template<class T>
void TransportSystem<T>::create(){
	ifstream in("HuffTree.bin",ios::binary|ios::in);
	if (in){
		int l, m;
		l = in.tellg();
		in.seekg(0, ios::end);//move the file point to the end of the file
		m = in.tellg();
		in.seekg(0, ios::beg);//move the file point back to the head of the file
		int len = (m - l) / sizeof(Sign<T>);//get the number of characters in the file
		Sign<T> *a = new Sign<T>[len];
		for (int i = 0; i < len; i++){
			in.read((char*)&a[i], sizeof(Sign<T>));
		}
		in.close();

		ht.CreateTree(a, len);
	}
	else{
		ofstream out("HuffTree.bin", ios::binary | ios::out);
		int charSize = 0;
		cout << "�������ַ�����С��" << endl;
		cin >> charSize;
		Sign<T> *a = new Sign<T>[charSize];
		for (size_t i = 0; i < charSize; i++){
			cout << "�������" << i + 1 << "���ַ�" << endl;
			a[i].member = getchar();
			cout << "�������" << i + 1 << "���ַ���Ȩֵ" << endl;
            a[i].weight = getchar();
			out.write((char*)&a[i], sizeof(Sign<T>));
		}
		/*Sign<char> a[] = { { 186, ' ' },{ 64, 'A' }, { 13, 'B' }, { 22, 'C' }, { 32, 'D' }, { 103, 'E' }, { 21, 'F' }, { 15, 'G' }, { 47, 'H' }, { 57, 'I' }, { 1, 'J' }, { 5, 'K' }, { 32, 'L' }, { 20, 'M' }, { 57, 'N' }, { 63, 'O' }, { 15, 'P' }, { 1, 'Q' }, { 48, 'R' }, { 51, 'S' }, { 80, 'T' }, { 23, 'U' }, { 8, 'V' }, { 18, 'W' }, { 1, 'X' }, { 16, 'Y' }, { 1, 'Z' } };
		for (int i = 0; i < 27; i++){
			out.write((char*)&a[i], sizeof(Sign<char>));
		}*/
		out.close();
		ht.CreateTree(a, charSize);
	}
	cout << "�ɹ�������" << endl;
}

template<class T>
void TransportSystem<T>::coding(){
	ifstream in("ToBeTran.txt");
    int l, m;
    l = in.tellg();
	in.seekg(0, ios::end);//move the file point to the end of the file
	m = in.tellg();
    in.seekg(0, ios::beg);//move the file point back to the head of the file
	int len = (m - l) / sizeof(T);//get the number of characters in the file
	T *a = new T[len+1];
	in.getline(a, 2*len);
	in.close();
    char *result=ht.Coding(a, len);
	ofstream out("CodeFile.txt");
	out << result;
	out.close();

	delete[] a;
	cout << "����ɹ���" << endl;
	
}


template<class T>
void TransportSystem<T>::encoding(){
	ifstream in("CodeFile.txt");
	int l, m;
	l = in.tellg();
	in.seekg(0, ios::end);//move the file point to the end of the file
	m = in.tellg();
	in.seekg(0, ios::beg);//move the file point back to the head of the file
	int len = (m - l) / sizeof(char);//get the number of characters in the file
	char *a = new char[len+1];
	in.getline(a, 2*len);
	in.close();

	T *result = ht.Encoding(a);
	ofstream out("TextFile.txt");
	out << result;
	out.close();

	delete[] a;
	cout << "����ɹ���" << endl;
}


template<class T>
void TransportSystem<T>::printCode(){
	ifstream in("CodeFile.txt");
	int l, m;
	l = in.tellg();
	in.seekg(0, ios::end);//move the file point to the end of the file
	m = in.tellg();
	in.seekg(0, ios::beg);//move the file point back to the head of the file
	int len = (m - l) / sizeof(char);//get the number of characters in the file

	ofstream out("CodePrint.txt");
	char *a = new char[51];
	int times=len/50;
	for(int i=0;i<times-1;i++){
		memset(a,'\0',51);
		for(int j=0;j<50;j++){
			in>>a[j];
		}
		cout<<a;
		out<<a;
	}
	int last=len-times*50;
	memset(a,'\0',51);
	for(int i=0;i<last;i++){
		in>>a[i];
	}
	cout<<a;
	out<<a;
	in.close();
	out.close();
	delete[] a;
}

template<class T>
void TransportSystem<T>::printHuffTree(){
	ht.ShowTree();
}

#endif