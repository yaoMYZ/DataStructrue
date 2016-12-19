#ifndef LIST
#define LIST

#include<iostream>
using namespace std;

template<class T>
struct ListNode
{
	T m_Member;
	ListNode<T> *m_Right = NULL;
	ListNode<T> *m_Left = NULL;
};


template <class T>
class CycleList
{
private:

	ListNode<T>*m_Head;
	ListNode<T>*m_Tail;

public:
	CycleList(){
		m_Head = new ListNode<T>;
		m_Tail = m_Head;

	}


	void Push(T);
	void Show();
	void Pop();
	void Reverse();
	bool Insert(int, T);
	bool Delete(int pos);
	int Length();
	bool IsEmpty();
	T &Member(int pos);
	bool Replace(int pos, T member);
	void Clear();
};


template <class T>//模板类的声明和定义一定要在同一文件中
void CycleList<T>::Push(T member)
{
	ListNode<T>*tail, *temp;
	temp = new ListNode<T>;
	temp->m_Member = member;

	tail = m_Head;
	while (tail->m_Right != NULL)
		tail = tail->m_Right;
	tail->m_Right = temp;
	temp->m_Left = tail;

	m_Tail = temp;
}


template <class T>//模板类的声明和定义一定要在同一文件中
void CycleList<T>::Show(){
	ListNode<T>*p;
	p = m_Head->m_Right;
	while (p != NULL){
		cout << p->m_Member << " ";
		p = p->m_Right;
	}
	cout << endl;
}



template <class T>//模板类的声明和定义一定要在同一文件中
void CycleList<T>::Pop(){
	ListNode<T>*pop, tail;
	pop = m_Tail;
	tail = pop->m_Left;
	delete pop;
	pop = NULL;
	tail->m_Right = NULL;
}



template <class T>//模板类的声明和定义一定要在同一文件中  
void CycleList<T>::Reverse(){
	ListNode<T>*now, *p, *temp;
	now = m_Head->m_Right;
	p = now->m_Right;
	now->m_Right = NULL;
	m_Tail = now;//the end of list is now the first one of the list
	while (p != NULL){
		temp = p;
		p = p->m_Right;
		temp->m_Right = now;
		now->m_Left = temp;
		now = temp;
	}
	m_Head->m_Right = now;
	now->m_Left = m_Head;

}



template <class T>//模板类的声明和定义一定要在同一文件中  
bool CycleList<T>::Insert(int number, T member){
	int len = Length();
	if (number<1 || number>len + 1) return false;

	ListNode<T>*newNode = new ListNode<T>;//create an new node
	newNode->m_Member = member;

	if (number == len + 1){//element insert in the end of the list
		m_Tail->m_Right = newNode;
		newNode->m_Left = m_Tail;
		m_Tail = newNode;
		m_Tail->m_Right = NULL;
		return true;
	}

	ListNode<T>*p = m_Head;

	int i = 1;
	while (i<number){
		p = p->m_Right;
		i++;
	}
	ListNode<T>*pRight = p->m_Right;

	p->m_Right = newNode;
	newNode->m_Left = p;

	if (pRight != NULL)
		pRight->m_Left = newNode;
	newNode->m_Right = pRight;

	return true;
}

template <class T>//模板类的声明和定义一定要在同一文件中
bool CycleList<T>::Delete(int pos){
	int len = Length();
	if (pos<1 || pos>len){
		cout << "输入超界！" << endl;
		return false;
	}

	ListNode<T>*del = NULL;
	if (pos == len){//when delete the final element in the list 
		del = m_Tail;
		m_Tail = del->m_Left;
		m_Tail->m_Right = NULL;
		delete del;
		return true;
	}

	ListNode<T>*p = m_Head;
	for (int i = 1; i < pos; i++){
		p = p->m_Right;
	}
	del = p->m_Right;
	p->m_Right = del->m_Right;
	del->m_Right->m_Left = p;
	delete del;
	return true;
}

template <class T>//模板类的声明和定义一定要在同一文件中
int CycleList<T>::Length(){
	int len = 0;
	ListNode<T>*p = m_Head;
	while (p->m_Right != NULL){
		p = p->m_Right;
		len++;
	}
	return len;
}

template<class T>
bool CycleList<T>::IsEmpty(){
	if (m_Head->m_Right == NULL)
		return true;
	else
		return false;
}

template<class T>
T & CycleList<T>::Member(int pos){
	if (pos > Length()) {
		cout << "out of range!" << endl;
		exit(0);
	}
	ListNode<T>*p = m_Head;
	for (int i = 0; i < pos; i++){
		p = p->m_Right;
	}
	return p->m_Member;
}

template<class T>
bool CycleList<T>::Replace(int pos, T member){
	int len = Length();
	if (pos<1 || pos>len){
		cout << "输入超界！" << endl;
		return false;
	}

	Member(pos) = member;
	return true;
}

template<class T>
void CycleList<T>::Clear(){
	ListNode<T>*p = m_Head->m_Right;
	while (p != NULL){
		ListNode<T> *del = p;
		p = p->m_Right;
		delete del;
	}
	m_Tail = m_Head;
	m_Tail->m_Right = NULL;
}
#endif