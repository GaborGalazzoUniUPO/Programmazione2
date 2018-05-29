# Il comando make cerca di realizzare il primo target (tutti)
# La linea "tutti: $(EXECS)" dice a make che tutti dipende
# tutti gli eseguibili e quindi il make provvedera' ad eseguire
# i comandi di compilazione

# opzioni di compilazione le definisco qui una volta per tutte
CFLAGS=-g -Wall -std=c99
LFLAGS=-lm

EXECS=tartaglia main

tutti: $(EXECS)

%.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(EXECS)
