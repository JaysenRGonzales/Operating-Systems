//Author: Jaysen Gonzales JRG301
#include <stdio.h>
#include <string.h> 


main()

{

char *iPath, *oPath, *argv[20], buf[80], n, *p;

int m, status, inword, continu;

//process identification 
pid_t pid;
int pipes, counter;

int leftPipe[2], rightPipe[2];

//if flag = 1 true, flag = 0 false
int inputFlag,outFlag;

//arguments storage max 20 arguments specified by argv
int argumentArray[20] = { 0 };


while(1) {

	inword = counter = pipes = pid = 0;

	p = buf;
	m = 0;
	continu=0;

    inputFlag = outFlag = 0;

	printf( "\nshhh> ");

	while ( ( n = getchar() ) != '\n'  || continu ) {

		if ( n ==  ' ' ) { 

			if ( inword ) {

				inword = 0;

				*p++ = 0;

			} 

		}

		else if ( n == '\n' ) continu = 0;

		else if ( n == '\\' && !inword ) continu = 1;

		else {

			if ( !inword ) {

				inword = 1;

				argv[m++] = p;

				*p++ = n;

			}

			else 

				*p++ = n;

		}

	}	

	*p++ = 0;

	argv[m] = 0;
    
	//No arguments EXIT
	if ( strcmp(argv[0],"quit") == 0 ) exit (0);


	// Redirection Handler
	while(argv[counter] =! 0)
	{
		if (strcmp(argv[counter], "|") == 0) {
            argv[counter] = 0;
            argumentContainer[pipes + 1] = counter + 1;
            ++pipes;
        }
		else if (strcmp(argv[counter], ">") == 0) {
            oPath = strdup(argv[counter + 1]); 
            argv[counter] = 0;
            argv[counter + 1] = 0;
            outFlag = 1;
		}
        else if (strcmp(argv[counter], "<") == 0) {
            iPath = strdup(argv[counter + 1]); 
            argv[counter] = 0;
            argv[counter + 1] = 0;
            inputFlag = 1;
        }
        
        else {
            argumentArray[counter] = counter;
        }

        ++counter;	
		 
	}



	if ( fork() == 0 ){

		execvp( argv[0], argv );

		printf ( " didn't exec \n ");

	}



	wait(&status);
	

}//while 1 

}//main
