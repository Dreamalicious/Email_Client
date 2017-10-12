#!/bin/bash

CC = gcc
files = client_services.c mail_client.c shell.c
objects = client_services.o mail_client.o shell.o
CLIENT = client.out

CFLAGS = -Wall -Wextra -O3 -lrt

.PHONY: all
all: $(CLIENT)

$(CLIENT): $(objects)
	$(CC) $(CFLAGS) $(objects) -o $@

client_services.o : client_services.c client_services.h client_global_header.h
		    $(CC) -c -g client_services.c

mail_client.o	  : mail_client.c client_global_header.h client_services.h
		    $(CC) -c -g mail_client.c

shell.o		  : shell.c client_global_header.h client_services.h shell.h
		    $(CC) -c -g shell.c

.PHONY: clean
clean:
	@echo "all *.o *~ *.out files will be deleted!"
	rm -f *.o *~ *.out