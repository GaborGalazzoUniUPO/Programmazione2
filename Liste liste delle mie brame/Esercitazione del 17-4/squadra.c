#define _GNU_SOURCE   // permette di usare estensioni GNU
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

typedef struct sq {
  char *nome;
  int punti;
  struct sq *next;
  int goal_fatti;
  int goal_subuiti;
} squadra;

squadra *crea_squadra(char n[], int p, int goal_f, int goal_s){
    squadra* s = malloc(sizeof(squadra));
    s->nome = malloc(255);
    strcpy(s->nome, n);
    s->punti = p;
    s->next = NULL;
    s->goal_fatti = goal_f;
    s->goal_subuiti = goal_s;
    return s;
}

// stampa la squadra a cui punta c
void scrivi_squadra(squadra *c, FILE *f)
{
  fprintf(f,"%s: %d %d %d",c->nome,c->punti, c->goal_fatti, c->goal_subuiti);
}

// stampa le citta della lista lis
void scrivi_lista(squadra *lis, FILE *f)
{
    if(lis==NULL)
        return;
    scrivi_squadra(lis,f);
    fprintf(f,"\n");
    scrivi_lista(lis->next, f);
}

void distruggi_squadra(squadra *c)
{
    free(c->nome);
    free(c);
}

// dealloca tutti gli elementi della lista 
void distruggi_lista(squadra *head)
{
    if(head==NULL)
        return;
    distruggi_lista(head->next);
    distruggi_squadra(head);
}

squadra* aggiungi_ord(squadra* lis, squadra* c){
    assert(c!=NULL);
  squadra *candidato = lis;
  squadra *precedente = NULL;
  while(candidato!=NULL) {
    if(strcmp(candidato->nome,c->nome)>0)
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

/**
 * aggiunge alla squadra di nome n esattamente p punti. 
 * Se la lista lis contiene già la squadra di nome n si deve 
 * semplicemente aumentare di p il suo punteggio; se invece 
 * lis non contiene tale squadra essa deve essere creata e gli 
 * deve essere assegnato il punteggio p.
 */
squadra *aggiungi_punti(squadra *lis, char n[], int p, int gf, int gs){
    squadra* head = lis;
    while(lis!=NULL){
        if(!strcmp(lis->nome, n)){
            lis->punti += p;
            lis->goal_fatti += gf;
            lis->goal_subuiti += gs;
            return head;
        }
        lis = lis->next;
    }
    return aggiungi_ord(head,  crea_squadra(n,p, gf, gs));
}

squadra *aggiungi_partita(squadra *classifica, char s1[], int g1, char s2[], int g2){
    if(g1>g2)
        return aggiungi_punti(classifica, s1, 3, g1, g2);
    if(g1<g2)
        return aggiungi_punti(classifica, s2, 3, g2, g1);
    return aggiungi_punti(aggiungi_punti(classifica, s2, 1, g2, g1), s1, 1, g1, g2);
}

squadra* leggi_risultati(squadra* classifica, FILE* fp){
    int g1, g2;
    char* s1;
    char* s2;
    while(fscanf(fp, "%d %d %ms %ms",&g1, &g2, &s1, &s2)==4)
    {
        classifica = aggiungi_partita(classifica, s1, g1, s2, g2);
        free(s1);
        free(s2);
    }
    return classifica;
}

// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}  

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("usage: %s nomefile", argv[0]);
        exit(1);
    }

    squadra *classifica = NULL;
   // classifica = aggiungi_punti(classifica,"Juve",1);   

    FILE* risultati = NULL;
    if((risultati = fopen(argv[1],"rt"))==NULL)
        die("impossibile aprire il file");

    classifica = leggi_risultati(classifica, risultati);
    scrivi_lista(classifica,stdout); // da scrivere in analogia a quanto fatto per le citta'
    distruggi_lista(classifica);     // da scrivere in analogia a quanto fatto per le citta'


    if(fclose(risultati)) die("impossibile chiudere il file");
   
    return 0;
}