CC=gcc
CFLAGS= -Wall -g -O -pedantic -std=c99
EXECS= coppie ordina_coppie ordina_stringhe max_coppie

tutti: $(EXECS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(EXECS)