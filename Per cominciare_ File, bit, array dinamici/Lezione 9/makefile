# Il comando make cerca di realizzare il primo target (tutti)
# La linea "tutti: primo primi" dice a make che tutti dipende
# da primo e primi e quindi il make provvedera' ad eseguire
# i comandi di compilazione

# opzioni di compilazione le definisco qui una volta per tutte
CFLAGS=-g -Wall -O -std=c99

EXECS=scrivi_coppie leggi_coppie coppia acoppie

tutti: $(EXECS)


scrivi_coppie: scrivi_coppie.c
	gcc $(CFLAGS) -o scrivi_coppie scrivi_coppie.c

coppia: coppia.c
	gcc $(CFLAGS) -o coppia coppia.c

acoppie: acoppie.c
	gcc $(CFLAGS) -o acoppie acoppie.c

# nelle regole di compilazione:
#  $@ viene sostituisto con il nome del target
#  $? viene sostituito con il nome delle dipendenze 
leggi_coppie: leggi_coppie.c
	gcc $(CFLAGS) -o $@ $?


clean:
	rm -f $(EXECS)
