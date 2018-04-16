CC=gcc
CFLAGS= -Wall -g -O -pedantic -std=c99
EXECS= coppia scrivi_coppie leggi_coppie

tutti: $(EXECS)

coppia: coppia.c
	$(CC) $(CFLAGS) -o coppia coppia.c

scrivi_coppie: scrivi_coppie.c
	$(CC) $(CFLAGS) -o scrivi_coppie scrivi_coppie.c

leggi_coppie: leggi_coppie.c
		$(CC) $(CFLAGS) -o leggi_coppie leggi_coppie.c

clean:
	rm $(EXECS)