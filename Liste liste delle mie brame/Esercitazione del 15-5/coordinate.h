// ---- oggetto coordinate 
typedef struct {
  double lat;
  double lon;
} coordinate;


void stampa_coordinate(coordinate c, FILE *f);

int latitudinepiuanord(coordinate a, coordinate b);


double distanza(coordinate p, coordinate q);
