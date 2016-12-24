#ifndef QUEUE
#define QUEUE

#include<iostream>
using namespace std;

template<class T>
struct  QueueNode
{
	T m_Member;
	QueueNode<T> *Next = NULL;
};

template <class T>
class Queue
{
private:
	QueueNode<T> *m_Head;
	QueueNode<T> *m_Tail;
	int len;
public:
	Queue(){
		m_Head = new QueueNode<T>;
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
	T Top();
	bool Pop();
};


template <class T>//模板类的声明和定义一定要在同一文件中
void Queue<T>::Push(T member)
{
	QueueNode<T> *temp;
	temp = new QueueNode<T>;
	temp->m_Member = member;

	m_Tail->Next = temp;
	m_Tail = temp;

	len++;
}


template <class T>//模板类的声明和定义一定要在同一文件中
void Queue<T>::Show(){
	QueueNode<T> *p;
	p = m_Head->Next;
	while (p != NULL){
		cout << p->m_Member << " ";
		p = p->Next;
	}
	cout << endl;
}



template <class T>//模板类的声明和定义一定要在同一文件中  
bool Queue<T>::Reverse(){
	if (len < 2){
		cout << "There are not enough elements" << endl;
		return false;
	}

	QueueNode<T> *now, *p, *temp;
	now = m_Head->Next;
	p = now->Next;
	now->Next = NULL;//reset the final element's Next

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
bool Queue<T>::Insert(int number, T member){
	if (number<1 || number>len + 1) return false;

	QueueNode<T> *newNode = new QueueNode<T>;//create an new node
	newNode->m_Member = member;
	//插入到队列尾部时
	if (number == len){
		m_Tail->Next = newNode;
		m_Tail = newNode;
		return;
	}

	QueueNode<T> *p = m_Head;

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
bool Queue<T>::Delete(int pos){
	if (pos<1 || pos>len){
		cout << "输入超界！" << endl;
		return false;
	}
	if (IsEmpty()){
		cout << "队列为空！" << endl;
		return false;
	}

	QueueNode<T> *del = NULL;

	//search the element before the element that have to be deleted
	QueueNode<T> *p = m_Head;
	for (int i = 1; i < pos; i++){
		p = p->Next;
	}

	del = p->Next;
	p->Next = del->Next;
	delete del;
	//队列为空时
	if (IsEmpty()){
		m_Tail = m_Head;
	}

	len--;
	return true;
}

template <class T>//模板类的声明和定义一定要在同一文件中
bool Queue<T>::Remove(T member){
	if (IsEmpty()){
		cout << "队列为空！" << endl;
		return false;
	}

	bool JudeExit = false;
	QueueNode<T>* p = m_Head;
	while (p->Next != NULL){
		if (p->Next->m_Member == member){
			QueueNode<T>* del = p->Next;
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
int Queue<T>::Length(){
	return len;
}

template<class T>
bool Queue<T>::IsEmpty(){
	if (m_Head->Next == NULL)
		return true;
	else
		return false;
}

template<class T>
T & Queue<T>::Member(int pos){
	if (pos > len) {
		cout << "out of range!" << endl;
		exit(0);
	}
	QueueNode<T> *p = m_Head;
	for (int i = 0; i < pos; i++){
		p = p->Next;
	}
	return p->m_Member;
}

template<class T>
bool Queue<T>::Replace(int pos, T member){
	if (pos<1 || pos>len){
		cout << "输入超界！" << endl;
		return false;
	}

	Member(pos) = member;
	return true;
}

template<class T>
T Queue<T>::Top(){
	try{
		if (IsEmpty())
			throw "队列为空！";
	}
	catch (char *a){
		cout << a << endl;
	}
	return m_Head->Next->m_Member;
}

template<class T>
bool Queue<T>::Pop(){
	return Delete(1);
}
#endif