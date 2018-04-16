#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int str_bin_to_int(char* n);

int main(int argc, char* argv[]){
	if(argc==1){
		printf("usage %s numero_binario_1 numero_binario_2 ... numero_binario_n\n",argv[0]);
		return 1;
	}
	for(int i = 1; i < argc; i++){
		assert(strlen(argv[i])<=32);
		int num = str_bin_to_int(argv[i]);
		printf("%s = %d\n", argv[i], num);
	}
	return 0;
}

int str_bin_to_int(char* n){
	int i = 0;
	int num = 0;
	while(n[i] != 0){
		assert(n[i] == '0' || n[i] == '1');
		num = num<<1 | (n[i]-'0');
		i++;
	}
	return num;
}
