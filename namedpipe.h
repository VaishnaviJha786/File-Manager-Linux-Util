#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// function declarations

void create_pipe(char *file_name);
void read_pipe(char *file_name);
void write_pipe(char *file_name);
void info_pipe(char *file_name);

// driver code

void named_pipe(char *file_name, char *mode)
{

	if (strcmp(mode, "create") == 0)
	{
		create_pipe(file_name);
	}
	else if (strcmp(mode, "write") == 0)
	{
		write_pipe(file_name);
	}
	else if (strcmp(mode, "read") == 0)
	{
		read_pipe(file_name);
	}
	else if (strcmp(mode, "info") == 0)
	{
		printf("\nInfo of the pipe:");
		info_pipe(file_name);
	}
	else
	{
		printf("Wrong Mode Selected");
	}
}

// function definitions

void create_pipe(char *file_name)
{
	int fd;
	int access_check = access(file_name, F_OK);
	if (access_check == 0)
	{
		printf("\nPipe with the name: %s already exists. \nPlease try a different name or use this one in future.", file_name);

		return;
	}

	int mk = mknod(file_name, 010777, 0);

	if (mk < 0)
	{

		printf("\nError in creating the pipe %s.", file_name);
		return;
	}
	else
	{
		printf("\nPipe %s created successfully!!!", file_name);
	}
}

void write_pipe(char *file_name)
{
	int fd;
	int access_check = access(file_name, F_OK);
	if (access_check != 0)
	{
		printf("\nPipe %s doesn't exists, please create one before.", file_name);
		return;
	}

	access_check = access(file_name, W_OK);
	if (access_check != 0)
	{
		printf("\nPipe %s doesn't have write access.", file_name);
		return;
	}

	fd = open(file_name, O_WRONLY);
	if (fd < 0)
	{

		printf("\nError opening the pipe %s in write mode", file_name);
		return;
	}
	int nw;
	printf("\nEnter the contents to be written in the pipe (Press # to stop writing)\n");
	char c;
	scanf("%c", &c);
	while (c != '#')
	{

		nw = write(fd, &c, 1);
		scanf("%c", &c);

		if (nw <= 0)
		{
			printf("\nError! While writing the pipe");
			close(fd);
			return;
		}
	}
	close(fd);
}

void read_pipe(char *file_name)
{
	int fd;
	int access_check = access(file_name, F_OK);
	if (access_check != 0)
	{
		printf("\nPipe %s doesn't exists, please create one before", file_name);
		return;
	}

	access_check = access(file_name, R_OK);
	if (access_check != 0)
	{
		printf("\nPipe %s doesn't have read access", file_name);
		return;
	}

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{

		printf("\nError opening the pipe %s in read mode.", file_name);
		return;
	}
	char c;
	int nr;
	printf("\nContents of the pipe:\n");
	do
	{
		nr = read(fd, &c, 1);
		printf("%c", c);
		if (nr < 0)
		{
			printf("\nPipe either ended or encountered an  error.");
			close(fd);
			return;
		}

	} while (nr > 0);
	close(fd);
}

void info_pipe(char *file_name)
{
	struct stat stats;
	struct tm dt;

	if (stat(file_name, &stats) == 0)
	{
		// File permissions
		printf("\nFile access: ");
		if (stats.st_mode & R_OK)
			printf("read ");
		if (stats.st_mode & W_OK)
			printf("write ");
		if (stats.st_mode & X_OK)
			printf("execute");

		// File size
		printf("\nFile size: %ld", stats.st_size);

		// Get file creation time in seconds and
		// convert seconds to date and time format
		dt = *(gmtime(&stats.st_ctime));
		printf("\nCreated on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
			   dt.tm_hour, dt.tm_min, dt.tm_sec);

		// File modification time
		dt = *(gmtime(&stats.st_mtime));
		printf("\nModified on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
			   dt.tm_hour, dt.tm_min, dt.tm_sec);
	}
	else
	{
		printf("Unable to get file properties.\n");
		printf("Please check whether '%s' file exists.\n", file_name);
	}
}
