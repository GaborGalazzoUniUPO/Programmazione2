#define _GNU_SOURCE   // permette di usare estensioni GNU
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

typedef struct lis_int{
	int n;
	struct lis_int* next;
} int_list;

void die(char* s){
	perror(s);
	exit(1);
}

void scrivi_numero(int_list *i, FILE *f)
{
  fprintf(f,"%d",i->n);
}

int_list* crea_numero(int n){
	int_list* list = malloc(sizeof(int_list));
	if(list==NULL)
		die("iompossibile allocare la memoria per un int_lis");
	list->n = n;
	return list;
}

int_list* add_on_head(int_list* curr, int_list* head){
	curr->next = head;
	return curr;
}

int_list *inserisci_num_ordinata(int_list *lis, int_list *c)
{
  assert(c!=NULL);
  int_list *candidato = lis;
  int_list *precedente = NULL;
  while(candidato!=NULL) {
    if(candidato->n > c->n)
      break;
    precedente = candidato;
    candidato = candidato->next;
  }
  // caso in cui sono arrivato in fondo alla lista
  if(candidato==NULL) {
    if(precedente!=NULL) {//lista non vuota
      precedente->next = c;
      c->next = NULL;
    }
    else {// lista vuota
      lis = c;
      c->next = NULL;
    }
  }
  else {// l'inserimento avviene non in fondo
    if(precedente!=NULL) {//lista non vuota
      c->next = precedente->next;
      precedente->next = c;
    }
    else {// lista vuota
      lis = c;
      c->next = candidato;
    }
  }
  return lis;
}

void print_num(int_list* n, FILE* fp){
	fprintf(fp, "%d\n", n->n);
}

int_list* leggi_int_da_file(FILE *f){
	int n;
	int_list* head = NULL;
	while(fscanf(f,"%d",&n)!=EOF){
		head = inserisci_num_ordinata(head, crea_numero(n));
	}
	return head;
}

void scrivi_lista_su_file(int_list* list, FILE* f2){
	while(list!=NULL){
		print_num(list, f2);
		list = list->next;
	}
}

void destroy_num(int_list* num){
	free(num->next);
	free(num);
}

void destroy_list(int_list* list){
	if(list == NULL)
		return;
	destroy_list(list->next);
	free(list);
}



int main(int argc, char* argv[]){
	
	if(argc!=2)
	{
		printf("usage: %s nomefile", argv[0]);
		return 1;
	}
	FILE* f = NULL;
	if((f = fopen(argv[1],"rt"))==NULL)
		die("impossibile aprire il file per leggere");
	
	int_list* list = leggi_int_da_file(f);
	
	FILE* f2 = NULL;
	if((f2 = fopen(strcat(argv[1],".ordinati"),"wt"))==NULL)
		die("impossibile aprire il file per scrivere");
	
	scrivi_lista_su_file(list, f2);
	destroy_list(list);
	list = NULL;
	
	if(fclose(f))
		die("Impossibile chiudere file f");
	
	if((f = fopen(argv[1],"rt"))==NULL)
		die("impossibile aprire il file per leggere");
	
	list = leggi_int_da_file(f);
	while(list!=NULL)
	{
		print_num(list, stdout);
		list = list->next;
		destroy_num(list);
	}
	
	if(fclose(f))
		die("Impossibile chiudere file f");
	
	if(fclose(f2))
		die("Impossibile chiudere file f2");
	
	return 0;
}
