#ifndef STUDENTHEALTH
#define STUDENTHEALTH
#include<iostream>
#include<fstream>
#include"stdio.h"
#include"stdlib.h"
using namespace std;


struct Student
{
	char strName[10];
	char strSex[8];
	char strStudentID[15];
	char strBirthday[11];
	char IfHealthy[5];

	Student & operator=(Student other){
		strcpy_s(strName, other.strName);
		strcpy_s(strSex, other.strSex);
		strcpy_s(strStudentID, other.strStudentID);
		strcpy_s(strBirthday, other.strBirthday);
		strcpy_s(IfHealthy, other.IfHealthy);
		return *this;
	}
};


class StudentHealth{
private:
	Student *SHlist;
	int index;
	int MaxSize;

	void JudeIfOverflow(){
		if (index >= MaxSize){//Jude data overflow
			Student *newList = new Student[MaxSize * 2];//To apply for a bigger array
			memmove(newList, SHlist, sizeof(Student)*MaxSize);
			MaxSize *= 2;
			delete[] SHlist;
			SHlist = newList;//variable SHlist point to the variable newList
		}
	}

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
			if (a[moveleft].strStudentID<x.strStudentID)
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
		for (int i = 0; i < index; i++){
			write.write((char*)&SHlist[i], sizeof(SHlist[i]));
		}
		write.close();
	}
	void Initial(){
		index = 0;
		MaxSize = 100;
		if (SHlist == NULL)
			SHlist = new Student[MaxSize];
		ifstream read("Information.dat", ios::binary|ios::in);
		int l, m;
		l = read.tellg();
		read.seekg(0, ios::end);//move the file point to the end of the file
		m = read.tellg();
		read.seekg(0, ios::beg);//move the file point back to the head of the file
		int len = (m - l) / sizeof(Student);//get the number of the Student structrue in the file
		for (int i = 0; i < len; i++){
			read.read((char*)&SHlist[i], sizeof(SHlist[i]));
			//add the charater '\0' to every element of SHlist[i]
			index++;
		}
		read.close();
	}


public:
	StudentHealth(){
		SHlist = NULL;
		Initial();
	}

	~StudentHealth(){
		if (SHlist != NULL)
			delete[] SHlist;
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
		cout << "������ѧ��������";
		int number = 0;
		cin >> number;
		int judeHealth = 1;
		for (int i = 0; i < number; i++){
			bool bJudeRange=false;
			cout << "������������";
			cin >> SHlist[i].strName;
			bJudeRange=IfLenOutOfRange(SHlist[i].strName);
			if (bJudeRange){
			   fflush(stdout);
			   system("cls");
			   i--;
			   continue;
			}
			cout << "�������Ա�";
			cin >> SHlist[i].strSex;
			bJudeRange=IfLenOutOfRange(SHlist[i].strSex);
			if (bJudeRange){
				fflush(stdout);
               system("cls");
			   i--;
			   continue;
			}
			cout << "������ѧ�ţ�";
			cin >> SHlist[i].strStudentID;
			bJudeRange=IfLenOutOfRange(SHlist[i].strStudentID);
			if (bJudeRange){
				fflush(stdout);
               system("cls");
			   i--;
			   continue;
			}
			cout << "���������գ���ʽ�磺1998/10/8)��";
			cin >> SHlist[i].strBirthday;
			bJudeRange=IfLenOutOfRange(SHlist[i].strBirthday);
			if (bJudeRange){
			   fflush(stdout);
			   system("cls");
			   i--;
			   continue;
			}
			cout << "�����뽡��״��������������0�����������0�ַ�����";
			cin >> judeHealth;
			if (judeHealth == 0)
				strcpy_s(SHlist[i].IfHealthy, "��");
			else
				strcpy_s(SHlist[i].IfHealthy, "��");
			index++;
			cout << endl;
		}
		Write();
		cout << "���������" << endl;
		system("pause");
		Menu();
	}


	void AddStudent(){
		JudeIfOverflow();//Jude data overflow
		bool bJudeRange=false;
		int judeHealth = 1;
		cout << "������������";
		cin >> SHlist[index].strName;
		bJudeRange=IfLenOutOfRange(SHlist[index].strName);
		if (bJudeRange){
		   system("cls");
		   AddStudent();
		}
		cout << "�������Ա�";
		cin >> SHlist[index].strSex;
		bJudeRange=IfLenOutOfRange(SHlist[index].strSex);
		if (bJudeRange){
		   system("cls");
		   AddStudent();
		}
		cout << "������ѧ�ţ�";
		cin >> SHlist[index].strStudentID;
		bJudeRange=IfLenOutOfRange(SHlist[index].strStudentID);
		if (bJudeRange){
		   system("cls");
		   AddStudent();
		}
		cout << "���������գ���ʽ�磺1998/10/8)��";
		cin >> SHlist[index].strBirthday;
		bJudeRange=IfLenOutOfRange(SHlist[index].strBirthday);
		if (bJudeRange){
		   system("cls");
		   AddStudent();
		}
		cout << "�����뽡��״��������������0�����������0�ַ�����";
		cin >> judeHealth;
		if (judeHealth == 0)
			strcpy_s(SHlist[index].IfHealthy, "��");
		else
			strcpy_s(SHlist[index].IfHealthy, "��");
		index++;
		Write();
		system("pause");
		Menu();
	}

	void InsertStudent(){
		JudeIfOverflow();//Jude data overflow
		int pos = 0;
		cout << "���������λ�ã�����0���뵽��һ��λ�ã��Դ����ƣ���";
		cin >> pos;
		if (pos > index){
			cout << "�����������������룡";
			InsertStudent();
		}
		for (int i = index - 1; i >= pos; i--){//all elements after the index of pos move backward one byte
			SHlist[i + 1] = SHlist[i];
		}
		index++;

		bool bJudeRange=false;
		int judeHealth = 1;
		cout << "������������";
		cin >> SHlist[pos].strName;
		bJudeRange=IfLenOutOfRange(SHlist[pos].strName);
		if (bJudeRange){
		   system("cls");
		   InsertStudent();
		}
		cout << "�������Ա�";
		cin >> SHlist[pos].strSex;
		bJudeRange=IfLenOutOfRange(SHlist[pos].strSex);
		if (bJudeRange){
		   system("cls");
		   InsertStudent();
		}
		cout << "������ѧ�ţ�";
		cin >> SHlist[pos].strStudentID;
		bJudeRange=IfLenOutOfRange(SHlist[pos].strStudentID);
		if (bJudeRange){
		   system("cls");
		   InsertStudent();
		}
		cout << "���������գ���ʽ�磺1998/10/8)��";
		cin >> SHlist[pos].strBirthday;
		bJudeRange=IfLenOutOfRange(SHlist[pos].strBirthday);
		if (bJudeRange){
		   system("cls");
		   InsertStudent();
		}
		cout << "�����뽡��״��������������0�����������0�ַ�����";
		cin >> judeHealth;
		if (judeHealth == 0)
			strcpy_s(SHlist[pos].IfHealthy, "��");
		else
			strcpy_s(SHlist[pos].IfHealthy, "��");
		Write();
		system("pause");
		Menu();
	}

	void DeleteStudent(){
		char ID[15];
		cout << "������ѧ����ѧ�ţ�";
		cin >> ID;
		bool IfHaveID = false;
		for (int i = 0; i < index; i++){
			if (strcmp(ID, SHlist[i].strStudentID) == 0){
				if (i != index - 1){//if i==index-1,we should do not thing but let index--;
					for (int j = i; j < index - 1; j++){
						SHlist[j] = SHlist[j + 1];
					}
				}
				IfHaveID = true;
				index--;
				Write();
				break;
			}
		}
		if (!IfHaveID)
			cout << "û����ѧ����" << endl;
		system("pause");
		Menu();
	}

	void ChangeInformation(){
		char ID[15];
		cout << "������ѧ����ѧ�ţ�";
		cin >> ID;
		bool IfHaveID = false;
		for (int i = 0; i < index; i++){
			if (strcmp(ID, SHlist[i].strStudentID) == 0){
				bool bJudeRange=false;
				int judeHealth = 1;
				cout << "������������";
				cin >> SHlist[i].strName;
				bJudeRange=IfLenOutOfRange(SHlist[i].strName);
				if (bJudeRange){
					system("cls");
					ChangeInformation();
				}
				cout << "�������Ա�";
				cin >> SHlist[i].strSex;
				bJudeRange=IfLenOutOfRange(SHlist[i].strSex);
				if (bJudeRange){
					system("cls");
					ChangeInformation();
				}
				cout << "������ѧ�ţ�";
				cin >> SHlist[i].strStudentID;
				bJudeRange=IfLenOutOfRange(SHlist[i].strStudentID);
				if (bJudeRange){
					system("cls");
					ChangeInformation();
				}
				cout << "���������գ���ʽ�磺1998/10/8)��";
				cin >> SHlist[i].strBirthday;
				bJudeRange=IfLenOutOfRange(SHlist[i].strBirthday);
				if (bJudeRange){
					system("cls");
					ChangeInformation();
				}
				cout << "�����뽡��״��������������0�����������0�ַ�����";
				cin >> judeHealth;
				if (judeHealth == 0)
					strcpy_s(SHlist[i].IfHealthy, "��");
				else
					strcpy_s(SHlist[i].IfHealthy, "��");
				IfHaveID = true;
				Write();
				break;
			}
		}
		if (!IfHaveID)
			cout << "û����ѧ����" << endl;
		system("pause");
		Menu();
	}

	void ShowStudentInformation(){
		for (int i = 0; i < index; i++){
			cout << "���֣�" << SHlist[i].strName << endl;
			cout << "�Ա�" << SHlist[i].strSex << endl;
			cout << "ѧ�ţ�" << SHlist[i].strStudentID << endl;
			cout << "���գ�" << SHlist[i].strStudentID << endl;
			cout << "�Ƿ񽡿���" << SHlist[i].IfHealthy << endl;
			cout << endl << endl;
		}
		system("pause");
		Menu();
	}

	void FindStudent(){
		char ID[15];
		cout << "������ѧ����ѧ�ţ�";
		cin >> ID;
		bool IfHaveID = false;
		for (int i = 0; i < index; i++){
			if (strcmp(ID, SHlist[i].strStudentID) == 0){
				cout << "���֣�" << SHlist[i].strName << endl;
				cout << "�Ա�" << SHlist[i].strSex << endl;
				cout << "ѧ�ţ�" << SHlist[i].strStudentID << endl;
				cout << "���գ�" << SHlist[i].strStudentID << endl;
				cout << "�Ƿ񽡿���" << SHlist[i].IfHealthy << endl;
				cout << endl << endl;
				IfHaveID = true;
				break;
			}
		}
		if (!IfHaveID)
			cout << "û����ѧ����" << endl;
		system("pause");
		Menu();
	}

	void ShowInformationByID(){
		Student *newList = new Student[index];
		memmove(newList, SHlist, (sizeof(Student))*index);
		Quicksort(newList, 0, index - 1);
		for (int i = 0; i < index; i++){
			cout << "���֣�" << newList[i].strName << endl;
			cout << "�Ա�" << newList[i].strSex << endl;
			cout << "ѧ�ţ�" << newList[i].strStudentID << endl;
			cout << "���գ�" << newList[i].strStudentID << endl;
			cout << "�Ƿ񽡿���" << newList[i].IfHealthy << endl;
			cout << endl << endl;
		}
		delete[] newList;
		system("pause");
		Menu();
	}
};


#endif