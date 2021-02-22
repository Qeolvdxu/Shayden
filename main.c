#include <stdio.h>
#include <string.h>

int main(void)
{
	int running = 1;

	char* token; 
	char* input; 

	char* PS1; 
//	PS1 = "$ ";

	int i;

// Loops runs the whole time the shell is running
	while(running == 1)
	{
// Collect and Break up user input
//		printf("%s ",PS1);
		scanf(" %[^\n]",input);
		token = strtok(input, " ");

// Commands
		if(!strcmp(token,"exit"))
			running = 0;
		else if(!strcmp(token,"echo"))
		{
			token = strtok(NULL, "-");
			printf("%s\n",token);
		}
		else if(!strcmp(token,"PS1"))
		{
				
		}
		else
			printf("%s: Command Not Found!\n",token);
	}
	
}
