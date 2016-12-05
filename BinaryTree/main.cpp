#include "BinaryTree.h"
template<class T>
void showList(ListNode<T> *a){
	while (a != NULL){
		cout << a->member << " ";
		a = a->next;
	}
	cout << endl;
}


int main()
{
	BinaryTree<int> tree;
	int a[10];
	int reg = 0;
	cout << "请输入一串数字(输入-1结束输入）:" << endl;
	while (cin >> a[reg] && a[reg] != -1){
		reg++;
	}
    tree.createByCharacter(a, reg);
	tree.inOrderNoRecur(Visit);
	cout << endl;
	tree.exchangeChild();
	tree.inOrderNoRecur(Visit);
	cout << endl;
	/*tree.exchangeChild();
	tree.inOrder(Visit);*/
	/*BinaryTree<int> t;
	t.copy(tree);
	if (t.ifEqual(tree)){
		cout << "Yes" << endl;
	}
	t.inOrder(Visit);*/
	//showList(tree.changeToList());
	//int *b = tree.changeIntoCharacter();
	system("pause");
	return 0;
}

