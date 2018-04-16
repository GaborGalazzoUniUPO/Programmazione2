CFLAGS=-g -Wall -O -std=c99 -pedantic

tutti: insertion_sort insertion_sort_string coppia

%: %.c 
	gcc $(CFLAGS) -o $@ $?
	
clear: 
	rm conta_uni converti scrivi_interi leggi_interi print_persona save_persona