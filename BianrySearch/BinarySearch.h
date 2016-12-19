#ifndef BINARYSEARCH
#define BINARYSEARCH

template<class T>
T BinarySearch(T search,T *Array, int len){
	int head = 0;
	int tail = len - 1;
	int middle = (head+tail) / 2;
	bool IfFind = false;
	while (head<= tail){
		if (Array[middle] == search){
			return Array[middle];
			IfFind = true;
		}
		else{
			if (Array[middle] > search)
				tail = middle-1;
			else
				head = middle + 1;		
			middle = (head + tail) / 2;
		}
	}
	//无法找到元素
	try{
		if (!IfFind){
			throw "Element not Found!";
		}
	}
	catch (char *a){
		cout << a << endl;
	}
}












#endif