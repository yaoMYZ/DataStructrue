#ifndef TREE
#define TREE

#include<iostream>
#include"Stack.h"
using namespace std;

#define StackMaxSize 100

template<class T>
struct Node{
	T m_Member;
	Node *m_Left = NULL;
	Node *m_Right = NULL;
};

template<class T>
void Visit(Node<T> *p){
	cout << p->m_Member << " ";
}

template<class T>
class BinaryTree{
private:
	Node<T> *Root;
	void Insert(Node<T>**, T);
	int Delete(Node<T> **, T);
	int Depth(Node<T> **);
	void Clear(Node<T> **);
	void preOrder(Node<T> *, void(*operation)(Node<T>*p));
	void inOrder(Node<T> *, void(*operation)(Node<T>*p));
	void postOrder(Node<T> *, void(*operation)(Node<T>*p));

public:
	BinaryTree(){
		Root = NULL;
	}
	~BinaryTree(){

	}
	void Insert(T);//insert a node
	T* Find(T);//find nodes by value
	int Update(T);//update a node'information by value
	int Delete(T);//delete a node
	int Depth();//get the depth of the tree
	void Clear();//clear the tree
	void preOrder(void(*operation)(Node<T>*p));//traverse the tree by preorder with recursion
	void inOrder(void(*operation)(Node<T>*p));//traverse the tree by inorder with recursion
	void postOrder(void(*operation)(Node<T>*p));//traverse the tree by postorder with recursion
	void preOrderNoRecur(void(*operation)(Node<T>*p));//traverse the tree by preorder without recursion
	//void inOrderNoRecur(void(*operation)(Node<T>*p));//traverse the tree by inorder without recursion
	//void postOrderNoRecur(void(*operation)(Node<T>*p));//traverse the tree by postorder without recusion

};



template<class T>
void BinaryTree<T>::Insert(Node<T> **tree, T a)//为使指针进行地址传递需使用指向指针的指针
{

	if (*tree == NULL){
		Node<T> *p = new Node<T>;
		p->m_Member = a;
		*tree = p;
	}
	else{
		if ((*tree)->m_Member<a){
			Insert(&((*tree)->m_Right), a);
		}
		else{
			Insert(&((*tree)->m_Left), a);
		}
	}
}

template<class T>
void BinaryTree<T>::Insert(T a)
{
	Insert(&Root, a);
}

template<class T>
T*  BinaryTree<T>::Find(T a)
{
	Node<T> *tree = Root;
	while (tree != NULL){
		if (tree->m_Member == a)
			return &(tree->m_Member);
		if (tree->m_Member < a)
			tree = tree->m_Right;
		else
			tree = tree->m_Left;
	}
	cout << "No this element." << endl;
	return NULL:
}


template<class T>
int BinaryTree<T>::Update(T a)
{
	Node<T> *tree = Root;
	while (tree != NULL){
		if (tree->m_Member == a){
			cout << "Please input the new element." << endl;
			T Put;
			cin >> Put;
			tree->m_Member = Put;
			return 1;
		}
		if (tree->m_Member < a)
			tree = tree->m_Right;
		else
			tree = tree->m_Left;
	}
	return 0;
}

template<class T>
int BinaryTree<T>::Delete(Node<T> **tree, T a)
{
	Node<T> *p = *tree;
	if (*tree == NULL)
		return 0;
	if ((*tree)->m_Member > a)
		return Delete(&((*tree)->m_Left), a);
	if ((*tree)->m_Member < a)
		return Delete(&((*tree)->m_Right), a);
	if ((*tree)->m_Left == NULL){
		*tree = (*tree)->m_Right;
		delete p;
		return 1;
	}
	else if ((*tree)->m_Right == NULL)	{
		*tree = (*tree)->m_Left;
		delete p;
		return 1;
	}
	else{
		if ((*tree)->m_Left->m_Right == NULL){
			(*tree)->m_Member = (*tree)->m_Left->m_Member;
			return Delete(&((*tree)->m_Left), (*tree)->m_Member);
		}
		else{
			Node<T> *p2 = (*tree)->m_Left;
			while (p2->m_Right != NULL)
				p2 = p2->m_Right;
			(*tree)->m_Member = p2->m_Member;
			return Delete(&(p2), p2->m_Member);
		}
	}
	return 0;
}

template<class T>
int BinaryTree<T>::Delete(T a)
{
	return Delete(&Root, a);
}

template<class T>
int BinaryTree<T>::Depth(Node<T> **tree)
{
	if (*tree == NULL)
		return 0;
	int temp1 = Depth(&((*tree)->m_Left));
	int temp2 = Depth(&((*tree)->m_Right));
	if (temp1 > temp2)
		return temp1 + 1;
	else
		return temp2 + 1;
}


template<class T>
int BinaryTree<T>::Depth()
{
	return Depth(&Root);
}

template<class T>
void BinaryTree<T>::Clear(Node<T> **tree)
{
	if (*tree == NULL)
		return;
	Clear(&((*tree)->m_Left));
	Clear(&((*tree)->m_Right));
	delete *tree;
	*tree = NULL;
}

template<class T>
void BinaryTree<T>::Clear()
{
	Clear(&Root);
}

template<class T>
void BinaryTree<T>::preOrder(Node<T>*subTree, void(*operation)(Node<T>*p)){
	if (subTree != NULL){
		operation(subTree);
		preOrder(subTree->m_Left, operation);
		preOrder(subTree->m_Right, operation);
	}

}

template<class T>
void BinaryTree<T>::preOrder(void(*operation)(Node<T>*p)){
	preOrder(Root, operation);
}


template<class T>
void BinaryTree<T>::inOrder(Node<T>*subTree, void(*operation)(Node<T>*p)){
	if (subTree != NULL){
		inOrder(subTree->m_Left, operation);
		operation(subTree);
		inOrder(subTree->m_Right, operation);
	}

}

template<class T>
void BinaryTree<T>::inOrder(void(*operation)(Node<T>*p)){
	inOrder(Root, operation);
}


template<class T>
void BinaryTree<T>::postOrder(Node<T>*subTree, void(*operation)(Node<T>*p)){
	if (subTree != NULL){
		postOrder(subTree->m_Left, operation);
		postOrder(subTree->m_Right, operation);
		operation(subTree);
	}

}

template<class T>
void BinaryTree<T>::postOrder(void(*operation)(Node<T>*p)){
	postOrder(Root, operation);
}

template<class T>
void BinaryTree<T>::preOrderNoRecur(void(*operation)(Node<T>*p)){
	Stack<Node<T>*>s;
	Node<T>* p = Root;
	s.Push(NULL);//avoid the situation that when visiting the last node,s do operation Pop()
	while (p != NULL){
		Visit(p);
		if (p->m_Right != NULL) s.Push(p->m_Right);
		if (p->m_Left != NULL) p = p->m_Left;
		else
			p = s.Pop();
	}
}
#endif