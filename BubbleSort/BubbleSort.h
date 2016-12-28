#ifndef BUBBLESORT
#define BUBBLESORT

template<class T>
void BubbleSort(int length,T *a){
	for (size_t i =length - 1; i >0; i--){
		for (size_t j = 0; j < i;j++){
			if (a[j]>a[j + 1]){
				T temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}








#endif