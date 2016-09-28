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
	char IfHealthy[5];

	Student(){
		strcpy_s(strName, "0");
		strcpy_s(strSex, "0");
		strcpy_s(strStudentID, "0");
		strcpy_s(strBirthday, "0");
		strcpy_s(IfHealthy, "0");
	}
	Student & operator=(Student other){
		strcpy_s(strName, other.strName);
		strcpy_s(strSex, other.strSex);
		strcpy_s(strStudentID, other.strStudentID);
		strcpy_s(strBirthday, other.strBirthday);
		strcpy_s(IfHealthy, other.IfHealthy);
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
	cout << "名字：" << st.strName << endl;
	cout << "性别：" << st.strSex << endl;
	cout << "学号：" << st.strStudentID << endl;
	cout << "生日：" << st.strBirthday << endl;
	cout << "是否健康：" << st.IfHealthy << endl;
	cout << endl << endl;
	return output;
}

istream & operator>>(istream & input, Student &st){//st must pass address
	int judeHealth = 1;
	cout << "请输入姓名：";
	input >> st.strName;
	cout << "请输入性别：";
	input >> st.strSex;
	cout << "请输入学号：";
	input >> st.strStudentID;
	cout << "请输入生日（格式如：1998/10/8)：";
	input >> st.strBirthday;
	cout << "请输入健康状况（不健康输入0，健康输入非0字符）：";
	input >> judeHealth;
	if (judeHealth == 0)
		strcpy_s(st.IfHealthy, "否");
	else
		strcpy_s(st.IfHealthy, "是");
	cout << endl;
	return input;
}


class StudentHealth{
private:
	List<Student> SHlist;
	int Length;
	//void JudeIfOverflow(){
	//	if (Length >= MaxSize){//Jude data overflow
	//		Student *newList = new Student[MaxSize * 2];//To apply for a bigger array
	//		memmove(newList, SHlist, sizeof(Student)*MaxSize);
	//		MaxSize *= 2;
	//		delete[] SHlist;
	//		SHlist = newList;//variable SHlist point to the variable newList
	//	}
	//}

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
		for (int i = 0; i < number; i++){
			Student temp;
			cin >> temp;
			SHlist.Push(temp);
			Length++;
		}
		Write();
		cout << "输入结束！" << endl;
		system("pause");
		Menu();
	}


	void AddStudent(){
		Student temp;
		cin >> temp;
		SHlist.Push(temp);
		Length++;
		Write();
		system("pause");
		Menu();
	}

	void InsertStudent(){
		int pos = 0;
		cout << "请输入插入位置（输入1插入到第一个位置，以此类推）：";
		cin >> pos;
		if (pos > Length+1||pos<1){
			cout << "超过界限请重新输入！";
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
		cout << "请输入学生的学号：";
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
			cout << "没有这学生，请重新输入！" << endl;
			DeleteStudent();
		}			
		system("pause");
		Menu();
	}

	void ChangeInformation(){
		char ID[15];
		cout << "请输入学生的学号：";
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
			cout << "没有这学生，请重新输入！" << endl;
			ChangeInformation();
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
		cout << "请输入学生的学号：";
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
			cout << "没有这学生，请重新输入！" << endl;
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