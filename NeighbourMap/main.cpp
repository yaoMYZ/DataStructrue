#include<iostream>
#include"NeighbourList.h"
#include"NeighbourMatric.h"

using namespace std;

int main(){
	//NeighbourMatric<char> n;
	//n.Create();


	NeighbourList<char> nl;
	nl.Create();
	nl.BFS();
	nl.DFS();
	system("pause");
}