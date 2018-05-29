#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *  my_strtok(char *s, const char *delim) 
{
    static char *lasts;

    if (s == NULL)
        s = lasts;
    while (strchr(delim, *s)) s++;
    lasts = s + strcspn(s, delim);
    if (*lasts != '\0')
        *lasts++ = '\0';
    return s;
}

void stampa_tokens(char *s)
{
  char *t = strtok(s,":;., ");
  char *t2 = my_strtok(s,":;., ");
  while(t!=NULL) {
    puts(t);
    puts(t2);
    t = strtok(NULL,":;., ");
    t2 = my_strtok(NULL,":;., ");
  }
  puts("-----------");
}  


int main(int argc, char *argv[])
{
  // controlla numero argomenti
  if(argc!=2) {
      printf("Uso: %s stringa\n",argv[0]);
      return 1;
  }
  stampa_tokens(argv[1]);
  return 0;
}
