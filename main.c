#include <stdio.h>
#include <string.h>

int main(void)
{
	int running = 1;

	char* token; 
	char* input; 

	char PS1[100] = "$"; 

	FILE *inFile;
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
			token = strtok(NULL, " ");
			if (!strcmp(token, "-n"))
			{
				token = strtok(NULL, "-");
				printf("\r%s",token);
			}
			else
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



		else
			printf("%s: Command Not Found!\n",token);
	}
	
}
