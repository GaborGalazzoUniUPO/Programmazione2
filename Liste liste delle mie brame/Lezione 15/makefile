CFLAGS=-g -O -Wall -pedantic -std=c99
EXECS=ordina

tutti: $(EXECS)

% : %.c
	gcc $(CFLAGS) -o $@ $^
	
clean:
	rm $(EXECS)
	