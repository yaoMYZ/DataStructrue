#ifndef STACK
#define STACK
#include<stdlib.h>
template<class T>
struct StackNode
{
	T Member;
	StackNode<T> *Next=NULL;
};

template<class T>
class Stack
{
private:
	int Length;
	StackNode<T> *top;

public:
	Stack(){
		Length = 0;
		top = NULL;
	}

	void Push(T member);
	T Pop();
	void Print();
	void Clear();
	T GetTop();
};

template<class T>
void Stack<T>::Push(T member){
	//create new node
	StackNode<T> *newNode = new StackNode<T>;
	newNode->Member = member;
	//add new node
	newNode->Next = top;
	top = newNode;

	Length++;
}

template < class T>
T Stack<T>::Pop(){
	if (Length == 0){
		cout << "The stack is empty!" << endl;
		exit(0);
	}
	//get the data
	T temp = top->Member;
	StackNode<T> *del = top;
	top = top->Next;
   //delete the node
	delete del;
	return temp;
}

template<class T>
void Stack<T>::Print(){
	StackNode<T> *p = top;

	while (p != NULL){
		cout << p->Member << endl;
		p = p->Next;
	}
}

template<class T>
void Stack<T>::Clear(){
	while (top != NULL){
		StackNode<T> *del = top;
		top = top->Next;
		delete del;
	}
	Length = 0;
}


template<class T>
T Stack<T>::GetTop(){
	if (Length == NULL){
		cout << "There is no elements in the stack!" << endl;
		exit(0);
	}
	return top->Member;
}

#endif