#ifndef    GLOBAL_HEADER_H
#define    GLOBAL_HEADER_H 



#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#include   <sys/wait.h>


#include <fcntl.h>
#include <sys/stat.h>
#include <arpa/inet.h>





#define 	SOCK_NAME	 "socket"		 /* address to connect */





/***********************************
 * GLOBAL VARIABLES
 ***********************************/



	int sd_client;			/* Client's Socket descriptor */




/***************************************
 * FUNCTION PROTOTYPE DECLARATION
 ***************************************/



	void mail_client( char *, int );
	
	

#endif
