#ifndef NEIGHBOURLIST
#define NEIGHBOURLIST

#include"Queue.h"
#include<iostream>
using namespace std;

struct EdgeNode{
	int index = 0;
	int weight = 0;
	EdgeNode *next = NULL;
};

template<class T>
struct VertexNode{
	T Data;
	EdgeNode *Next = NULL;
};


template<class T>
class NeighbourList{
private:
	int VertexNumber;
	int EdgeNumber;
	VertexNode<T> *Vertex;
	bool *Visit;

	void DFS(int);
public:
	NeighbourList(){
		VertexNumber = 0;
		EdgeNumber = 0;
		Vertex = NULL;
		Visit = NULL;
	}
	~NeighbourList(){
		delete[] Vertex;
		delete[] Visit;
	}
	void Create();
	void DFS();
	void BFS();
};


template<class T>
void NeighbourList<T>::Create(){
	cout << "�����붥�������" << endl;
	cin >> VertexNumber;
	Vertex = new VertexNode<T>[VertexNumber];
	Visit = new bool[VertexNumber];

	for (int i = 0; i < VertexNumber; i++){
		cout << "�������" << i << "���ڵ�����ݣ�" << endl;
		cin >> Vertex[i].Data;
	}
	cout << "�����������ڵ�ĸ�����";
	int number = 0;
	cin >> number;
	EdgeNumber = number;

	for (int i = 0; i < number; i++){
		int x = 0;
		int y = 0;
		cout << "���������������ڵ��λ��������" << endl;
		cin >> x >> y;
		//�½ڵ㸳ֵ
		EdgeNode *newVertexNode = new EdgeNode;
		newVertexNode->index = y;
		cout << "������(" << x << "," << y << ")��Ȩ�أ�" << endl;
		cin >> newVertexNode->weight;
		//�����½ڵ�
		newVertexNode->next = Vertex[x].Next;
		Vertex[x].Next = newVertexNode;
	}
}


template<class T>
void NeighbourList<T>::BFS(){
	Queue<int> q;
	q.Push(0);
	memset(Visit, false, VertexNumber);

	while (!q.IsEmpty()){
		int index = q.Top();
		q.Pop();
		cout << Vertex[index].Data << " ";
		Visit[index] = true;
		EdgeNode *temp = Vertex[index].Next;
		while (temp != NULL){
			if (!Visit[temp->index]){
				q.Push(temp->index);
			}
			temp = temp->next;
		}
	}
	cout << endl;
}

template<class T>
void NeighbourList<T>::DFS(){
	memset(Visit, false, VertexNumber);
	DFS(0);
	cout << endl;
}

template<class T>
void NeighbourList<T>::DFS(int index){
	if (Visit[index])
		return;
	else{
		//��������ñ�־
		cout << Vertex[index].Data<<" ";
		Visit[index] = true;
		EdgeNode  *temp = Vertex[index].Next;
		while (temp != NULL){
			DFS(temp->index);
			temp = temp->next;
		}
	}
}
#endif