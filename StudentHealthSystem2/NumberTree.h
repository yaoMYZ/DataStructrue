#ifndef NUMBERTREE
#define NUMBERTREE

#define NumberMaxSize 100
#define ChildNumber       2
#include<string>
#include<iostream>
#include<queue>
#include<fstream>
using namespace std;

char* charToReverseBinary(char *a){
	int index = 0;
	int len = strlen(a);
	int number = 0;//�ַ�ת��������
	while (a[index] == 48&&index<len){//����ǰ���0������֤���鲻����
		index++;
	}
	try{
		if (index == len){//�ж��Ƿ�����һ������0
			throw "�������ֲ���Ϊ0";
		}
		for (int i = index; i < len; i++){
			if (a[i]<48 || a[i]>57){
				throw "�����ʽ����";
			}
			number = 10 * number + a[i] - 48;
		}
	}
	catch (string s){
		cout << s << endl;
	}
	

	char *ReverseBinary = new char[NumberMaxSize];//��¼��������
	int reg = 0;//��¼�±�
	//ת��
	while (number){
		if (number & 1)
			ReverseBinary[reg] = 49;
		else
			ReverseBinary[reg] = 48;
		reg++;
		number = number >> 1;
	}

	ReverseBinary[reg] = '\0';

	return ReverseBinary;
}





template<class T>
struct TreeNode{
	int tag;
	T member;
	TreeNode<T> *node[ChildNumber];

	TreeNode<T>(){
		int tag = 0;
		for (int i = 0; i < ChildNumber; i++){
			node[i] = NULL;
		}
	}
};


template<class T>
void Visit(TreeNode<T> *p){
	cout << p->member << " ";
}


template<class T>
void setDeletedSignal(TreeNode<T> *p){
	p->tag = -1;
}

template<class T>
class NumberTree
{
private:
	int NodeNumber ;
	TreeNode<T> *Root;
	void inOrder(TreeNode<T>*,void(*operation)(TreeNode<T> *));
public:
	NumberTree(){ 
	NodeNumber = 0;
	Root = NULL; }

	bool insert(T, char *);
	void inOrder(void(*operation)(TreeNode<T> *));
	void layerOrder(void(*operation)(TreeNode<T> *));
	void layerOrder(char *fileRout, unsigned size);
	bool remove(char *);
	T getMember(char *);
	bool hasMember(char *);
	void clear();
};

template<class T>
bool NumberTree<T>::insert(T member,char *a){
	char *ReverseNumber = charToReverseBinary(a);//ת��Ϊ�ߵ��Ķ�����
	int len = strlen(ReverseNumber);

	TreeNode<T> *currentNode = Root;
	if (len == 1){
		if (currentNode == NULL){
			Root = new TreeNode<T>;

		}
		Root->tag = 1;
		Root->member = member;

		NodeNumber++;
		return true;
	}
	//�ߵ���Ҫ�����Ľ��
	for (int i = len-2; i >=0; i--)
	{
		int index = ReverseNumber[i] - 48;
		if (currentNode->node[index] == NULL){
			currentNode->node[index] = new TreeNode<T>;
		}
		currentNode = currentNode->node[index];
	}
	//��㸳ֵ
	currentNode->tag = 1;
	currentNode->member = member;
	//����̬���ɵ��ַ�����
	delete[] ReverseNumber;
	ReverseNumber = NULL;

	NodeNumber++;
	return true;
}


template<class T>
void NumberTree<T>::inOrder(void(*operation)(TreeNode<T>*p)){
	inOrder(Root, operation);
}


template<class T>
void NumberTree<T>::inOrder(TreeNode<T>*subTree, void(*operation)(TreeNode<T>*p)){
	if (subTree != NULL){
		inOrder(subTree->node[0], operation);
		if (subTree->tag == 1)
			operation(subTree);
		inOrder(subTree->node[1], operation);
	}
}


template<class T>
void NumberTree<T>::layerOrder(void(*operation)(TreeNode<T> *)){
	queue<TreeNode<T>*> q;
	q.push(Root);
	TreeNode<T> *cunrrentNode;
	while (!q.empty()){
		cunrrentNode =  q.front();
		q.pop();
		if (cunrrentNode->tag==1)
		operation(cunrrentNode);
		for (int i = 0; i < ChildNumber; i++){
			if (cunrrentNode->node[i]!=NULL)
			q.push(cunrrentNode->node[i]);
		}
	}
}


template<class T>
void NumberTree<T>::layerOrder(char *rout, unsigned size){
	queue<TreeNode<T>*> q;
	q.push(Root);
	TreeNode<T> *cunrrentNode;
	ofstream Write(rout, ios::binary | ios::out);
	while (!q.empty()){
		cunrrentNode = q.front();
		q.pop();
		if (cunrrentNode->tag == 1)
			Write.write((char*)&cunrrentNode->member,size);
		for (int i = 0; i < ChildNumber; i++){
			if (cunrrentNode->node[i] != NULL)
				q.push(cunrrentNode->node[i]);
		}
	}
	Write.close();
}

template<class T>
bool NumberTree<T>::remove(char *a){
	if (NodeNumber <= 0  ){
		return false;
	}

	char *ReverseNumber = charToReverseBinary(a);//ת��Ϊ�ߵ��Ķ�����
	int len = strlen(ReverseNumber);

	TreeNode<T> *currentNode = Root;
	for (int i = len - 2; i>=0; i--){
		int index = ReverseNumber[i] - 48;
		if (currentNode->node[index] == NULL){
			return false;
		}
		currentNode = currentNode->node[index];
	}
	currentNode->tag = -1;//tag ����ɾ����־

	//����̬���ɵ��ַ�����
	delete[] ReverseNumber;
	ReverseNumber = NULL;

	NodeNumber--;
	return true;
}


template<class T>
T NumberTree<T>::getMember(char *a){
	try{
		if (!hasMember(a))
			throw "�޴���Ϣ���";
	}
	catch (string s){
		cout << s << endl;
	}

	char *ReverseNumber = charToReverseBinary(a);//ת��Ϊ�ߵ��Ķ�����
	int len = strlen(ReverseNumber);

	TreeNode<T> *currentNode = Root;
	for (int i = len - 2; i >= 0; i--){
		int index = ReverseNumber[i] - 48;
		currentNode = currentNode->node[index];
	}

	//����̬���ɵ��ַ�����
	delete[] ReverseNumber;
	ReverseNumber = NULL;

    return currentNode->member;

}

template<class T>
bool NumberTree<T>::hasMember(char *a){
	if (NodeNumber <= 0){
		return false;
	}

	char *ReverseNumber = charToReverseBinary(a);//ת��Ϊ�ߵ��Ķ�����
	int len = strlen(ReverseNumber);

	TreeNode<T> *currentNode = Root;
	for (int i = len - 2; i >= 0; i--){
		int index = ReverseNumber[i] - 48;
		if (currentNode->node[index] == NULL){
			return false;
		}
		currentNode = currentNode->node[index];
	}

	//����̬���ɵ��ַ�����
	delete[] ReverseNumber;
	ReverseNumber = NULL;

	if (currentNode->tag == 1)
		return true;
	else
		return false;
}


template<class T>
void NumberTree<T>::clear(){
	inOrder(setDeletedSignal);
}
#endif