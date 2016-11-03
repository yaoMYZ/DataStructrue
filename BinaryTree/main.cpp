#include "BinaryTree.h"

int main()
{
	BinaryTree<int> tree;
	tree.Insert(2);
	tree.Insert(4);
	tree.Insert(7);
	tree.preOrderNoRecur(Visit);
	system("pause");
	return 0;
}

