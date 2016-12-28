#ifndef NEIGHBOURLIST
#define NEIGHBOURLIST

#include"Queue.h"
#include<iostream>
#include<queue>
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


struct EdgeInfor{
	int from;
	int to;
	int weight;
	EdgeInfor(){
		from = 0;
		to = 0;
		weight = 0;
	}
	EdgeInfor(int f = 0, int t = 0, int w = 0){
		from = f;
		to = t;
		weight = w;
	}

	EdgeInfor& operator =(const  EdgeInfor &f2){
		from = f2.from;
		to = f2.to;
		weight = f2.weight;
		return *this;
	}
};

bool operator <(const  EdgeInfor &f1, const  EdgeInfor &f2){
	return f1.weight > f2.weight;
}



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
	EdgeInfor* MinSpanTree();
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


template<class V>
EdgeInfor* NeighbourList<V>::MinSpanTree(){
	priority_queue<EdgeInfor> pq;
	memset(Visit, false, VertexNumber);
	int count = 0;
	//�����б߷������ȶ�����
	for (int i = 0; i < EdgeNumber; i++){
		EdgeNode *temp = Vertex[i].Next;
		while (temp != NULL){
			EdgeInfor EI = { i, temp->index, temp->weight };
			pq.push(EI);
			temp = temp->next;
		}
	}
	//�����
	EdgeInfor *forReturn=new EdgeInfor[VertexNumber];
	while (count < EdgeNumber){
		EdgeInfor temp = pq.top();
		pq.pop();
		if (!Visit[temp.from] && !Visit[temp.to]){
			forReturn[count] = temp;
			Visit[temp.from] = true;
			Visit[temp.to] = true;
			count++;
		}
	}
	//��ʾ
	for (size_t i = 0; i < count; i++){
		cout << Vertex[forReturn[i].from].Data << " " << forReturn[i].weight << " " << Vertex[forReturn[i].to].Data << endl;
	}
	return forReturn;
}
#endif