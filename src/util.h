#ifndef util_h 
#define util_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define NAME       0
#define MODE       1
#define UID        2
#define GID        3
#define SIZE       4
#define MTIME      5
#define TYPEFLAG   6
#define LINKNAME   7
#define MAGIC      8
#define VERSION    9
#define UNAME     10
#define GNAME     11


#define BASIC      1
#define MEDIUM     2
#define LINKED     3


struct tar_t
{                              /* byte offset */
    char name[100];               /*   0 */
    char mode[8];                 /* 100 */
    char uid[8];                  /* 108 */
    char gid[8];                  /* 116 */
    char size[12];                /* 124 */
    char mtime[12];               /* 136 */
    char chksum[8];               /* 148 */
    char typeflag;                /* 156 */
    char linkname[100];           /* 157 */
    char magic[6];                /* 257 */
    char version[2];              /* 263 */
    char uname[32];               /* 265 */
    char gname[32];               /* 297 */
    char devmajor[8];             /* 329 */
    char devminor[8];             /* 337 */
    char prefix[155];             /* 345 */
    char padding[12];             /* 500 */
};

/* Converts an ASCII-encoded octal-based number into a regular integer */
#define TAR_INT(char_ptr) strtol(char_ptr, NULL, 8)

/**
 * Launches another executable given as argument,
 * parses its output and check whether or not it matches "*** The program has crashed ***".
 * @param the path to the executable
 * @return -1 if the executable cannot be launched,
 *          0 if it is launched but does not print "*** The program has crashed ***",
 *          1 if it is launched and prints "*** The program has crashed ***".
 *
 * BONUS (for fun, no additional marks) without modifying this code,
 * compile it and use the executable to restart our computer.
 */
int launch(char* argv[]);

/**
 * Computes the checksum for a tar header and encode it on the header
 * @param entry: The tar header
 * @return the value of the checksum
 */
unsigned int calculate_checksum(struct tar_t* entry);

/**
 * close current file descriptor, make a new copy of the archive of reference
 * and pre load the first header by reading the first sizeof(struct tar_t) bytes.
 * @param fd file descriptor
 * @param header pointer to a header structure
 * @param wich_tar flag to know wich archive it need to copy
 * @return -1 if an error occurred,
 *          0 if everything went good.
 *
 */
int setup(int fd, struct tar_t *header, int wich_tar);

/**
 * try some combinations of all char value (from -128 to 127) in the current specified field, and launch the extractor.
 * The values will be tested on a header from an already opened file descriptor of a tar archive.
 * @param argc argument from main fct
 * @param argv argument from main fct
 * @param fd file descriptor
 * @param header pointer to a header structure
 * @param wich_elem some flag value to know which elemnent from the header will be tested
 * @param size maximum number of char for which_elem
 * @param reset if set to 1 will reset value of previous position to 0
 * @return -1 if an error occurred,
 *          0 if all the test performed without finding a crash for the extractor.
 *          1 if a crash for the extractor is found.
 *
 */
int fillHeader(int argc, char* argv[], int fd, struct tar_t *header, int wich_elem, int size, int reset);

#endif