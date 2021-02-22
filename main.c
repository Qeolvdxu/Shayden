#include <stdio.h>
#include <string.h>

int main(void)
{
	int running = 1;

	int check;

	char* token; 
	char* input; 

	char PS1[100] = "$"; 

	FILE *inFile;
	FILE *outFile;
	char fileReader;

	int i;

/* Loops runs the whole time the shell is running */
	while(running == 1)
	{
/* Collect and Break up user input */
		printf("%s ",PS1);
		scanf(" %[^\n]",input);
		token = strtok(input, " ");

/* Commands */
		if(!strcmp(token,"exit"))
			running = 0;



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
						printf("\n",token);
				}
			}
			else
			 printf("Echo returns its given values.\nExample: \"echo test test\" returns \"test test\"\nThe flag -n return the values on the same line\n");
		}


		else if(!strcmp(token,"PS1"))
		{	
			if ( (token = strtok(NULL, "-")) != NULL)
				strcpy(PS1, token);
			else
				printf("Please specify the string for PS1");
		}


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




		else
			printf("%s: Command Not Found!\n",token);
	}
	
}
