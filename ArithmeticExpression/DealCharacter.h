#ifndef DEALCHARACTER
#define DEALCHARACTER
#include<string.h>
#include<math.h>

double CharacterToValue(char *c){
	int len=strlen(c);
	double value = 0;
	double decimal = 0;
	for (int i = 0; i < len; i++){
		if (c[i] == 46){
			int reg = 1;
			for (int j = i + 1; j < len; j++){
				decimal += (c[j] - 48) / pow(10.0,reg);
				reg++;
			}
			break;
		}
		value = value * 10 + c[i] - 48;
	}
	return value+decimal;
}


#endif