#include<iostream>

using namespace std;

template<class T>
struct BinaryTree{
	T data;
	BinaryTree *left;
	BinaryTree *right;
};


template<class T>
BinaryTree<T> *CreateHuffman(T a[], int n){//��������a��n��Ȩֵ����һ��������������������ָ��
	int i, j;
	BinaryTree<T> **b;
	BinaryTree<T> *q=NULL;
	b = new BinaryTree<T> *[n];//��̬����һ����bָ��ĵ�ָ������
	//��ʼ����̬����b��ʹÿ��ָ��Ԫ��ָ��a�����ж�ӦԪ�صĽ��
	for (i = 0; i < n; i++){
		b[i] = new BinaryTree<T>;
		b[i]->data = a[i];
		b[i]->left = b[i]->right = NULL;
	}
	//����n-1��ѭ��������������
	for (i = 1; i < n; i++){
		//��k1��ʾɭ���о�����СȨֵ�����������±꣬k2��ʾɭ���о��д�СȨֵ�����������±�
		int k1 = -1, k2;
		//��ʼ��k1.k2,ʹk1ָ��ɭ�ֵĵ�һ������k2ָ��ɭ�ֵĵڶ�����
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
		//�ӵ�ǰɭ����ѡ��Ȩֵ��С��������
		for (j = k1; j < n; j++){
			if (b[k1]->data < b[j]->data){
				k2 = k1;
				k1 = j;
				continue;
			}
			if (b[k2]->data < b[j]->data)
				k2 = j;
		}
		//��Ȩֵ��С������������һ��������qΪ�������
		q = new BinaryTree<T>;
		q->data = b[k1]->data + b[k2]->data;
		//��������ָ�븳��b[k1]��b[k2]��λ��Ϊ��
		b[k1] = q;
		b[k2] = NULL;
	}
	delete[]b;
	return q;
}