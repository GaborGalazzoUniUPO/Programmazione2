CFLAGS=-g -Wall -O -std=c99 -pedantic

tutti: conta_uni converti scrivi_interi leggi_interi

%: %.c 
	gcc $(CFLAGS) -o $@ $?
	
clear: 
	rm conta_uni converti scrivi_interi leggi_interi print_persona save_persona