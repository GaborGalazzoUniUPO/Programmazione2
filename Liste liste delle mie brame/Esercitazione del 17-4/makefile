EXECS=squadra
CFLAGS=-O -p -g -pedantic -Wall -std=c99

tutti: $(EXECS)

% : %.c
	gcc $(CFLAGS) -o $@ $?

clean:
	rm $(EXECS)