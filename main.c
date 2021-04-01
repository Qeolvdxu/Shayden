#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

void tokenizer(char* string, char* delim, const char** token)
{
	char* temp = strtok(string, delim);

	int i;
	for (i = 0; temp != NULL; i++)
	{
		token[i] = temp;
		temp = strtok(NULL,delim);
	}
	token[i] = "0";

}

int main(void)
{
	int i;

	int check;

	int status;

	pid_t pid;

	char* token; 

	char* input; 

	char PS1[100] = "$"; 

	const char* pathTokens[10] = {NULL};
	tokenizer(getenv("PATH"),":",pathTokens);
	char tempPaths[10][10] = {NULL};

	int nargc;
	char* nargv[100];

	FILE *inFile;
	FILE *outFile;
	char fileReader;

/* Loops runs the whole time the shell is running */
	while(1)
	{
/* Collect and Break up user input */
		printf("\n%s ",PS1);
		scanf(" %[^\n]",input);
		token = strtok(input, " ");

/* Commands */
		if(!strcmp(token,"exit"))
			exit(0);


	/* Print out the commands input */
		else if(!strcmp(token,"echo"))
		{
			if ( (token = strtok(NULL, " ")) != NULL)
			{
				if (!strcmp(token, "-n"))
				{
					token = strtok(NULL, "-");
					printf("\r%s",token);
				}
				else if(token != NULL)
				{	
					printf("%s ",token);
					token = strtok(NULL, "-");
					fflush(stdout);
					if (token != NULL)
						printf("%s\n",token);
					else
						printf("\n");
				}
			}
			else
			 printf("Echo returns its given values.\nExample: \"echo test test\" returns \"test test\"\nThe flag -n return the values on the same line\n");
		}


	/* Set the PS1 variable */
		else if(!strcmp(token,"PS1"))
		{	
			if ( (token = strtok(NULL, "-")) != NULL)
				strcpy(PS1, token);
			else
				printf("Please specify the string for PS1");
		}


	/* Print the contents of a specific file */
		else if(!strcmp(token,"cat"))
		{
			if ( (token = strtok(NULL, " ")) != NULL)
			{
					inFile = fopen(token,"r");
					while ((fileReader=fgetc(inFile)) != EOF)
						printf("%c",fileReader);
					fclose(inFile);
			}
			else
				printf("Please enter the file you want the contents of returned to you\n");
		}


	/* Copy a specific file */
		else if(!strcmp(token,"cp"))
		{
			if ( (token = strtok(NULL, " ")) != NULL)
			{
					inFile = fopen(token,"r");

					if ( (token = strtok(NULL, " ")) != NULL)
					{
							remove(token);
							outFile = fopen(token,"w");

							while ((fileReader=fgetc(inFile)) != EOF)
								fputc (fileReader, outFile);

							fclose(inFile);
							fclose(outFile);
					}
					else
						printf("Please supply the name of the destination file\n");	
			}
			else
				printf("Please supply the name of the source file\n");	

		}


	/* Remove a specific file */
		else if(!strcmp(token,"rm"))
		{
			if ( (token = strtok(NULL, " ")) != NULL)
			{
					check = remove(token);
					if(!check)
						printf("%s removed correctly\n", token);
					else
						printf("could not remove file: %s\n", token);
			}
			else
				printf("Please supply the name of the file you want to remove\n");
		}


	/* Create a directory */
		else if(!strcmp(token,"mkdir"))
		{
			if ( (token = strtok(NULL, " ")) != NULL)
			{	
					check = mkdir(token, 0777);
					if(!check)
						printf("%s created correctly\n", token);
					else
						printf("could not create directory: %s\n", token);
			}
			else
				printf("Please supply the name of the directory you want to create\n");
		}



	/* Remove a specific directory */
		else if(!strcmp(token,"rmdir"))
		{
			if ( (token = strtok(NULL, " ")) != NULL)
			{
					check = rmdir(token);
					if(!check)
						printf("%s removed directory correctly\n", token);
					else
						printf("could not remove directory: %s\n", token);
			}
			else
				printf("Please supply the name of the directory you want to remove\n");
		}



	/* Exectute a external application */
		else if(!strcmp(token,"exec"))
		{
			if ((token = strtok(NULL, " ")) != NULL)
			{
				if (token[0] == '.' || token[0] == '/')
				{
				/*	 Execute Child Process  */
					pid = fork();
					if (pid == -1)
						printf("FORKING ERROR!\n");
					else if (pid > 0)
						waitpid(pid, &status, 0);
					else if ( execv(token, NULL) == -1)
						printf("%s command does not exist\n",nargv[0]);
				}
				else
				{
		
					for (i = 0; i < 10 && pathTokens[i] != NULL && pathTokens[i] != '0'; i++)
					{	
						strcpy(tempPaths[i],pathTokens[i]);
						strcat(tempPaths[i],"/");
						strcat(tempPaths[i],token);

					/*	 Execute Child Process  */
						pid = fork();
						if (pid == -1)
							printf("FORKING ERROR!\n");
						else if (pid > 0)
							waitpid(pid, &status, 0);
						else
							execv(tempPaths[i], NULL);
					}
					printf("%s command does not exist\n",token);
		
				}
			
			}
			else 
				printf("Enter a command to execute\n");
		}
	}
	
	free(tempPaths);
	return 0;	
}
