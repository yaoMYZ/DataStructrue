#ifndef TREE
#define TREE

#include<iostream>
#include<string.h>
#include"Stack.h"
#include<queue>
using namespace std;

#define StackMaxSize 100

template<class T>
struct ListNode
{
	T member;
	ListNode<T> *next = NULL;
};

template<class T>
struct Node{
	T m_Member;
	Node<T> *m_Left = NULL;
	Node<T> *m_Right = NULL;
};


template<class T>
struct SignNode{
	int sign;
	Node<T> *p;
	SignNode() :sign(0), p(NULL){}
};

template<class T>
void Visit(Node<T> *p){
	cout << p->m_Member << " ";
}

template<class T>
class BinaryTree{
private:
	Node<T> *Root;
	int NodeNumber;
	void Insert(Node<T>**, T);
	int Delete(Node<T> **, T);
	int Depth(Node<T> *);
	void Clear(Node<T> *);
	void preOrder(Node<T> *, void(*operation)(Node<T>*p));
	void inOrder(Node<T> *, void(*operation)(Node<T>*p));
	void postOrder(Node<T> *, void(*operation)(Node<T>*p));
	void exchangeChild(Node<T> *);
	void ifEqual(Node<T>*, Node<T>*,bool &);
	void copy(Node<T>**,Node<T>*);
	void changeToList(Node<T>*, ListNode<T>**);
	void changeIntoCharacter(Node<T>*, T**, int index);
public:
	BinaryTree(){
		Root = NULL;
		NodeNumber = 0;
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
	void inOrderNoRecur(void(*operation)(Node<T>*p));//traverse the tree by inorder without recursion
	void postOrderNoRecur(void(*operation)(Node<T>*p));//traverse the tree by postorder without recusion
	void exchangeChild();//exchange left subtrees and right subtrees
	Node<T>* getRoot();//get Root node
	bool ifEqual(BinaryTree<T> );//jude the two if they are equal
	void copy(BinaryTree<T>);//copy a tree
	ListNode<T>* changeToList();//use the tree nodes to create a list
	void createByCharacter(T a[], int len);//create a tree by characters
	T* changeIntoCharacter();//return a ordinal character array
};



template<class T>
void BinaryTree<T>::Insert(Node<T> **tree, T a)//为使指针进行地址传递需使用指向指针的指针
{

	if (*tree == NULL){
		Node<T> *p = new Node<T>;
		p->m_Member = a;
		*tree = p;

		NodeNumber++;
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
	int jude= Delete(&Root, a);
	if (jude == 1)
		NodeNumber++;
	return jude;
}

template<class T>
int BinaryTree<T>::Depth(Node<T> *tree)
{
	if (tree == NULL)
		return 0;
	int temp1 = Depth(tree->m_Left);
	int temp2 = Depth(tree->m_Right);
	if (temp1 > temp2)
		return temp1 + 1;
	else
		return temp2 + 1;
}


template<class T>
int BinaryTree<T>::Depth()
{
	return Depth(Root);
}

template<class T>
void BinaryTree<T>::Clear(Node<T> *tree)
{
	if (tree == NULL)
		return;
	else
	{
		Clear(tree->m_Left);
		Clear(tree->m_Right);
		delete tree;
		tree = NULL;
	}	
}

template<class T>
void BinaryTree<T>::Clear()
{
	Clear(Root);
	Root = NULL;
	NodeNumber = 0;
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

template<class T>
void BinaryTree<T>::inOrderNoRecur(void(*operation)(Node<T>*p)){
	Stack<Node<T>*>s;
	Node<T>* p = Root;
	while (p!=NULL||!s.IsEmpty()){
	    while (p!= NULL){
			s.Push(p);
			p = p->m_Left;
		}
		if(!s.IsEmpty()){
			p = s.Pop();
			Visit(p);
			p = p->m_Right;//at this point, p's right child can be NULL,as long as s is not empty.
		}
		
	}
}

template<class T>
void BinaryTree<T>::postOrderNoRecur(void(*operation)(Node<T>*p)){
	Stack<SignNode<T>>s;
	SignNode<T> f;
	Node<T>* p=Root;
	do {
		while (p != NULL){
			f.p = p;
			f.sign = 0;//it must be initialised as 0
			s.Push(f);
			p = p->m_Left;
		}
		int continue1 = 1;//the signal for continuing circulation so that the property sign of the parent node can turn into R
		while (continue1&&!s.IsEmpty()){
			f = s.Pop();
			p = f.p;
			if (f.sign == L){
				f.sign = 1;
				s.Push(f);
				continue1 = 0;
				p = p->m_Right;
			}
			else{
				Visit(p);//continuing the circulation until meeting the node that haven't visit tiwce 
			}
		}
	} while (!s.IsEmpty());
}

template<class T>
void BinaryTree<T>::exchangeChild(Node<T> *subNode){
	if (subNode != NULL){
		//exchange the child node
		Node<T> *p = subNode->m_Left;
		subNode->m_Left = subNode->m_Right;
		subNode->m_Right = p;

		exchangeChild(subNode->m_Left);
		exchangeChild(subNode->m_Right);
	}
}

template<class T>
void BinaryTree<T>::exchangeChild(){
	exchangeChild(Root);
}

template<class T>
Node<T>* BinaryTree<T>::getRoot(){
	return Root;
}

template<class T>
void BinaryTree<T>::ifEqual(Node<T>* subTree1,Node<T>* subTree2,bool &jude){
	if (!jude)//the value of jude is false,so we can return immediately
		return;
	if (subTree1==NULL&&subTree2==NULL){
		return;
	}
	if (subTree1 != NULL&&subTree2 != NULL){
		if (subTree1->m_Member != subTree2->m_Member){
			jude = false;
			return;
		}
		ifEqual(subTree1->m_Left, subTree2->m_Left, jude);
		ifEqual(subTree1->m_Right, subTree2->m_Right, jude);
	}
	else{
		jude = false;
		return;
	}
		
}

template<class T>
bool BinaryTree<T>::ifEqual(BinaryTree<T> another){
	bool jude = true;
	ifEqual(Root,another.getRoot(),jude);
	return jude;
}

template<class T>
void BinaryTree<T>::copy(Node<T> **subNode1, Node<T>*subNode2){
	if (subNode2 == NULL){
		*subNode1 = NULL;
		return;
	}
	else{
		Node<T> *p = new Node<T>;
		p->m_Member = subNode2->m_Member;
		*subNode1 = p;

		NodeNumber++;
		copy(&((*subNode1)->m_Left), subNode2->m_Left);
		copy(&((*subNode1)->m_Right), subNode2->m_Right);
	}

}

template<class T>
void BinaryTree<T>::copy(BinaryTree<T> another){
	copy(&Root, another.getRoot());
}

template<class T>
void BinaryTree<T>::changeToList(Node<T> *subNode,ListNode<T>**head){
	if (subNode == NULL){
		return;
	}
	else{
		changeToList(subNode->m_Right,&(*head));

		ListNode<T>*p = new ListNode<T>;
		p->member = subNode->m_Member;
		p->next = *head;
		*head = p;

		changeToList(subNode->m_Left,&(*head));
	}
}

template<class T>
ListNode<T>* BinaryTree<T>::changeToList(){
	ListNode<T>* head = NULL;
	changeToList(Root, &head);
	return head;
}

template<class T>
void BinaryTree<T>::createByCharacter(T a[], int len){
	Clear();//first clear the tree
	queue<SignNode<T>>q;
	SignNode<T>snode;
	Node<T>*parent = NULL;
	int reg = 0;
	if (a[0] != 0){
		Node<T>*root = new Node<T>;
		root->m_Member = a[0];
		Root = root;

		NodeNumber++;
		//add the root node to the stack
		snode.p = root;
		snode.sign = 0;
		q.push(snode);
	}
	else{
		return;
	}
	
	while (!q.empty()){
		snode = q.front();
		q.pop();
		parent = snode.p;
		reg = snode.sign;
		
		if (2 * reg+1 < len){
			if (a[2 * reg + 1] != 0){
				//add the child node to the tree
				Node<T>*leftchild = new Node<T>;
				leftchild->m_Member = a[2*reg+1];
				parent->m_Left = leftchild;

				NodeNumber++;
				//add the child node into the stack
				snode.p = leftchild;
				snode.sign = 2*reg+1;
				q.push(snode);
			}
			else{
				parent->m_Left = NULL;
			}
		}
		if (2 * reg +2< len){
			if (a[2 * reg+2] != 0){
				//add the child node to the tree
				Node<T>* rightchild = new Node<T>;
				rightchild->m_Member = a[2 * reg+2];
				parent->m_Right = rightchild;

				NodeNumber++;
				//add the child node into the stack
				snode.p = rightchild;
				snode.sign = 2 * reg+2;
				q.push(snode);
			}
			else{
				parent->m_Right = NULL;
			}
		}
	} 
}

template<class T>
void BinaryTree<T>::changeIntoCharacter(Node<T>* subNode, T** a, int index){
	if (subNode != NULL){
		(*a)[index] = subNode->m_Member;
		changeIntoCharacter(subNode->m_Left, a, 2 * index + 1);
		changeIntoCharacter(subNode->m_Right, a, 2 * index + 2);
	}
   else
	return;
}

template<class T>
T* BinaryTree<T>::changeIntoCharacter(){
	T *a=new T[100];
	changeIntoCharacter(Root, &a, 0);
	return a;
}
#endif