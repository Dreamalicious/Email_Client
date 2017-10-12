#ifndef SHELL_H
#define SHELL_H



	/*********************************
	 * * * * * * * * * * * * * * * * *                               
	 *	GLOBAL VARIABLES	         *
	 * * * * * * * * * * * * * * * * *				
	 *********************************/


	/**********************************************
	 *
	 * Variable commandTable is a struct its 
	 * members are the names of utilities that
	 * our System provides to the client. 
	 *
	 **********************************************/

	struct commandTable {
        
        	char user[5];
        	char pass[5];
        	char stat[5];
        	char list[5];
        	char dele[5];
        	char retr[5];    
        	char help[5];                                                               
        	char quit[5];
      	
	};                                                                      



	/*********************************
	 * * * * * * * * * * * * * * * * *
	 * 	FUNCTION PROTOTYPES	 *
	 * * * * * * * * * * * * * * * * *
	 *********************************/


	void shell();           
	void prompt();
	int numOfArgs( char * );
      
	struct commandTable *initializeCmds();                  




#endif



