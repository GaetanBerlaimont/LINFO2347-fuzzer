#ifndef SRC_TEST_H
#define SRC_TEST_H
#include "util.h"


/**
 * This test checks if the extractor can handle large length values and
 * if it crashes or shows unexpected behavior when processing such values
 * in the len field. It tests this with a set of random large length values
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_name1(char *argv[], int fd, struct tar_t *header);

/**
 *
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_name2(char *argv[], int fd, struct tar_t *header);

/**
 * Test every possible char for every possible position for the mode field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_mode1(char *argv[], int fd, struct tar_t *header);

/**
 * Test every possible char for every possible position for the uid field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_uid1(char *argv[], int fd, struct tar_t *header);

/**
 * Test every possible char for every possible position for the gid field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_gid1(char *argv[], int fd, struct tar_t *header);

/**
 * Test every possible char for every possible position for the size field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_size1(char *argv[], int fd, struct tar_t *header);

/**
 * Test every possible char for every possible position for the mtime field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_mtime1(char *argv[], int fd, struct tar_t *header);

/**
 * Test every possible char for every possible position for the typeflag field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_typeflag1(char *argv[], int fd, struct tar_t *header);

/**
 * Test every possible char for every possible position for the linkname field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_linkname1(char *argv[], int fd, struct tar_t *header);

/**
 * Test every possible char for every possible position for the magic field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_magic1(char *argv[], int fd, struct tar_t *header);

/**
 * Test every possible char for every possible position for the version field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_version1(char *argv[], int fd, struct tar_t *header);

/**
 * Test every possible char for every possible position for the uname field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_uname1(char *argv[], int fd, struct tar_t *header);

/**
 * Test every possible char for every possible position for the gname field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_gname1(char *argv[], int fd, struct tar_t *header);

/**
 * Test an empty archive
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_0byte(char *argv[], int fd, struct tar_t *header);

/**
 * Test vulnerability related to handling large checksum values in the tar header.
 * Generates random octal numbers within maximum range
 * for a 7-character checksum and calls chksum_single_test with each value.
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_chksum_MAX_multiple(char *argv[], int fd, struct tar_t *header);

/**
 * This function tests vulnerability for handling very long checksum strings in the tar header.
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_chksum_field_overflow(char *argv[], int fd, struct tar_t *header);

/**
 * Same as "test_size1" but this time with 2 files with data, try every char value for every position AND reset to '0' when passing
 * to the next index to ensure that we can test the case with short size as '00000000001'
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_medium_size1(char *argv[], int fd, struct tar_t *header);

/**
 * Test an archive with 2 files by writing with (possible) non-ASCII character to both of them.
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_medium_nonASCII_data(char *argv[], int fd,  struct tar_t *header);

/**
 * Test an archive with a ".txt" file and a simbolic link that point to itself first,
 * and then test with every char value in the field linkname for that simbolic link.
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_linked_linkname(char *argv[], int fd, struct tar_t *header);

/**
 * Test an archive with a folder who has a non-null size with some data
 * and
 * Test by writing data in the end padding field
 * @param argv contains the extractor name as first argument
 * @param fd file descriptor
 * @param header pointer to a header structure
 *
 */
void test_dir_adding_data(char* argv[], int fd, struct tar_t *header);


#endif //SRC_TEST_H
