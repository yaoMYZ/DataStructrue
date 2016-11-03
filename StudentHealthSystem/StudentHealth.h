#ifndef STUDENTHEALTH
#define STUDENTHEALTH
#include<iostream>
#include<fstream>
#include"stdio.h"
#include"stdlib.h"
#include"List.h"
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
	List<Student> SHlist;
	int Length;

	//jude if the length of the array overflow
	bool IfLenOutOfRange(char a[]){
	    if (strlen(a)>=sizeof(a)*2){
		   cout<<"�ַ����磬���������룡"<<endl;
		   system("pause");
		   return true;
		}else
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
		ofstream write("Information.dat", ios::binary|ios::out);
		for (int i = 1; i <= Length;i++){
			write.write((char*)&SHlist.Member(i), sizeof(Student));
		}
		write.close();
	}

	void Initial(){
		ifstream read("Information.dat", ios::binary|ios::in);
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
			SHlist.Push(temp);
			//add the charater '\0' to every element of SHlist[i]
		}
		read.close();
	}


public:
	StudentHealth(){
		Initial();
	}

	~StudentHealth(){

	}

	void Menu(){
		system("cls");
		int choose = 0;
		cout << "-----------------------------ѧ����������ϵͳ-----------------------------" << endl;
		cout << "                  ��1�½�ѧ��������" << endl;
		cout << "                  ��2��ѧ������������µ�ѧ����Ϣ" << endl;
		cout << "                  ��3��ѧ������������µ�ѧ����Ϣ����λ�ú�����������㣩" << endl;
		cout << "                  ��4�ڽ�����ɾ��ָ��ѧ������Ϣ����ѧ�Ų�����" << endl;
		cout << "                  ��5Ϊĳ��ѧ���޸�����״����Ϣ����ѧ�Ų�����" << endl;
		cout << "                  ��6��ѧ����ѧ��������ʾ���" << endl;
		cout << "                  ��7�ڽ������в�ѯѧ����Ϣ����ѧ��ѧ�������в��ң�" << endl;
		cout << "                  ��8����Ļ�����ȫ��ѧ����Ϣ" << endl;
		cout << "                  ��9����" << endl;
		cout << "                  ��0�˳�ϵͳ" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << endl << endl << endl << "���������֣���ѡ���ܣ�";
		cin >> choose;
		switch (choose)
		{
		case 0:
			exit(0);
		case 1:
			system("cls");
			CreateHealthList();
			break;
		case 2:
			system("cls");
			AddStudent();
			break;
		case 3:
			system("cls");
			InsertStudent();
			break;
		case 4:
			system("cls");
			DeleteStudent();
			break;
		case 5:
			system("cls");
			ChangeInformation();
			break;
		case 6:
			system("cls");
			ShowInformationByID();
			break;
		case 7:
			system("cls");
			FindStudent();
			break;
		case 8:
			system("cls");
			ShowStudentInformation();
			break;
		case 9:
			Menu();
			break;
		default:
			cout << "����������������룡";
			system("pause");
			Menu();
			break;
		}
	}

	void CreateHealthList(){
		SHlist.Clear();
		cout << "������ѧ��������";
		int number = 0;
		cin >> number;
		for (int i = 0; i < number; i++){
			Student temp;
			cin >> temp;
			SHlist.Push(temp);
			Length++;
		}
		Write();
		system("pause");
		Menu();
	}


	void AddStudent(){
		Student temp;
		cin >> temp;
		for (int i = 1; i <= Length; i++){
			Student s = SHlist.Member(i);
			if (strcmp(s.strStudentID, temp.strStudentID) == 0){
				cout << "�����ѧ���Ѵ��ڣ����������룡" << endl;
				system("pause");
				system("cls");
				AddStudent();
			}
		}
		SHlist.Push(temp);
		Length++;
		Write();
		system("pause");
		Menu();
	}

	void InsertStudent(){
		int pos = 0;
		cout << "���������λ�ã�����1���뵽��һ��λ�ã��Դ����ƣ���";
		cin >> pos;
		if (pos > Length+1||pos<1){
			cout << "�����������������룡";
			InsertStudent();
		}
		Student temp;
		cin >> temp;
		SHlist.Insert(pos, temp);
		Length++;
		Write();
		system("pause");
		Menu();
	}

	void DeleteStudent(){
		char ID[15];
		cout << "������ѧ����ѧ�ţ�";
		cin >> ID;
		bool IfHaveID = false;
		for (int i = 1; i <= Length; i++){
			if (strcmp(ID, SHlist.Member(i).strStudentID) == 0){
				SHlist.Delete(i);
				IfHaveID = true;
				Length--;
				Write();
				break;
			}
		}
		if (!IfHaveID){
			cout << "û����ѧ�������������룡" << endl;
			DeleteStudent();
		}else{
			cout << "��ϲ�����ɹ���" << endl;
		}
		system("pause");
		Menu();
	}

	void ChangeInformation(){
		char ID[15];
		cout << "������ѧ����ѧ�ţ�";
		cin >> ID;
		bool IfHaveID = false;
		for (int i = 1; i <= Length; i++){
			if (strcmp(ID, SHlist.Member(i).strStudentID) == 0){
				Student temp;
				cin >> temp;
				SHlist.Replace(i, temp);
				IfHaveID = true;
				Write();
				break;
			}
		}
		if (!IfHaveID){
			cout << "û����ѧ�������������룡" << endl;
			ChangeInformation();
		}else{
			cout << "��ϲ�����ɹ���" << endl;
		}
		system("pause");
		Menu();
	}

	void ShowStudentInformation(){
		for (int i = 1; i <= Length; i++){
			cout << SHlist.Member(i);
		}
		system("pause");
		Menu();
	}

	void FindStudent(){
		char ID[15];
		cout << "������ѧ����ѧ�ţ�";
		cin >> ID;
		bool IfHaveID = false;
		for (int i = 1; i <= Length; i++){
			if (strcmp(ID, SHlist.Member(i).strStudentID) == 0){
				cout << SHlist.Member(i);
				IfHaveID = true;
				break;
			}
		}
		if (!IfHaveID){
			cout << "û����ѧ�������������룡" << endl;
			FindStudent();
		}
		system("pause");
		Menu();
	}

	void ShowInformationByID(){
		Student *newList = new Student[Length];
		for (int index = 1; index <= Length; index++)
			newList[index - 1] = SHlist.Member(index);
		Quicksort(newList, 0, Length - 1);
		for (int i = 0; i < Length; i++){
			cout << newList[i];
		}
		delete[] newList;
		system("pause");
		Menu();
	}
};


#endif