#include "client_global_header.h"
#include "shell.h"
#include "client_services.h"


struct commandTable *initializeCmds() {

	struct commandTable *command = (struct commandTable *)calloc( 1, sizeof(struct commandTable) ); 


	strcpy( command->user, "USER" );
	strcpy( command->pass, "PASS" );
	strcpy( command->stat, "STAT" );
	strcpy( command->list, "LIST" );
	strcpy( command->dele ,"DELE" );	
	strcpy( command->retr, "RETR" );
	strcpy( command->help, "HELP" );	
	strcpy( command->quit, "QUIT" );


return command;
}


void shell() {


	int num;  
	int choice;

	int i, j; 

	char *buffer     = (char *) malloc ( 32 * sizeof(char) );
	char *command    = (char *) malloc ( 32 * sizeof(char) );
	char *argument   = (char *) malloc ( 32 * sizeof(char) );

	struct commandTable *cmd = initializeCmds();



		while(1) {

			prompt();
			
			memset( command   , '\0', 32 );				/* Initializes all local variables which used to */
			memset( argument  , '\0', 32 );				/* manipulate the interaction with the user.     */
			memset( buffer    , '\0', 32 );
			
			
			choice = 1;
			num    = 0;
			j      = 0;
			

			fgets( buffer, 32, stdin );					/* gets user's command from keyboard */
			
			buffer[strlen(buffer)-1] = '\0';
			
			
			
		        while( choice != 3 ) {						/* separates command and argument(s) if exists */
															/* and stores them in different variables to   */
															/* be easily manipulated.                      */
			
                		switch( (int)choice ) {
			
			
                                		case 1:
                                        		for( i=0; (buffer[i] != ' ') && (i < strlen(buffer)); i++ ) 
                                                			command[i] = buffer[i];
			
												j = i+1;
			
		                                        while( buffer[j] == ' ' )
                		                                j++;
			
                                		        choice = 2;
												break;
			
										case 2:
												for( i=j;  buffer[i] != ' ' && i<strlen(buffer); i++ ) 
															argument[i-j] = buffer[i];
							
												j = i+1;
									
												while( buffer[j] == ' ' )
													j++;

												choice = 3;                                        
												break;

										default:
												printf("\nERR : on communucation with the user.\n");
												break;
				}

        	}



		num = numOfArgs( argument );				/* Counts the number of command's argument */

				


				if( num == 0 ) {		/* Commands with no arguments executed here */

                                        if( memcmp( cmd->stat, command, 4 ) == 0 )
                                                ask_stat();
                                        else if( memcmp( cmd->list, command, 4 ) == 0 )
                                                ask_list();
                                        else if( memcmp( cmd->help, command, 4 ) == 0 )
                                                help();
                                        else if( memcmp( cmd->quit, command, 4 ) == 0 ) {
                                                ask_quit();
						break;
					}
                                        else
                                            printf("Command -%s not found.\n", command);
                                }
                                
				if( num == 1 ) {		/* Commands with one argument executed here */
											
										if( memcmp( cmd->user, command, 4 ) == 0 )
											ask_name( argument );
										else if( memcmp( cmd->pass, command, 4 ) == 0 )
											ask_pass( argument );
										else if( memcmp( cmd->dele, command, 4 ) == 0 )
											ask_dele( atoi( argument ) );
										else if( memcmp( cmd->retr, command, 4 ) == 0 )
											ask_retr( atoi( argument ) );
										else
											printf("Command -%s not found.\n", command);					
				}	
				

			
			}
	
	

}


void prompt() {

	printf("\n>> ");
}


int numOfArgs( char *arg1 ) {		/* Counts the number of arguments that command have */
									/* and returns its value                            */
int num = 0;


	if( (arg1[0] != ' ') && (arg1[0] != '\n') && (arg1[0] != '\0') )
		num++;

return num;
}

