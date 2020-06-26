#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[], char **envp)
{
	
	char *path;

	path = getenv("PATH");
	printf("Actual PATH : %s\n", path);

	char new_path[100] = "/usr/local/bin:/sbin:/bin:/usr/bin";
	setenv("PATH", new_path, 1);

	path = getenv("PATH");
	printf("New PATH :%s\n", path);

	putenv("PATH=.:maher:/usr/bin");



	for(char ** envp_i = envp; *envp_i; envp_i++)
	{
		printf("%s\n", *envp_i);
	}



	return 0;
}
