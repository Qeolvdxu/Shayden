#include <stdio.h>
#include <string.h>

int main(void)
{
	int running = 1;

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
			 printf("Echo returns its given values.\n 
				    Example: \"echo test test\" returns \"test test\"\n
			        the flag -n return the values on the same line");
		}


		else if(!strcmp(token,"PS1"))
		{	
			token = strtok(NULL, "-");
			strcpy(PS1, token);
		}


		else if(!strcmp(token,"cat"))
		{
			token = strtok(NULL, " ");
			inFile = fopen(token,"r");
			while ((fileReader=fgetc(inFile)) != EOF)
				printf("%c",fileReader);
			fclose(inFile);
		}



		else if(!strcmp(token,"cp"))
		{
			token = strtok(NULL, " ");
			inFile = fopen(token,"r");

			token = strtok(NULL, " ");
			remove(token);
			outFile = fopen(token,"w");

			while ((fileReader=fgetc(inFile)) != EOF)
				fputc (fileReader, outFile);

			fclose(inFile);
			fclose(outFile);

		}



		else if(!strcmp(token,"rm"))
		{
			token = strtok(NULL, " ");
			remove(token);
		}



		else
			printf("%s: Command Not Found!\n",token);
	}
	
}
