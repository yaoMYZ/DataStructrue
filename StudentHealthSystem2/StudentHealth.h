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
	cout << "名字：" << st.strName << endl;
	cout << "性别：" << st.strSex << endl;
	cout << "学号：" << st.strStudentID << endl;
	cout << "生日：" << st.strBirthday << endl;
	cout << "健康程度：" << st.Healthy << endl;
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
	cout << "请输入健康状况（优输入1，良输入2，差输入其他数字）：";
	input >> judeHealth;
	if (judeHealth == 1)
		strcpy_s(st.Healthy, "优");
	else if (judeHealth == 2)
		strcpy_s(st.Healthy, "良");
	else
		strcpy_s(st.Healthy, "差");
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
			cout << "字符过界，请重新输入！" << endl;
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
		cout << "数据存入成功！" << endl;
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
		cout << "-----------------------------学生健康管理系统-----------------------------" << endl;
		cout << "                  按1新建学生健康表" << endl;
		cout << "                  按2向学生健康表添加新的学生信息" << endl;
		cout << "                  按3在健康表删除指定学生的信息（按学号操作）" << endl;
		cout << "                  按4为某个学生修改身体状况信息（按学号操作）" << endl;
		cout << "                  按5按学生的学号排序并显示结果" << endl;
		cout << "                  按6在健康表中查询学生信息（按学生学号来进行查找）" << endl;
		cout << "                  按7在屏幕中输出全部学生信息" << endl;
		cout << "                  按8清屏" << endl;
		cout << "                  按9把数据存入文件中" << endl;
		cout << "                  按0把数据存入文件中退出系统" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << endl << endl << endl << "请输入数字，以选择功能：";
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
			cout << "输入错误，请重新输入！";
			system("pause");
			Menu();
			break;
		}
	}

	void CreateHealthNumberTree(){
		//clear the NumberTree
		STree.clear();
		Length = 0;
		cout << "请输入学生人数：";
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
			cout << "已存在该学号学生，请重新输入！" << endl;
			AddStudent();
		}
		STree.insert(temp,temp.strStudentID);
		Length++;
		cout << "恭喜添加成功！" << endl;
	}


	void DeleteStudent(){
		char ID[15];
		cout << "请输入学生的学号：";
		cin >> ID;
		if (!STree.hasMember(ID)){
			cout << "没有此学生，请重新输入！" << endl;
			DeleteStudent();
		}
		else{
			STree.remove(ID);
		}
		cout << "删除成功！" << endl;
	}

	void ChangeInformation(){
		char ID[15];
		cout << "请输入学生的学号：";
		cin >> ID;
		if (!STree.hasMember(ID)){
			cout << "没有此学生，请重新输入！" << endl;
			ChangeInformation();
		}
		else{
			Student temp;
			cin >> temp;
			STree.insert(temp, temp.strStudentID);
		}
		cout << "学生信息修改成功！" << endl;
	}

	void ShowStudentInformation(){
		STree.inOrder(Visit);
	}

	void FindStudent(){
		char ID[15];
		cout << "请输入学生的学号：";
		cin >> ID;
		if (!STree.hasMember(ID)){
			cout << "没有这学生，请重新输入！" << endl;
			FindStudent();
		}
		cout << STree.getMember(ID);
	}

	void ShowInformationByID(){
		STree.layerOrder(Visit);
	}
};


#endif