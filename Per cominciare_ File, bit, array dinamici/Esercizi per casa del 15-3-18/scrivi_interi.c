#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void die(char* n);

int main(int argc, char* argv[]){
	if(argc<3){
		printf("usage %s nome_file numero_1 numero_2 ... numero_n\n",argv[0]);
		return 1;
	}
	char* nome_file = argv[1];
	int interi[argc-2];
	for(int i = 2; i<argc; i++){
		interi[i-2] = atoi(argv[i]);
	}
	FILE* fp = NULL;
	if((fp = fopen(nome_file, "wb")) == NULL)
		die("Errore durante l'apertra del file");
	if(fwrite(interi, sizeof(int), argc-2, fp) != argc-2)
		die("Errore durante la scrittura del file");
	fclose(fp);
	return 0;
}

void die(char* n){
	perror(n);
	exit(1);
}
