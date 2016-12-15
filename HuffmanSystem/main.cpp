#include<iostream>
#include"HuffmanTree.h"
#include"TransportSystem.h"

using namespace std;

int main(){
	//Sign<char> a[3] = { { 10, 'A' }, { 5, 'B' }, { 3, 'C' } };
	//HuffmanTree<char> ht;
	//ht.CreateTree(a, 3);
	//ht.ShowMap();
	//char *show = ht.Coding("ABC", 3);
	//cout << show << endl;
	//cout << ht.Encoding(show) << endl;
	//ht.ShowTree();
	TransportSystem<char> ts;
	ts.menu();
	system("pause");
}