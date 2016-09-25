#ifndef LIST
#define LIST

#include<iostream>
using namespace std;

template <class T> 
class List
{
private:
	T m_Member;
	List *m_Head;
	List *m_Tail;
	List *m_Right;
	List *m_Left;

public:
	List(){
		m_Head = NULL;
		m_Tail = NULL;
		m_Right = NULL;
		m_Left = NULL;
	}

	void Push(T);
	void Show();
	void Pop();
	void Reverse();
	void Insert(int,T);
};


template <class T>//模板类的声明和定义一定要在同一文件中
void List<T>::Push(T member)
{
	List *tail, *temp;
	temp = new List;
	temp->m_Member = member;
	if (m_Head == NULL){
		List *head = new List;
		head->m_Member = (T)0;
		m_Head = head;

	}
	tail = m_Head;
	while (tail->m_Right != NULL)
		tail = tail->m_Right;
	tail->m_Right = temp;
	temp->m_Left = tail;

	m_Tail = temp;
}



template <class T>//模板类的声明和定义一定要在同一文件中
void List<T>::Show(){
	List *p;
	p = m_Head->m_Right;
	while (p != NULL){
		cout << p->m_Member << " ";
		p = p->m_Right;
	}
	cout << endl;
}



template <class T>//模板类的声明和定义一定要在同一文件中
void List<T>::Pop(){
	List *pop,tail;
	pop = m_Tail;
	tail = pop->m_Left;
	delete pop;
	pop = NULL;
	tail->m_Right = NULL;
}



template <class T>//模板类的声明和定义一定要在同一文件中  
void List<T>::Reverse(){
	List *now, *p,*temp;
	now = m_Head->m_Right;
	p = now->m_Right;
	now->m_Right = NULL;
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
void List<T>::Insert(int munber,T member){
	List *p = m_Head;
	
	int i = 0;
	while (i<munber){
		p = p->m_Right;
		i++;
	}
	List *pRight = p->m_Right;

	List *newNode = new List;
	newNode->m_Member = member;
	
	p->m_Right = newNode;
	newNode->m_Left = p;

	if (pRight!=NULL)
	pRight->m_Left = newNode;
	newNode->m_Right = pRight;
}


#endif