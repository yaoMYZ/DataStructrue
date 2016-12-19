#ifndef LIST
#define LIST

#include<iostream>
using namespace std;

template<class T>
struct  ListNode
{
	T m_Member;
	ListNode<T> *Next = NULL;
};

template <class T>
class List
{
private:
	ListNode<T> *m_Head;
	ListNode<T> *m_Tail;
	int len;
public:
	List(){
		m_Head = new ListNode<T>;
		m_Tail = m_Head;
		len = 0;
	}


	void Push(T);
	void Show();
	bool Reverse();
	bool Insert(int, T);
	bool Delete(int pos);
	bool Remove(T);
	int Length();
	bool IsEmpty();
	T &Member(int pos);
	bool Replace(int pos, T member);
};


template <class T>//模板类的声明和定义一定要在同一文件中
void List<T>::Push(T member)
{
	ListNode<T> *temp;
	temp = new ListNode<T>;
	temp->m_Member = member;
	
	m_Tail->Next = temp;
	m_Tail = temp;

	len++;
}


template <class T>//模板类的声明和定义一定要在同一文件中
void List<T>::Show(){
	ListNode<T> *p;
	p = m_Head->Next;
	while (p != NULL){
		cout << p->m_Member << " ";
		p = p->Next;
	}
	cout << endl;
}



template <class T>//模板类的声明和定义一定要在同一文件中  
bool List<T>::Reverse(){
	if (len < 2){
		cout << "There are not enough elements" << endl;
		return false;
	}

	ListNode<T> *now, *p, *temp;
	now = m_Head->Next;
	p = now->Next;
	now->Next =NULL;//reset the final element's Next

	while (p != NULL){
		temp = p;
		p = p->Next;
		//tail insert
		temp->Next = now;
		now = temp;
	}
	m_Head->Next = now;

	return true;
}



template <class T>//模板类的声明和定义一定要在同一文件中  
bool List<T>::Insert(int number, T member){
	if (number<1 || number>len + 1) return false;

	ListNode<T> *newNode = new ListNode<T>;//create an new node
	newNode->m_Member = member;

	ListNode<T> *p = m_Head;

	int i = 1;
	while (i<number){
		p = p->Next;
		i++;
	}
   
	//insert the newNode
	newNode->Next = p->Next;
	p->Next = newNode;

	len++;
	return true;
}

template <class T>//模板类的声明和定义一定要在同一文件中
bool List<T>::Delete(int pos){
	if (pos<1 || pos>len){
		cout << "输入超界！" << endl;
		return false;
	}

	ListNode<T> *del = NULL;

	//search the element before the element that have to be deleted
	ListNode<T> *p = m_Head;
	for (int i = 1; i < pos; i++){
		p = p->Next;
	}

	del = p->Next;
	p->Next = del->Next;
	delete del;

	len--;
	return true;
}

template <class T>//模板类的声明和定义一定要在同一文件中
bool List<T>::Remove(T member){
	bool JudeExit = false;
	ListNode<T>* p = m_Head;
	while (p->Next!=NULL){
		if (p->Next->m_Member == member){
			ListNode<T>* del = p->Next;
			p->Next = del->Next;
			delete del;

			JudeExit = true;
			Length--;
			continue;
		}
		p = p->Next;
	}

	if (JudeExit)
		return true;
	else
		return false;
}

template <class T>//模板类的声明和定义一定要在同一文件中
int List<T>::Length(){
	return len;
}

template<class T>
bool List<T>::IsEmpty(){
	if (m_Head->Next == NULL)
		return true;
	else
		return false;
}

template<class T>
T & List<T>::Member(int pos){
	if (pos > len) {
		cout << "out of range!" << endl;
		exit(0);
	}
	ListNode<T> *p = m_Head;
	for (int i = 0; i < pos; i++){
		p = p->Next;
	}
	return p->m_Member;
}

template<class T>
bool List<T>::Replace(int pos, T member){
	if (pos<1 || pos>len){
		cout << "输入超界！" << endl;
		return false;
	}

	Member(pos) = member;
	return true;
}
#endif