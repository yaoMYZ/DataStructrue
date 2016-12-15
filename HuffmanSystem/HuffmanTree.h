#ifndef HUFFMANTREE
#define HUFFMANTREE

#define ChildNode   2
#define MaxCharSize 100

#include<queue>
#include<hash_map>
#include<iostream>
using namespace std;

struct CharLess : public binary_function<const char*, const char*, bool>
{
public:
	result_type operator()(const first_argument_type& _Left, const second_argument_type& _Right) const
	{
		return(_stricmp(_Left, _Right) < 0 ? true : false);
	}
};

template<class T>
struct  Sign
{
	int weight;
	T member;
	Sign(){
		if (typeid(T)==typeid(char))
		{
			member = '@';
		}
		weight = 0;
	}
	Sign(int w, T t){
		weight = w;
		member = t;
	}
};


template<class T>
struct TreeNode
{
	Sign<T> sign;
	TreeNode<T>* node[ChildNode];
	int symbol;//�����ж��Ƿ�ΪҶ�ӽ�㣬1�ǣ�0����
	TreeNode<T>(){
		symbol = 0;//��ʼ������Ҷ�ӽ�/��
		for (int i = 0; i < ChildNode; i++){
			node[i] = NULL;
		}
	}
};

template<class T>
bool operator <(const TreeNode<T> &t1, const TreeNode<T> &t2){
	return t1.sign.weight > t2.sign.weight;
}


template<class T>
void Visit(TreeNode<T> *node){
	cout << node->sign.member << " ";
}

template <class T>
class HuffmanTree{
private:
	TreeNode<T>* Root;
	hash_map<T, char*> hm;
	hash_map<char*, T, hash_compare<const char*, CharLess>> hmForEncoding;
	char *coding;//����������Ŷ�Ӧ�ַ�������ʱ����
	int Size;//�ࡢ���������ַ����Ĵ�С
	void ForHashMap(TreeNode<T>*, int rag, int index);
	void InOrder(TreeNode<T>*, void(*operatin)(TreeNode<T>*));
	T* IfResize(int index, T*);
	void ShowTree(TreeNode<T>*, int);
public:
	HuffmanTree(){
		coding = new char[MaxCharSize];
		memset(coding, '\0', MaxCharSize);
		Size = 1000;
		Root = NULL;
	}
	~HuffmanTree(){
		delete[] coding;
	}
	void CreateTree(Sign<T> *sign, int length);
	void InOrder(void(*operatin)(TreeNode<T>*));
	void ShowMap();
	char* Coding(T *a, int len);
	T* Encoding(char*);
	void ShowTree();
};


template<class T>
void HuffmanTree<T>::CreateTree(Sign<T> *sign, int length){
	//��Ž������ȶ���
	priority_queue<TreeNode<T>*> pq;
	//�γɽ������������ȶ�����
	for (int i = 0; i < length; i++){
		TreeNode<T> *tempTN = new TreeNode<T>;
		tempTN->sign = sign[i];
		tempTN->symbol = 1;
		pq.push(tempTN);
	}
	//huffman�㷨
	while (pq.size() != 1){
		//Ŀǰ��С�ڵ�
		TreeNode<T> *small1 = pq.top();
		pq.pop();
		//Ŀǰ��С���
		TreeNode<T> *small2 = pq.top();
		pq.pop();
		//�����½ڵ�
		TreeNode<T> *newNode = new TreeNode<T>;
		newNode->node[0] = small1;
		newNode->node[1] = small2;
		newNode->sign.weight = small1->sign.weight + small2->sign.weight;
		//�½ڵ������
		pq.push(newNode);
	}
	//���������һ�����Ϊ�����
	Root = pq.top();
	pq.pop();

	//����ӳ���ϵ
	ForHashMap(Root, 1, 0);

}

template<class T>
void HuffmanTree<T>::InOrder(TreeNode<T>*node, void(*operation)(TreeNode<T>*)){
	if (node != NULL){
		InOrder(node->node[0], operation);
		operation(node);
		InOrder(node->node[1], operation);
	}
}

template<class T>
void HuffmanTree<T>::InOrder(void(*operation)(TreeNode<T>*)){
	InOrder(Root, operation);
}

template<class T>
void HuffmanTree<T>::ForHashMap(TreeNode<T>*node, int rag, int index){
	if (node->symbol == 1){
		//hashmap�洢
		coding[index] = rag + 48;
		coding[index + 1] = '\0';
		//����hashmap�洢
		hm[node->sign.member] = new char[MaxCharSize];//
		strcpy_s(hm[node->sign.member], MaxCharSize, coding);
		//����hashmap����
		char* tempChar = new char[MaxCharSize];
		strcpy_s(tempChar, MaxCharSize, coding);
		hmForEncoding[tempChar] = node->sign.member;
		//�����ַ�����λ������
		coding[index] = '\0';
		return;
	}
	else{
		coding[index] = rag + 48;
		ForHashMap(node->node[0], 0, index + 1);
		ForHashMap(node->node[1], 1, index + 1);
	}
}


template<class T>
void HuffmanTree<T>::ShowMap(){
	for (hash_map<T, char *>::const_iterator it = hm.begin(); it != hm.end(); ++it){
		cout << it->first << "-> " << it->second << endl;
	}
}


template<class T>
T* HuffmanTree<T>::IfResize(int index, T*bc){
	if (index + 10 > Size){
		Size = Size * 2;
		T *newMemory = new T[Size];
		for (int i = 0; i <= index; i++){
			newMemory[i] = bc[i];
		}
		delete[] bc;
		return newMemory;
	}
	else
		return bc;
}

template<class T>
char* HuffmanTree<T>::Coding(T *a, int len){
	char *binaryChar = new char[Size];
	int index = 0;
	for (int i = 0; i < len; i++){
		binaryChar = IfResize(index, binaryChar);
		try{
			if (hm.count(a[i]) == 0){
				throw "����huffman���в����ڸ�ֵ";
			}
			else{
				int length = strlen(hm[a[i]]);
				for (int j = 0; j < length; j++){
					binaryChar[index++] = hm[a[i]][j];
				}
			}
		}
		catch (char *s){
			cout << s << endl;
		}
	}
	binaryChar[index] = '\0';
	Size = 1000;
	return binaryChar;
}


template<class T>
T* HuffmanTree<T>::Encoding(char* a){
	int len = strlen(a);
	T *encoding = new T[Size];
	int index = 0;
	for (int i = 0; i < len; i++){
		encoding = IfResize(index, encoding);
		memset(coding, '\0', MaxCharSize);//������ʱ�ַ�����
		int indexForCode = 0;
		int maxIteration = i + MaxCharSize;
		while (i<maxIteration){
			coding[indexForCode++] = a[i];
			if (hmForEncoding.count(coding)>0){
				encoding[index++] = hmForEncoding[coding];
				break;
			}
			i++;
		}
	}
	if (typeid(encoding) == typeid(char*)){
		encoding[index] = '\0';
	}
	return encoding;
}

template<class T>
void HuffmanTree<T>::ShowTree(){
	ShowTree(Root, 0);
}


template<class T>
void HuffmanTree<T>::ShowTree(TreeNode<T>*node, int layer){
	if (node != NULL){
		ShowTree(node->node[1], layer + 1);
		for (int i = 0; i < layer; i++){
			cout << " ";
		}
		cout << node->sign.member << endl;
		ShowTree(node->node[0], layer + 1);
	}
}


#endif