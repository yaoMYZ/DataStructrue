#ifndef NEIGHBOURMATRIC
#define NEIGHBOURMATRIC

#define Max 2147483647
#include"Queue.h"
#include<queue>
using namespace std;

struct ForMST{
	int from = -1;
	int index = -1;
	int weight = Max;
};

bool operator <(const ForMST &f1, const ForMST &f2){
	return f1.weight > f2.weight;
}

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
	ForMST* MinSpanTree();
};


template<class V>
void NeighbourMatric<V>::Create(){
	cout << "请输入顶点个数：" << endl;
	cin >> VertexNumber;

	Edges = new int* [VertexNumber];
	Vertex = new V[VertexNumber];
	for (int i = 0; i < VertexNumber; i++){
		Edges[i] = new int [VertexNumber];
		for (int j = 0; j < VertexNumber; j++)
			Edges[i][j] = Max;
	}
	for (int i = 0; i < VertexNumber; i++){
		cout << "请输入第" << i << "个节点的数据：" << endl;
		cin >> Vertex[i];
	}
	cout << "请输入相连节点的个数：";
	int number = 0;
	cin >> number;
	EdgeNumber = number;
	for (int i = 0; i < number; i++){
		int x = 0;
		int y = 0;
		cout << "请输入两个相连节点的位置索引：" << endl;
		cin >> x >> y;
		cout << "请输入("<<x<<","<<y<<")的权重：" << endl;
		cin >> Edges[x][y];
		//该图为无向图
		Edges[y][x] = Edges[x][y];
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
		//访问节点，并设置访问符号
		cout << Vertex[index] << " ";
		Edges[index][index] = 0;
		
		for (int i = 0; i < VertexNumber; i++){
			if (Edges[index][i] != Max&&Edges[i][i]!=0)
				q.Push(i);
		}
	}
	//访问符号复原
	for (int i = 0; i < VertexNumber; i++){
		Edges[i][i] = Max;
	}
	cout << endl;
}

template < class T>
void NeighbourMatric<T>::DFS(){
	DFS(0);
	//访问符号复原
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
		//访问节点，并设置访问符号
		cout << Vertex[index] << " ";
		Edges[index][index] = 0;
		//访问相邻节点
		for (int i = 0; i < VertexNumber; i++){
			if (Edges[index][i] != Max)
				DFS(i);
		}
	}
	//访问符号复原
	for (int i = 0; i < VertexNumber; i++){
		Edges[i][i] = Max;
	}
}

template<class V>
ForMST* NeighbourMatric<V>::MinSpanTree(){
	int count = 0;

	ForMST *mst=new ForMST [VertexNumber];
	//对优先队列初始化赋值
	priority_queue<ForMST*> pq;
	for (size_t i = 0; i < VertexNumber; i++)	{
		if (Edges[0][i] != Max){
			mst[i].from = 0;
			mst[i].index = i;
			mst[i].weight = Edges[0][i];
			pq.push(&mst[i]);
		}
	}
	//设置访问标志
	Edges[0][0] = 0;
	count++;
	while (count < VertexNumber){
		//取出权重最小节点
		ForMST *temp = pq.top();
		pq.pop();
		int index = temp->index;

		//更新边集
		if (Edges[index][index] != 0){//该点必须没访问过
			for (size_t i = 0; i < VertexNumber; i++){
				if (Edges[index][i] != Max&&Edges[i][i]!=0){//要操作的点必须没被访问过
					if (mst[i].weight != Max){
						//边集中通向该点的边已存在
						if (mst[i].weight>Edges[index][i]){
							mst[i].from = index;
							mst[i].weight = Edges[index][i];
						}
					}
					else{
						//边集中通向该点的边不存在
						mst[i].from = index;
						mst[i].index = i;
						mst[i].weight = Edges[index][i];
						pq.push(&mst[i]);
					}
				}
			}
			//访问节点加1
			count++;
			Edges[index][index] = 0;
		}
	}

	for (size_t i = 0; i < VertexNumber; i++){
		if (mst[i].weight!=Max)
		cout << Vertex[mst[i].from] << " " << mst[i].weight << " " << Vertex[mst[i].index] << endl;
	}
	return mst;
}
#endif