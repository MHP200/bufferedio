/**************************************************************
* Class: CSC-415-03 Spring 2023
* Name: Mahdi Hassanpour
* Student ID: 922278744
* GitHub UserID: MHP200
* Project: Assignment 5 – Buffered I/O
*
* File: b_io.c
*
* Description:
*
*This assignment is to handle the input and output when
*we are doing the buferring. We will use the provide
*Skeleton code frame to writeing three function:
*b_io_fd b_open (char * filename, int flags);
*int b_read (b_io_fd fd, char * buffer, int count);
*int b_close (b_io_fd fd);
**************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "b_io.h"
#include "fsLowSmall.h"
#include "stdbool.h"

#define MAXFCBS 20 // The maximum number of files open at one time

// This structure is all the information needed to maintain an open file
// It contains a pointer to a fileInfo strucutre and any other information
// that you need to maintain your open file.
typedef struct b_fcb
{
	fileInfo *fi; // holds the low level systems file info

	char *fileReaderBuffer;

	int currentBufferPosition;

} b_fcb;

// static array of file control blocks
b_fcb fcbArray[MAXFCBS];

// Indicates that the file control block array has not been initialized
int startup = 0;

// Method to get a free File Control Block FCB element
b_io_fd b_getFCB()
{
	for (int i = 0; i < MAXFCBS; i++)
	{
		if (fcbArray[i].fi == NULL)
		{
			fcbArray[i].fi = (fileInfo *)-2; // used but not assigned
			return i;						 // Not thread safe but okay for this project
		}
	}

	return (-1); // all in use
}

// b_open is called by the "user application" to open a file.  This routine is
// similar to the Linux open function.
// You will create your own file descriptor which is just an integer index into an
// array of file control blocks (fcbArray) that you maintain for each open file.

b_io_fd b_open(char *filename, int flags)
{

}
// b_read functions just like its Linux counterpart read.  The user passes in
// the file descriptor (index into fcbArray), a buffer where thay want you to
// place the data, and a count of how many bytes they want from the file.
// The return value is the number of bytes you have copied into their buffer.
// The return value can never be greater then the requested count, but it can
// be less only when you have run out of bytes to read.  i.e. End of File
int b_read(b_io_fd fd, char *buffer, int count)
{
	//*** TODO ***:
	// Write buffered read function to return the data and # bytes read
	// You must use LBAread and you must buffer the data in B_CHUNK_SIZE byte chunks.

	if (startup == 0)
		b_init(); // Initialize our system

	// check that fd is between 0 and (MAXFCBS-1)
	if ((fd < 0) || (fd >= MAXFCBS))
	{
		return (-1); // invalid file descriptor
	}

	// and check that the specified FCB is actually in use
	//*** TODO ***:  Release any resources
	if (fcbArray[fd].fileReaderBuffer)
	{
		free(fcbArray[fd].fileReaderBuffer);
	}
	fcbArray[fd].fileReaderBuffer = NULL;
	fcbArray[fd].fi = NULL;
}
