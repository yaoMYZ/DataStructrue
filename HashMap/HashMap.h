#ifndef HASHMAP
#define HASHMAP

#define DefautSize 100

#include<iostream>
using namespace std;

template<class K,class D>
struct Entry
{
	D data;
	K key;
	Entry<K, D>*link;
	Entry<K, D>(){
		link = NULL;
	}
	Entry<K, D>(K Key, D Data){
		data = Data;
		key = Key;
		link = NULL;
	}
};

template<class K,class D>
class HashMap{
private:
	Entry<K, D> **entry;
public:
	HashMap(){
		entry = new Entry<K, D>*[DefautSize];
		memset(entry, NULL, DefautSize);
	}
	~HashMap(){
		delete[] entry;
	}
	void Put(K key, D data);
	D Find(K);
};

template<class K,class D>
void HashMap<K, D>::Put(K key, D data){
	int index = key%DefautSize;
	Entry<K, D> *temp;
	if (entry[index] == NULL){
		entry[index] = new Entry<K, D>;
		entry[index]->data = data;
		entry[index]->key = key;
	}
	else	{
		temp = entry[index];
		while (temp->link!=NULL){
			temp = temp->link;			
		}
		Entry<K, D> *newEntry = new Entry<K, D>(key,data);
		temp->link = newEntry;
	}
}


template<class K,class D>
D HashMap<K, D>::Find(K key){
	int index = key%DefautSize;
	Entry<K, D> *temp = entry[index];
	while (temp!=NULL){
		if (temp->key = key){
			return temp->data;
		}
		else
			temp = temp->link;
	}
	//找不到节点
	try{
		throw "无此节点";
	}
	catch (char *a){
		cout << a << endl;
	}
}
#endif HASHMAP