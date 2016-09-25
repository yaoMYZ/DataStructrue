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
		   cout<<"字符过界，请重新输入！"<<endl;
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
		cout << "-----------------------------学生健康管理系统-----------------------------" << endl;
		cout << "                  按1新建学生健康表" << endl;
		cout << "                  按2向学生健康表添加新的学生信息" << endl;
		cout << "                  按3向学生健康表插入新的学生信息（按位置号来描述插入点）" << endl;
		cout << "                  按4在健康表删除指定学生的信息（按学号操作）" << endl;
		cout << "                  按5为某个学生修改身体状况信息（按学号操作）" << endl;
		cout << "                  按6按学生的学号排序并显示结果" << endl;
		cout << "                  按7在健康表中查询学生信息（按学生学号来进行查找）" << endl;
		cout << "                  按8在屏幕中输出全部学生信息" << endl;
		cout << "                  按9清屏" << endl;
		cout << "                  按0退出系统" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << endl << endl << endl << "请输入数字，以选择功能：";
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
			cout << "输入错误，请重新输入！";
			system("pause");
			Menu();
			break;
		}
	}

	void CreateHealthList(){
		cout << "请输入学生人数：";
		int number = 0;
		cin >> number;
		int judeHealth = 1;
		for (int i = 0; i < number; i++){
			bool bJudeRange=false;
			cout << "请输入姓名：";
			cin >> SHlist[i].strName;
			bJudeRange=IfLenOutOfRange(SHlist[i].strName);
			if (bJudeRange){
			   fflush(stdout);
			   system("cls");
			   i--;
			   continue;
			}
			cout << "请输入性别：";
			cin >> SHlist[i].strSex;
			bJudeRange=IfLenOutOfRange(SHlist[i].strSex);
			if (bJudeRange){
				fflush(stdout);
               system("cls");
			   i--;
			   continue;
			}
			cout << "请输入学号：";
			cin >> SHlist[i].strStudentID;
			bJudeRange=IfLenOutOfRange(SHlist[i].strStudentID);
			if (bJudeRange){
				fflush(stdout);
               system("cls");
			   i--;
			   continue;
			}
			cout << "请输入生日（格式如：1998/10/8)：";
			cin >> SHlist[i].strBirthday;
			bJudeRange=IfLenOutOfRange(SHlist[i].strBirthday);
			if (bJudeRange){
			   fflush(stdout);
			   system("cls");
			   i--;
			   continue;
			}
			cout << "请输入健康状况（不健康输入0，健康输入非0字符）：";
			cin >> judeHealth;
			if (judeHealth == 0)
				strcpy_s(SHlist[i].IfHealthy, "否");
			else
				strcpy_s(SHlist[i].IfHealthy, "是");
			index++;
			cout << endl;
		}
		Write();
		cout << "输入结束！" << endl;
		system("pause");
		Menu();
	}


	void AddStudent(){
		JudeIfOverflow();//Jude data overflow
		bool bJudeRange=false;
		int judeHealth = 1;
		cout << "请输入姓名：";
		cin >> SHlist[index].strName;
		bJudeRange=IfLenOutOfRange(SHlist[index].strName);
		if (bJudeRange){
		   system("cls");
		   AddStudent();
		}
		cout << "请输入性别：";
		cin >> SHlist[index].strSex;
		bJudeRange=IfLenOutOfRange(SHlist[index].strSex);
		if (bJudeRange){
		   system("cls");
		   AddStudent();
		}
		cout << "请输入学号：";
		cin >> SHlist[index].strStudentID;
		bJudeRange=IfLenOutOfRange(SHlist[index].strStudentID);
		if (bJudeRange){
		   system("cls");
		   AddStudent();
		}
		cout << "请输入生日（格式如：1998/10/8)：";
		cin >> SHlist[index].strBirthday;
		bJudeRange=IfLenOutOfRange(SHlist[index].strBirthday);
		if (bJudeRange){
		   system("cls");
		   AddStudent();
		}
		cout << "请输入健康状况（不健康输入0，健康输入非0字符）：";
		cin >> judeHealth;
		if (judeHealth == 0)
			strcpy_s(SHlist[index].IfHealthy, "否");
		else
			strcpy_s(SHlist[index].IfHealthy, "是");
		index++;
		Write();
		system("pause");
		Menu();
	}

	void InsertStudent(){
		JudeIfOverflow();//Jude data overflow
		int pos = 0;
		cout << "请输入插入位置（输入0插入到第一个位置，以此类推）：";
		cin >> pos;
		if (pos > index){
			cout << "超过界限请重新输入！";
			InsertStudent();
		}
		for (int i = index - 1; i >= pos; i--){//all elements after the index of pos move backward one byte
			SHlist[i + 1] = SHlist[i];
		}
		index++;

		bool bJudeRange=false;
		int judeHealth = 1;
		cout << "请输入姓名：";
		cin >> SHlist[pos].strName;
		bJudeRange=IfLenOutOfRange(SHlist[pos].strName);
		if (bJudeRange){
		   system("cls");
		   InsertStudent();
		}
		cout << "请输入性别：";
		cin >> SHlist[pos].strSex;
		bJudeRange=IfLenOutOfRange(SHlist[pos].strSex);
		if (bJudeRange){
		   system("cls");
		   InsertStudent();
		}
		cout << "请输入学号：";
		cin >> SHlist[pos].strStudentID;
		bJudeRange=IfLenOutOfRange(SHlist[pos].strStudentID);
		if (bJudeRange){
		   system("cls");
		   InsertStudent();
		}
		cout << "请输入生日（格式如：1998/10/8)：";
		cin >> SHlist[pos].strBirthday;
		bJudeRange=IfLenOutOfRange(SHlist[pos].strBirthday);
		if (bJudeRange){
		   system("cls");
		   InsertStudent();
		}
		cout << "请输入健康状况（不健康输入0，健康输入非0字符）：";
		cin >> judeHealth;
		if (judeHealth == 0)
			strcpy_s(SHlist[pos].IfHealthy, "否");
		else
			strcpy_s(SHlist[pos].IfHealthy, "是");
		Write();
		system("pause");
		Menu();
	}

	void DeleteStudent(){
		char ID[15];
		cout << "请输入学生的学号：";
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
			cout << "没有这学生！" << endl;
		system("pause");
		Menu();
	}

	void ChangeInformation(){
		char ID[15];
		cout << "请输入学生的学号：";
		cin >> ID;
		bool IfHaveID = false;
		for (int i = 0; i < index; i++){
			if (strcmp(ID, SHlist[i].strStudentID) == 0){
				bool bJudeRange=false;
				int judeHealth = 1;
				cout << "请输入姓名：";
				cin >> SHlist[i].strName;
				bJudeRange=IfLenOutOfRange(SHlist[i].strName);
				if (bJudeRange){
					system("cls");
					ChangeInformation();
				}
				cout << "请输入性别：";
				cin >> SHlist[i].strSex;
				bJudeRange=IfLenOutOfRange(SHlist[i].strSex);
				if (bJudeRange){
					system("cls");
					ChangeInformation();
				}
				cout << "请输入学号：";
				cin >> SHlist[i].strStudentID;
				bJudeRange=IfLenOutOfRange(SHlist[i].strStudentID);
				if (bJudeRange){
					system("cls");
					ChangeInformation();
				}
				cout << "请输入生日（格式如：1998/10/8)：";
				cin >> SHlist[i].strBirthday;
				bJudeRange=IfLenOutOfRange(SHlist[i].strBirthday);
				if (bJudeRange){
					system("cls");
					ChangeInformation();
				}
				cout << "请输入健康状况（不健康输入0，健康输入非0字符）：";
				cin >> judeHealth;
				if (judeHealth == 0)
					strcpy_s(SHlist[i].IfHealthy, "否");
				else
					strcpy_s(SHlist[i].IfHealthy, "是");
				IfHaveID = true;
				Write();
				break;
			}
		}
		if (!IfHaveID)
			cout << "没有这学生！" << endl;
		system("pause");
		Menu();
	}

	void ShowStudentInformation(){
		for (int i = 0; i < index; i++){
			cout << "名字：" << SHlist[i].strName << endl;
			cout << "性别：" << SHlist[i].strSex << endl;
			cout << "学号：" << SHlist[i].strStudentID << endl;
			cout << "生日：" << SHlist[i].strStudentID << endl;
			cout << "是否健康：" << SHlist[i].IfHealthy << endl;
			cout << endl << endl;
		}
		system("pause");
		Menu();
	}

	void FindStudent(){
		char ID[15];
		cout << "请输入学生的学号：";
		cin >> ID;
		bool IfHaveID = false;
		for (int i = 0; i < index; i++){
			if (strcmp(ID, SHlist[i].strStudentID) == 0){
				cout << "名字：" << SHlist[i].strName << endl;
				cout << "性别：" << SHlist[i].strSex << endl;
				cout << "学号：" << SHlist[i].strStudentID << endl;
				cout << "生日：" << SHlist[i].strStudentID << endl;
				cout << "是否健康：" << SHlist[i].IfHealthy << endl;
				cout << endl << endl;
				IfHaveID = true;
				break;
			}
		}
		if (!IfHaveID)
			cout << "没有这学生！" << endl;
		system("pause");
		Menu();
	}

	void ShowInformationByID(){
		Student *newList = new Student[index];
		memmove(newList, SHlist, (sizeof(Student))*index);
		Quicksort(newList, 0, index - 1);
		for (int i = 0; i < index; i++){
			cout << "名字：" << newList[i].strName << endl;
			cout << "性别：" << newList[i].strSex << endl;
			cout << "学号：" << newList[i].strStudentID << endl;
			cout << "生日：" << newList[i].strStudentID << endl;
			cout << "是否健康：" << newList[i].IfHealthy << endl;
			cout << endl << endl;
		}
		delete[] newList;
		system("pause");
		Menu();
	}
};


#endif