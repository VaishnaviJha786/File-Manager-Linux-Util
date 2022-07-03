#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void unnamedpipe()
{
	int fds[2];

	pipe(fds);

	char buff[512];

	int nw, nr;
	do
	{
		printf("Input: ");
		scanf("%s", buff);
		nw = write(fds[1], buff, 512);

		if (nw <= 0)
		{
			printf("\nError! While wrting the pipe");
			return;
		}

		nr = read(fds[0], buff, 512);
		if (nr <= 0)
		{
			printf("\nError! While reading the pipe");
			return;
		}

		printf("Output: %s\n", buff);

	} while (strcmp(buff, "#") != 0);
}
