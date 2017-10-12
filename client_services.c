#include "client_services.h"
#include "client_global_header.h"




/************************************************************
 * 
 * help() fuction provides help to client...
 * 
 * **********************************************************/

void help() {
	
	
	printf("\n===================================\n\n");
	
	printf("I.    USER <username>\n");
	printf("II.   PASS <password>\n");
	printf("III.  STAT\n");
	printf("IV.   LIST\n");
	printf("V.    DELE <email number>\n");
	printf("VI.   RETR <email number>\n");
	printf("VII.  HELP\n");
	printf("VIII. QUIT\n\n");

	printf("\n===================================\n\n");

	
}


/******************************************************************
 * 
 * ask_name() takes as argument a string that contain the
 * username of client. This function send the username to 
 * server and receives a message that notifices him about
 * his apperance in the system.
 * 
 * ****************************************************************/

void ask_name( char *name ) {
	
	int ch = 2;
	
				if( write( sd_client, &ch, sizeof(int) ) < 0 ) 		
					perror("ERR < USERNAME cannot delivered >.\n");
				else {
						char mssg[3];							/* Message that client receives from server */
						memset( mssg, '\0', 3 );

						write( sd_client, name, 20 );			/* Send username to the server */
						read ( sd_client, mssg, 2  );			/* Receives server's message   */
						
						if( memcmp( mssg, "OK", 2 ) == 0 )		
							printf("\n+OK  User accepted.\n");
						else
							printf("\nUser %s does't exists.\n", name );
					
				}
	
}


/******************************************************************
 * 
 * ask_pass() takes as argument a string that contain the
 * password of client. This function send the password to 
 * server and receives a message that notifices him about
 * his apperance in the system.
 * 
 * ****************************************************************/

void ask_pass( char *pass ) {
	
	int ch = 3;
	
				if( write( sd_client, &ch, sizeof(int) ) < 0 ) 		
					perror("ERR < PASSWORD cannot delivered >.\n");
				else {
						char mssg[3];								/* Message that client receives from server */
						memset( mssg, '\0', 3 );

						write( sd_client, pass, 20 );				/* Send username to the server */
						read ( sd_client, mssg, 2  );				/* Receives server's message   */
						
						if( memcmp( mssg, "OK", 2 ) == 0 )
							printf("\n+OK  Password accepted.\n");
						else
							printf("\nPassword %s does't exists.\n", pass );
					
				}

}


/******************************************************************
 * 
 * ask_retr() takes as argument a valid number that shows
 * us the sequence number of mail that user want to read.
 * This function sends the number to server and receives
 * the mail message.
 * 
 * ****************************************************************/

void ask_retr( int num ) {
	
	
	int ch = 7;
	
	char *mail_messg = (char *)malloc( 1024 * sizeof(char) );
	char *from       = (char *)malloc( 64   * sizeof(char) );
	int size = 0;
	
	memset( mail_messg, '\0', 1024 );
	memset( from      , '\0', 64   );
	
		
				if( write( sd_client, &ch, sizeof(int) ) < 0 ) 		
					perror("ERR < PASSWORD cannot delivered >.\n");
				else {
	
						write( sd_client, &num, sizeof(int) );			/* Send mail number to the server */
						
						read( sd_client, &size, sizeof(int) );			/* Receives the size of mail   */
						read( sd_client, from      , 64     );			/* Receives the sender of mail */
						read( sd_client, mail_messg, 1024   );			/* Receives the email message  */

						printf("\n+OK  %d bytes\n", size );

						printf("\n==================================\n"  );
						printf("   M  A  I  L    R  E  T  R   #%d\n", num);

						printf("\n< %s >", from   );
						printf("\n%s", mail_messg );
						
						printf("\n==================================\n\n");
				}
				
				
free(mail_messg);	

}


/******************************************************************
 * 
 * ask_dele() takes as argument a valid number that shows
 * us the sequence number of mail that user want to delete.
 * This function sends the number to server and receives
 * a notification about procedure.
 * 
 * ****************************************************************/

void ask_dele( int num ) {
	
	int ch = 6;
	
	char *messg[3];													/* Message that client receives from server */
	
	
				if( write( sd_client, &ch, sizeof(int) ) < 0 ) 		
					perror("ERR < PASSWORD cannot delivered >.\n");
				else {
					
					memset( messg, '\0', 3 );
					write ( sd_client, &num, sizeof(int) );			/* Sends the number to the server.   */
					read  ( sd_client, messg, 2 );					/* Receives notification from server */
					
					if( memcmp( messg, "OK", 2 ) == 0 )
						printf( "\n+OK  Email #%d deleted\n", num );
					else
						printf("\nFailed to delete\n");
				}
	
}


/******************************************************************
 * 
 * ask_list() takes no arguments.
 * This function provides to the client a list with his emails.
 * 
 * ****************************************************************/

void ask_list() {
	
		int ch = 5;

		int total_numb = 0;
		int curr_size  = 0;
		int i;
		
				if( write( sd_client, &ch, sizeof(int) ) < 0 )
					perror("ERR <> Communication problem <>.\n>");
				else {
				
					read( sd_client, &total_numb, sizeof(int) );		/* Receives the number from server. */
					
					printf("\n+OK  %d emails\n", total_numb );

					printf("\n==================================\n"  );
					printf("   M  A  I  L    L  I  S  T   #%d\n\n", total_numb);
				
					for( i=0; i<total_numb; i++ ) {
						
						read( sd_client, &curr_size, sizeof(int) );		/* Receives mail's size. */
						printf("\t#%d %d bytes\n", i+1, curr_size);
					
					curr_size = 0;	
					}	
					
					printf("\n==================================\n"  );
					
			}
				
	
}


/******************************************************************
 * 
 * ask_stat() takes no arguments.
 * This function provides to the client the knowledge of actual
 * size of total number of emails and total number of its size 
 * that user has stored in server's file System.
 * 
 * ****************************************************************/

void ask_stat() {
	
		int ch = 4;
		
		int total_size = 0;
		int total_numb = 0;
		
	
				if( write( sd_client, &ch, sizeof(int) ) < 0 ) 		
					perror("ERR < Communication problem >.\n");
				else {
					
					read( sd_client, &total_numb, sizeof(int) );		/* Receives the number from server. */
					read( sd_client, &total_size, sizeof(int) );		/* Receives the number from server. */
					
					printf("\n+OK  %d emails, %d bytes.\n", total_numb, total_size );
					
				}
	
}


/******************************************************************
 * 
 * ask_quit() takes no arguments.
 * Sends a notification message to server to terminate connection.
 * 
 * ****************************************************************/

void ask_quit() {

	int ch = 8;
	
	
		if( write( sd_client, &ch, sizeof(int) ) < 0 ) 		
			perror("ERR < Message didn't delivered >.\n");
		else
			printf("\n+OK client sign out.\n\n");
	  
}







void askTo_create_Account() {


	int  check_communication = 0;

	char username[20];
	char password[15];
	
	
		memset( username, '\0', 20 );
		memset( password, '\0', 15 );

		
		printf("Enter your username: ");
		scanf ("%s", username);
		
		printf("\nEnter your password: ");
		scanf ("%s", password);
		
		
		write( sd_client, username, 20 );
		write( sd_client, password, 15 );
		
		read( sd_client, &check_communication, sizeof(int) );
	
	
		
			if( check_communication == 1 )
				printf("\n+OK Account created.\n\n");
			else
				printf("\nSystem failed to create your account.\n\n");

}




