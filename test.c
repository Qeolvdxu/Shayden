#include <dirent.h> /* For DIR and struct dirent */
#include <stdio.h>
 
int main(int argc, char **argv) 
{
	printf("%d",argc);

	DIR *dir; /* Returned by opendir */
	struct dirent *direntry; /* Returned by readdir */
 
	if (argc > 1)
		dir = opendir(argv[1]);

	closedir(dir);
 
	return 0;
}
