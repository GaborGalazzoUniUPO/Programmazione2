# Il comando make cerca di realizzare il primo target (tutti)
# La linea "tutti: primo primi" dice a make che tutti dipende
# da primo e primi e quindi il make provvedera' ad eseguire
# i comandi di compilazione

# opzioni di compilazione le definisco qui una volta per tutte
CFLAGS=-g -Wall -O -std=c99

EXECS=persona persone

tutti: $(EXECS)


# nelle regole di compilazione:
#  $@ viene sostituisto con il nome del target
#  $^ viene sostituito con tutte le dipendenze 

# Nella regola qua sotto il carattere % svolge il ruolo di wildcard (jolly)
# e quindi dice che un qualsiasi target (ad esempio persona) dipende dal file che
# si chiama come il target con estenzione .c
# Quindi con una regola sola indichiamo che "persona" dipende da "persona.c" 
# "persone" dipende da "persone.c" e così via.  
%: %.c
	gcc $(CFLAGS) -o $@ $^


clean:
	rm -f $(EXECS)
