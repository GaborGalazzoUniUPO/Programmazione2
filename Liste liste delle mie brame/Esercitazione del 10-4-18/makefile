CFLAGS=-g -Wall -O -std=c99 -pedantic

tutti: lista_citta

%: %.c 
	gcc $(CFLAGS) -o $@ $?
	
clear: 
	rm lista_citta