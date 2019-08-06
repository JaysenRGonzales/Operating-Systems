//Author: Jaysen Gonzales JRG301
#include <stdio.h>
#include <string.h> 
#include<stdlib.h>    //For Exit()
#include <unistd.h>   //For fork()
#include <fcntl.h>    //For O_RDWR 


int main()

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
	if ( strcmp(argv[0],"exit") == 0 ) exit (0);


	// Redirection Handler
	while(argv[counter] != 0)
	{
		//pipe'|'
        if (strcmp(argv[counter], "|") == 0) 
        {
            argv[counter] = 0;
            argumentArray[pipes + 1] = counter + 1;
            ++pipes;
        }
            //output direction
        else if (strcmp(argv[counter], ">") == 0) 
        {
            oPath = strdup(argv[counter + 1]); 
            argv[counter] = 0;
            argv[counter + 1] = 0;
            outFlag = 1;
        }
            //input direction
        else if (strcmp(argv[counter], "<") == 0) 
        {
            iPath = strdup(argv[counter + 1]); 
            argv[counter] = 0;
            argv[counter + 1] = 0;
            inputFlag = 1;
        }
        else 
        {
            argumentArray[counter] = counter;
        }

        ++counter;	
		 
	}

        
	int loop;  //variable for 'for' loop, for loop declaration invalid
 
	for (loop = 0; loop <= pipes; loop++){
        if(pipes > 0 && loop != pipes)
        {
            pipe(rightPipe);
        }
        
        //create new process
        pid = fork();

        // child creation was unsuccessful
        if(pid < 0){

            printf("unsucccesful child creation");
        }
        
        //child process was successful 
 	else if(pid == 0)
        {
            //creating input file
            if ((loop == 0) && (inputFlag == 1))
            {
                int inputFile = open(iPath, O_RDONLY, 0400);
                if (inputFile == -1)
                {
                    printf("input file failed\n");
                    
                }
                close(0);
                dup(inputFile);
                close(inputFile);
            }
                    
            if (pipes > 0)
            {
                if (loop == 0)
                {
                    close(1);
                    dup(rightPipe[1]);
                    close(rightPipe[1]);
                    close(rightPipe[0]);
                }
                else if (loop < pipes)
                {
                    close(0);
                    dup(leftPipe[0]);
                    close(leftPipe[0]);
                    close(leftPipe[1]);
                    close(1);
                    dup(rightPipe[1]);
                    close(rightPipe[0]);
                    close(rightPipe[1]);
                }
                else
                {
                    close(0);
                    dup(leftPipe[0]);
                    close(leftPipe[0]);
                    close(leftPipe[1]);
                }
            }
            //creaitng a output file 
            if ((loop == pipes) && (outFlag == 1))
            {
                int outputFile = creat(oPath, 0700);
                if (outputFile < 0)
                {
                    printf("output file failed.\n");
                }
                close(1);
                dup(outputFile);
                close(outputFile);
            }
            //command couldnt be read            
            execvp(argv[argumentArray[loop]], &argv[argumentArray[loop]]);
            printf("command failed !\n");
        }
        //parent process
        else{             
            if (loop > 0)
            {
                close(leftPipe[0]);
                close(leftPipe[1]);
            }
            leftPipe[0] = rightPipe[0];
            leftPipe[1] = rightPipe[1];

            wait(&status);

                
            }
        }
}
	
}//while 1 


