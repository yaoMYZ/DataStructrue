#ifndef STRAIGHTSELECTIONSORT
#define STRAIGHTSELECTIONSORT

template<class T>
void StraightSelectionSort(int length, T *a){
	for (size_t i = 0; i < length-1; i++){
		int min = i;
		for (size_t j = i+1; j <= length - 1; j++){
			if (a[j] < a[min])
				min = j;
		}
		T temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}


#endif