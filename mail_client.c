

#include "client_global_header.h"
#include "client_services.h"


void mail_client( char *ip, int port ) {


/*******************************
 * Local Variable Declaration
 *******************************/

	int len;
	struct sockaddr_in server_addr;


/*****************************************************
 * Get a socket to work with. This socket will be
 * in the UNIX domain, and will be a stream socket.
 *****************************************************/

	if ( (sd_client = socket(AF_INET, SOCK_STREAM, 0) ) < 0) {

		perror("client: socket's failure" );
		exit(1);
	}

/***********************************************
 * Create the address we will be binding to.
 ***********************************************/

	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family      = AF_INET;
	server_addr.sin_port        = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip);

/**********************************************************
 * Try to connect to the address. For this to succeed,
 * the server must already have bound this address,
 * and must have issued a listen() request.
 *
 * The third argument indicates the "length" of the
 * structure, not just the length of the socket name.
 **********************************************************/


	
	if ( connect(sd_client, (struct sockaddr *)&server_addr, sizeof(server_addr))  < 0 ) {

		perror("client: cannot connect" );
		exit(1);
	}

	shell();

	close(sd_client);



exit(1);

}



int main( int argc, char **argv ) {
	
	system("clear");
	printf("\n( Press HELP to see your choices )\n\n");
	
	mail_client( argv[1], atoi(argv[2]) );
	
	return 0;
}

