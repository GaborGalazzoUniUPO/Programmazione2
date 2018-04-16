#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void die(char* n);
int file_size(FILE* fp);
void print_array(int a[], int dim);

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("usage %s nome_file\n",argv[0]);
		return 1;
	}
	char* nome_file = argv[1];
	
	
	FILE* fp = NULL;
	if((fp = fopen(nome_file, "rb")) == NULL)
		die("Errore durante l'apertra del file");
	int file_byte_dim = file_size(fp);
	int numbers[file_byte_dim/sizeof(int)];
	if(fread(numbers, sizeof(int), file_byte_dim/sizeof(int), fp) != file_byte_dim/sizeof(int))
		die("Errore durante la scrittura del file");
	fclose(fp);
	print_array(numbers, file_byte_dim/sizeof(int));
	return 0;
}

void die(char* n){
	perror(n);
	exit(1);
}

//Number of bytes inside fp file
int file_size(FILE* fp){
	int old = ftell(fp); //save current position
	fseek(fp, 0, SEEK_END); //set offset to the end
	int dim = ftell(fp); //get offset of the end
	fseek(fp,old,SEEK_SET); //restore old position
	return dim;
}

void print_array(int a[], int dim){
	for(int i = 0; i<dim; i++)
		printf("%d\n", a[i]);
}
