#include<iostream>

using namespace std;

template<class T>
struct BinaryTree{
	T data;
	BinaryTree *left;
	BinaryTree *right;
};


template<class T>
BinaryTree<T> *CreateHuffman(T a[], int n){//根据数组a中n个权值建立一个哈夫曼树，返回树根指针
	int i, j;
	BinaryTree<T> **b;
	BinaryTree<T> *q=NULL;
	b = new BinaryTree<T> *[n];//动态分配一个有b指向的的指针数组
	//初始化动态数组b，使每个指针元素指向a数组中对应元素的结点
	for (i = 0; i < n; i++){
		b[i] = new BinaryTree<T>;
		b[i]->data = a[i];
		b[i]->left = b[i]->right = NULL;
	}
	//进行n-1次循环建立哈夫曼树
	for (i = 1; i < n; i++){
		//用k1表示森林中具有最小权值的树根结点的下标，k2表示森林中具有次小权值的树根结点的下标
		int k1 = -1, k2;
		//初始化k1.k2,使k1指向森林的第一棵树，k2指向森林的第二棵树
		for (j = 0; j < n; j++){
			if (b[j] != NULL&&k1 == -1){
				k1 = j;
				continue;
			}
			if (b[j] != NULL){
				k2 = j;
				break;
			}
		}
		//从当前森林中选出权值最小的两棵树
		for (j = k1; j < n; j++){
			if (b[k1]->data < b[j]->data){
				k2 = k1;
				k1 = j;
				continue;
			}
			if (b[k2]->data < b[j]->data)
				k2 = j;
		}
		//由权值最小的两棵树建立一棵新树，q为树根结点
		q = new BinaryTree<T>;
		q->data = b[k1]->data + b[k2]->data;
		//将新树的指针赋给b[k1]，b[k2]的位置为空
		b[k1] = q;
		b[k2] = NULL;
	}
	delete[]b;
	return q;
}