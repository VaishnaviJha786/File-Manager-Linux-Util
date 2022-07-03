#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// function declarations

void create_file(char *file_name);
void read_file(char *file_name);
void write_file(char *file_name);
void info_file(char *file_name);

// driver code

void file(char *file_name, char *mode)
{

	if (strcmp(mode, "create") == 0)
	{
		create_file(file_name);
	}
	else if (strcmp(mode, "write") == 0)
	{
		write_file(file_name);
	}
	else if (strcmp(mode, "read") == 0)
	{
		read_file(file_name);
	}
	else if (strcmp(mode, "info") == 0)
	{
		printf("\nInfo of the file:");
		info_file(file_name);
	}
	else
	{
		printf("Wrong Mode Selected");
	}
}

// function definitions

void create_file(char *file_name)
{
	int fd;
	int access_check = access(file_name, F_OK);
	if (access_check == 0)
	{
		printf("\nFile with the name: %s already exists. \nPlease try a different name or use this one in future.", file_name);

		return;
	}

	int cr = creat(file_name, O_RDWR | S_IRWXU | S_IRWXG | S_IRWXO);

	if (cr < 0)
	{

		printf("\nError in creating the file %s.", file_name);
		return;
	}
	else
	{
		printf("\nFile %s created successfully!!!", file_name);
	}
	close(cr);
}

void write_file(char *file_name)
{
	int fd;
	int access_check = access(file_name, F_OK);
	if (access_check != 0)
	{
		printf("\nFile %s doesn't exists, please create one before.", file_name);
		return;
	}

	access_check = access(file_name, W_OK);
	if (access_check != 0)
	{
		printf("\nFile %s doesn't have write access.", file_name);
		return;
	}
	printf("\nEnter the option in which you want to write to the file:");
	printf("\n[1] Truncate");
	printf("\n[2] Append");
	printf("\n[3] Overwrite(Default)\n");

	int choice;
	int flag = O_WRONLY;
	scanf("%d", &choice);

	if (choice == 1)
		flag = flag | O_TRUNC;
	else if (choice == 2)
		flag = flag | O_APPEND;
	else if (choice == 3)
		flag = O_WRONLY;
	else
	{
		printf("\nEnter correct choice");
		printf("\nUsing Default option");
	}

	fd = open(file_name, flag);
	if (fd < 0)
	{

		printf("\nError opening the file %s in write mode", file_name);
		return;
	}

	int nw;
	printf("\nEnter the contents to be written in the file (Press # to stop writing)\n");
	char c;
	scanf("%c", &c);
	while (c != '#')
	{

		nw = write(fd, &c, 1);
		scanf("%c", &c);

		if (nw <= 0)
		{
			printf("%s", "\nError! While writing the file");
			close(fd);
			return;
		}
	}
	close(fd);
}

void read_file(char *file_name)
{
	int fd;
	int access_check = access(file_name, F_OK);
	if (access_check != 0)
	{
		printf("\nFile %s doesn't exists, please create one before", file_name);
		return;
	}

	access_check = access(file_name, R_OK);
	if (access_check != 0)
	{
		printf("\nFile %s doesn't have read access", file_name);
		return;
	}

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{

		printf("\nError opening the file %s in read mode.", file_name);
		return;
	}

	int offset = 0;
	int lk = 0;
	printf("\nEnter the offset from which to read the file(Press 0 to read from start): ");
	scanf("%d", &offset);
	lk = lseek(fd, offset, SEEK_CUR);
	// printf("Output of lseek %d", lk);
	if (lk == -1)
	{

		printf("\nError!! While jumping the offset %d.", offset);
		printf("\nReading from starting of the file");
		lk = lseek(fd, 0, SEEK_SET);
	}

	char c;
	int nr;
	printf("\nContents of the file:\n");
	do
	{
		nr = read(fd, &c, 1);
		if (nr < 0)
		{
			printf("\nFile either ended or encountered an  error.");
			close(fd);
			return;
		}

		printf("%c", c);

	} while (nr > 0);
	close(fd);
}

void info_file(char *file_name)
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
