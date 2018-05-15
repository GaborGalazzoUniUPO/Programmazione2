// definisce il tipo citta composto dai campi nome e popolazione e 
// da un capo next da usare per le liste
typedef struct cit {
  char *nome;
  coordinate coord;
  struct cit *next;
} citta;

void stampa_citta(citta *c, FILE *f);

// confronta a e b restituendo -1 se a e' piu' a nord di b
int piuanord(citta *a, citta *b);

// confronta a e b restituendo -1 se a e' piu' vicina ad Alessandria di b
int vicinoAL(citta *a, citta *b);

int vicino_citta(citta *a, citta *b, citta* citta);