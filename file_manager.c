#include <stdio.h>
#include <string.h>
#include "namedpipe.h"
#include "file.h"
#include "unnamedpipe.h"

void help();

int main(int argc, char *argv[])
{
	if (argc == 2 && strcmp("unnamed-pipe", argv[1]) != 0)
	{
		printf("%s", "\nPlease enter the arguments in following form for the unnamed pipe.");
		printf("%s", "\n./file_manager unnamed-pipe");
		printf("%s", "\nRead the following documentation for more details.\n");
		help();
		return -1;
	}
	if (argc != 4)
	{
		printf("%s", "\nPlease enter the arguments in following form.");
		printf("%s", "\n./file_manager <file-type> <file-name> <mode>");
		printf("%s", "\nRead the following documentation for more details.\n");
		help();
		return -1;
	}

	if (strcmp("named-pipe", argv[1]) == 0)
	{
		printf("\n---------------------------module named-pipe start-------------------------------\n\n");
		named_pipe(argv[2], argv[3]);
		printf("\n\n----------------------------module named-pipe end--------------------------------\n\n");
	}
	else if (strcmp("file", argv[1]) == 0)
	{
		printf("\n---------------------------module file start-------------------------------\n\n");
		file(argv[2], argv[3]);
		printf("\n\n----------------------------module file end--------------------------------\n\n");
	}
	else if (strcmp("unnamed-pipe", argv[1]) == 0)
	{
		printf("\n---------------------------module unnamed-pipe start-------------------------------\n\n");
		unnamedpipe();
		printf("\n\n----------------------------module unnamed-pipe end--------------------------------\n\n");
	}
	else
	{
		printf("\nNot known file-type. Visit documentation for more details.");
		help();
	}

	return 0;
}

void help()
{
	int fd = open("cheat-sheet.txt", O_RDONLY);
	char c;
	while (read(fd, &c, 1))
	{
		printf("%c", c);
	}
}
