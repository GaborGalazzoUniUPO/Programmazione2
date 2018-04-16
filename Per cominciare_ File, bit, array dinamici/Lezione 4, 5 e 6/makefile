# Il comando make cerca di realizzare il primo target (tutti)
# La linea "tutti: primo primi" dice a make che tutti dipende
# da primo e primi e quindi il make provvedera' ad eseguire
# i comandi di compilazione

# opzioni di compilazione le definisco qui una volta per tutte
CFLAGS=-g -Wall -O -std=c99


tutti: caratteri bits scrivi_bits leggi_bits

scrivi_bits: scrivi_bits.c
	gcc $(CFLAGS) -o scrivi_bits scrivi_bits.c

leggi_bits: leggi_bits.c
	gcc $(CFLAGS) -o leggi_bits leggi_bits.c

bits: bits.c
	gcc $(CFLAGS) -o bits bits.c

caratteri: caratteri.c
	gcc $(CFLAGS) -o caratteri caratteri.c


clean:
	rm bits caratteri scrivi_bits leggi_bits
