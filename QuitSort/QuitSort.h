#ifndef QUITSORT
#define QUITSORT

#include <stdlib.h>

template<class T>
void QuitSort(int front, int end, T *a){
	if (front < end){
		int head = front;
		int tail = end;
		T border = a[end];//选取该组数最后一个元素作为一个分界值
		//数值交换
		while (head < tail){
			while (a[head] <= border&&tail>head)
				head++;
			while (a[tail]>=border&&tail>head)
				tail--;
			//交换两个数
			T temp = a[head];
			a[head] = a[tail];
			a[tail] = temp;
			head++;
		}
		a[end] = a[tail];
		a[tail] = border;
		QuitSort(front, tail - 1, a);
		QuitSort(tail + 1, end, a);
	}else
	return;
}






#endif