#ifndef LIST
#define LIST

#include<iostream>
using namespace std;

template<class T>
struct ListNode
{
	T m_Member;
	ListNode<T>*m_Next=NULL;
};


template <class T>
class CycleList
{
private:

	ListNode<T>*m_Tail;

public:
	CycleList(){
		m_Tail = NULL;
	}
	~CycleList(){
		Clear();
	}

	void Push(T);
	void Show();
	bool Pop();
	bool Reverse();
	int Length();
	bool IsEmpty();
	void Clear();
	bool DeleteMin();
};


template <class T>//ģ����������Ͷ���һ��Ҫ��ͬһ�ļ���
void CycleList<T>::Push(T member)
{
	ListNode<T> *newNode = new ListNode<T>;
	newNode->m_Member = member;
	if (m_Tail == NULL){
		m_Tail = newNode;
		m_Tail->m_Next = m_Tail;
	}
	else{
		newNode->m_Next = m_Tail->m_Next;
		m_Tail->m_Next = newNode;
		m_Tail = newNode;
	}
}


template <class T>//ģ����������Ͷ���һ��Ҫ��ͬһ�ļ���
void CycleList<T>::Show(){
	ListNode<T>*p;
	p = m_Tail->m_Next;
	while (p != m_Tail){
		cout << p->m_Member << " ";
		p = p->m_Next;
	} 
	cout << p->m_Member;
	cout << endl;
}



template <class T>//ģ����������Ͷ���һ��Ҫ��ͬһ�ļ���
bool CycleList<T>::Pop(){
	if (IsEmpty()){
		cout << "The list is empty!"��
		return false;
	}
	ListNode<T>*pop, tail;
	pop = m_Tail->m_Next;
	m_Tail->m_Next = pop->m_Next;
	delete pop;
	pop = NULL;
	return true;
}



template <class T>//ģ����������Ͷ���һ��Ҫ��ͬһ�ļ���  
bool CycleList<T>::Reverse(){
	if (IsEmpty()){
		cout << "The list is empty!";
		return false;
	}
	ListNode<T> *newList, *p,*newTail;
	newList = m_Tail->m_Next;
	newTail = m_Tail->m_Next;
	p = newList->m_Next;
	while (p != m_Tail){
		ListNode<T>*temp = p;
		p = p->m_Next;
		temp->m_Next = newList;
		newList = temp;
	}
	//�������һ���ڵ��γ�ѭ������
	m_Tail->m_Next = newList;
	newTail->m_Next = m_Tail;
	m_Tail = newTail;
	return true;
}




template <class T>//ģ����������Ͷ���һ��Ҫ��ͬһ�ļ���
int CycleList<T>::Length(){
	int len = 0;
	ListNode<T>*p = m_Tail;
	while (p!= m_Tail){
		len++;
		p = p->m_Next;
	}
	return len;
}

template<class T>
bool CycleList<T>::IsEmpty(){
	if (m_Tail == NULL)
		return true;
	else
		return false;
}




template<class T>
void CycleList<T>::Clear(){
	ListNode<T>*p = m_Tail->m_Next;
	while (p != m_Tail){
		ListNode<T> *del = p;
		p = p->m_Next;
		delete del;
	}
	//���ɾ����β
	delete m_Tail;
	m_Tail = NULL;
}

template<class T>
bool CycleList<T>::DeleteMin(){
	if (IsEmpty()){
		cout << "The list is empty!";
			return false;
	}
	ListNode<T> *min = m_Tail->m_Next;
	ListNode<T> *p = m_Tail;
	do{
		if (p->m_Next->m_Member < min->m_Member)
			min = p;
		p = p->m_Next;
	} while (p != m_Tail);
	//ɾ���ڵ�
	ListNode<T>* del = min->m_Next;
	min->m_Next = del->m_Next;
	//ɾ���ڵ�ǡΪ��βʱ
	if (del == m_Tail){
		m_Tail = min;
	}
	delete del;
	return true;
}
#endif