# File Manager Command Line Tool

File Manager is a command line tool, designed to operate on basic input/output/info operations on files, including and limited to named pipes, unnamed pipes, regular files on UNIX System.

Operations allowed:

1. Create
2. Read
3. Write
4. Info

## Pre-requisites

First compile the code to make the executable file

```
gcc file_manager.c -o file_manager
```

## Usage

To run the tool

```
./file_manager <file-type> <file-name> <mode>
```

<br><br>

### file-type

The allowed file-types are

1. Unnamed Pipe- "unnamed-pipe"
2. Named Pipe- "named-pipe"
3. Normal File- "file"
<br><br>

### file-name

User-defined name for named pipes and regular files. (Not required in case of unnamed pipes).
<br><br>

### mode

1. create- Allows creation of named pipes and  regular files.
2. read- Allows to read from a named pipe and a regular file.
3. write- Allows to write to a named pipe and a regular file.
4. info- Displays the info about the named pipe and regular file.

Note: These operations are not allowed in case of unnamed pipes.
<br><br>

## Example

```
./file_manager named-pipe create fifo1 
```

```
./file_manager file f1.txt read
```

```
./file_manager unnamed-pipe 
```

## About Tool

The tool consists of 3 header files "namedpipe.h", "unnamedpipe.h", "file.h" and the driver code "file_manager.c".
<br>
<br>

### namedpipe.h

Deals with the opeartion oriented to named pipes, i.e. creation, read, write, info.
<br><br>

### unnamedpipe.h

Creates a unnamedpipe, which takes input from the user and generates the output on the console.
<br> <br>

### file.h

Deals with the opeartion oriented to regular files, i.e. creation, read, write, info.

## Creator

Vaishnavi Jha, M.Sc. 1st Year (2021-23)
Department of Computer Science, University of Delhi
