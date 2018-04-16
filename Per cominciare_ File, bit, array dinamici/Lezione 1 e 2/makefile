# Il comando make cerca di realizzare il primo target (tutti)
# La linea "tutti: primo primi" dice a make che tutti dipende
# da primo e primi e quindi il make provvedera' ad eseguire
# i comandi di compilazione

tutti: primo primi

primi: primi.c
	gcc -g -Wall -O -std=c99 -o primi primi.c

primo: primo.c
	gcc -g -Wall -O -std=c99 -o primo primo.c
