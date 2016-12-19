#ifndef STUDENTHEALTH
#define STUDENTHEALTH
#include<iostream>
#include<fstream>
#include"stdio.h"
#include"stdlib.h"
#include"NumberTree.h"
using namespace std;


struct Student
{
	char strName[10];
	char strSex[8];
	char strStudentID[15];
	char strBirthday[11];
	char Healthy[5];

	Student(){
		strcpy_s(strName, "0");
		strcpy_s(strSex, "0");
		strcpy_s(strStudentID, "0");
		strcpy_s(strBirthday, "0");
		strcpy_s(Healthy, "0");
	}
	Student & operator=(const Student other){
		strcpy_s(strName, other.strName);
		strcpy_s(strSex, other.strSex);
		strcpy_s(strStudentID, other.strStudentID);
		strcpy_s(strBirthday, other.strBirthday);
		strcpy_s(Healthy, other.Healthy);
		return *this;
	}

	friend bool operator<(Student &s1, Student &s2);
	friend ostream & operator<<(ostream & output, Student st);
	friend istream & operator>>(istream & input, Student &st);
};

bool operator<(Student &s1, Student &s2){
	if (strcmp(s1.strStudentID, s2.strStudentID)<0){
		return true;
	}
	else
		return false;
}

ostream & operator<<(ostream & output, Student st){
	cout << "���֣�" << st.strName << endl;
	cout << "�Ա�" << st.strSex << endl;
	cout << "ѧ�ţ�" << st.strStudentID << endl;
	cout << "���գ�" << st.strBirthday << endl;
	cout << "�����̶ȣ�" << st.Healthy << endl;
	cout << endl << endl;
	return output;
}

istream & operator>>(istream & input, Student &st){//st must pass address
	int judeHealth = 1;
	cout << "������������";
	input >> st.strName;
	cout << "�������Ա�";
	input >> st.strSex;
	cout << "������ѧ�ţ�";
	input >> st.strStudentID;
	cout << "���������գ���ʽ�磺1998/10/8)��";
	input >> st.strBirthday;
	cout << "�����뽡��״����������1��������2���������������֣���";
	input >> judeHealth;
	if (judeHealth == 1)
		strcpy_s(st.Healthy, "��");
	else if (judeHealth == 2)
		strcpy_s(st.Healthy, "��");
	else
		strcpy_s(st.Healthy, "��");
	cout << endl;
	return input;
}


class StudentHealth{
private:
	NumberTree<Student> STree;
	int Length;

	//jude if the length of the array overflow
	bool IfLenOutOfRange(char a[]){
		if (strlen(a) >= sizeof(a)* 2){
			cout << "�ַ����磬���������룡" << endl;
			system("pause");
			return true;
		}
		else
			return false;

	}

	//QuickSort
	int Quick1(Student * a, int left, int right)
	{
		Student x = a[right];
		int left1 = left - 1;
		for (int moveleft = left; moveleft<right; moveleft++)
		{
			if (a[moveleft]<x)
			{
				left1++;
				Student temp = a[left1];
				a[left1] = a[moveleft];
				a[moveleft] = temp;
			}
		}
		Student temp1 = a[left1 + 1];
		a[left1 + 1] = a[right];
		a[right] = temp1;
		return left1 + 1;
	}

	void Quicksort(Student *a, int p, int r)
	{
		if (p<r)
		{
			int q = Quick1(a, p, r);
			Quicksort(a, p, q - 1);
			Quicksort(a, q + 1, r);

		}
	}

	//write the data to the file
	void Write(){
		char *rout = "Information.dat";
		STree.layerOrder(rout, sizeof(Student));
		cout << "���ݴ���ɹ���" << endl;
		system("pause");
		return;
	}

	void Initial(){
		ifstream read("Information.dat", ios::binary | ios::in);
		int l, m;
		l = read.tellg();
		read.seekg(0, ios::end);//move the file point to the end of the file
		m = read.tellg();
		read.seekg(0, ios::beg);//move the file point back to the head of the file
		int len = (m - l) / sizeof(Student);//get the number of the Student structrue in the file
		Length = len;
		for (int i = 1; i <= Length; i++){
			Student temp;
			read.read((char*)&temp, sizeof(Student));
			STree.insert(temp,temp.strStudentID);
			//add the charater '\0' to every element of STree[i]
		}
		read.close();
	}


public:
	StudentHealth(){
		Initial();
	}

	~StudentHealth(){
		Write();
	}

	void Menu(){
		system("cls");
		int choose = 0;
		cout << "-----------------------------ѧ����������ϵͳ-----------------------------" << endl;
		cout << "                  ��1�½�ѧ��������" << endl;
		cout << "                  ��2��ѧ������������µ�ѧ����Ϣ" << endl;
		cout << "                  ��3�ڽ�����ɾ��ָ��ѧ������Ϣ����ѧ�Ų�����" << endl;
		cout << "                  ��4Ϊĳ��ѧ���޸�����״����Ϣ����ѧ�Ų�����" << endl;
		cout << "                  ��5��ѧ����ѧ��������ʾ���" << endl;
		cout << "                  ��6�ڽ������в�ѯѧ����Ϣ����ѧ��ѧ�������в��ң�" << endl;
		cout << "                  ��7����Ļ�����ȫ��ѧ����Ϣ" << endl;
		cout << "                  ��8����" << endl;
		cout << "                  ��9�����ݴ����ļ���" << endl;
		cout << "                  ��0�����ݴ����ļ����˳�ϵͳ" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << endl << endl << endl << "���������֣���ѡ���ܣ�";
		cin >> choose;
		switch (choose)
		{
		case 0:
			exit(0);
		case 1:
			system("cls");
			CreateHealthNumberTree();
			system("pause");
			Menu();
			break;
		case 2:
			system("cls");
			AddStudent();
			system("pause");
			Menu();
			break;
		case 3:
			system("cls");
			DeleteStudent();
			system("pause");
			Menu();
			break;
		case 4:
			system("cls");
			ChangeInformation();
			system("pause");
			Menu();
			break;
		case 5:
			system("cls");
			ShowInformationByID();
			system("pause");
			Menu();
			break;
		case 6:
			system("cls");
			FindStudent();
			system("pause");
			Menu();
			break;
		case 7:
			system("cls");
			ShowStudentInformation();
			system("pause");
			Menu();
			break;
		case 8:
			Menu();
			break;
		case 9:
			system("cls");
			Write();
			system("pause");
			Menu();
			break;
		default:
			cout << "����������������룡";
			system("pause");
			Menu();
			break;
		}
	}

	void CreateHealthNumberTree(){
		//clear the NumberTree
		STree.clear();
		Length = 0;
		cout << "������ѧ��������";
		int number = 0;
		cin >> number;
		for (int i = 0; i < number; i++){
			Student temp;
			cin >> temp;
			STree.insert(temp,temp.strStudentID);
			Length++;
		}
	}


	void AddStudent(){
		Student temp;
		cin >> temp;
		if (STree.hasMember(temp.strStudentID)){
			cout << "�Ѵ��ڸ�ѧ��ѧ�������������룡" << endl;
			AddStudent();
		}
		STree.insert(temp,temp.strStudentID);
		Length++;
		cout << "��ϲ��ӳɹ���" << endl;
	}


	void DeleteStudent(){
		char ID[15];
		cout << "������ѧ����ѧ�ţ�";
		cin >> ID;
		if (!STree.hasMember(ID)){
			cout << "û�д�ѧ�������������룡" << endl;
			DeleteStudent();
		}
		else{
			STree.remove(ID);
		}
		cout << "ɾ���ɹ���" << endl;
	}

	void ChangeInformation(){
		char ID[15];
		cout << "������ѧ����ѧ�ţ�";
		cin >> ID;
		if (!STree.hasMember(ID)){
			cout << "û�д�ѧ�������������룡" << endl;
			ChangeInformation();
		}
		else{
			Student temp;
			cin >> temp;
			STree.insert(temp, temp.strStudentID);
		}
		cout << "ѧ����Ϣ�޸ĳɹ���" << endl;
	}

	void ShowStudentInformation(){
		STree.inOrder(Visit);
	}

	void FindStudent(){
		char ID[15];
		cout << "������ѧ����ѧ�ţ�";
		cin >> ID;
		if (!STree.hasMember(ID)){
			cout << "û����ѧ�������������룡" << endl;
			FindStudent();
		}
		cout << STree.getMember(ID);
	}

	void ShowInformationByID(){
		STree.layerOrder(Visit);
	}
};


#endif