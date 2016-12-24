#ifndef NEIGHBOURMATRIC
#define NEIGHBOURMATRIC

#define Max 2147483647
#include"Queue.h"
using namespace std;

template<class V>
class NeighbourMatric{
private:
	int **Edges;
	V *Vertex;
	int VertexNumber;
	int EdgeNumber;

	void DFS(int index);
public:
	NeighbourMatric(){
		Edges = NULL;
		Vertex = NULL;
		VertexNumber = 0;
		EdgeNumber = 0;
	}
	~NeighbourMatric(){
		delete [] Edges;
		delete [] Vertex;
	}
	void Create();
	void BFS();
	void DFS();
	void Print();
};


template<class V>
void NeighbourMatric<V>::Create(){
	cout << "�����붥�������" << endl;
	cin >> VertexNumber;

	Edges = new int* [VertexNumber];
	Vertex = new V[VertexNumber];
	for (int i = 0; i < VertexNumber; i++){
		Edges[i] = new int [VertexNumber];
		for (int j = 0; j < VertexNumber; j++)
			Edges[i][j] = Max;
	}
	for (int i = 0; i < VertexNumber; i++){
		cout << "�������" << i << "���ڵ�����ݣ�" << endl;
		cin >> Vertex[i];
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
		cout << "������("<<x<<","<<y<<")��Ȩ�أ�" << endl;
		cin >> Edges[x][y];
	}
}


template <class V>
void NeighbourMatric<V>::Print(){
	for (int i = 0; i < VertexNumber; i++){
		for (int j = 0; j < VertexNumber; j++){
			if (Edges[i][j] != Max)
				cout << Edges[i][j];
			else
				cout << " ";
		}
		cout << endl;
	}
}


template<class V>
void NeighbourMatric<V>::BFS(){
	Queue<int> q;
	q.Push(0);
	while (!q.IsEmpty()){
		int index = q.Top();
		q.Pop();
		//���ʽڵ㣬�����÷��ʷ���
		cout << Vertex[index] << " ";
		Edges[index][index] = 0;
		
		for (int i = 0; i < VertexNumber; i++){
			if (Edges[index][i] != Max&&Edges[i][i]!=0)
				q.Push(i);
		}
	}
	//���ʷ��Ÿ�ԭ
	for (int i = 0; i < VertexNumber; i++){
		Edges[i][i] = Max;
	}
	cout << endl;
}

template < class T>
void NeighbourMatric<T>::DFS(){
	DFS(0);
	//���ʷ��Ÿ�ԭ
	for (int i = 0; i < VertexNumber; i++){
		Edges[i][i] = Max;
	}
	cout << endl;
}

template<class V>
void NeighbourMatric<V>::DFS(int index){
	if (Edges[index][index] == 0)
		return;
	else{
		//���ʽڵ㣬�����÷��ʷ���
		cout << Vertex[index] << " ";
		Edges[index][index] = 0;
		//�������ڽڵ�
		for (int i = 0; i < VertexNumber; i++){
			if (Edges[index][i] != Max)
				DFS(i);
		}
	}
}
#endif