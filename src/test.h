#ifndef SRC_TEST_H
#define SRC_TEST_H
#include "util.h"

void test_name1(char *argv[], int tar, struct tar_t *header);
void test_name2(char *argv[], int tar, struct tar_t *header);

void test_mode1(char *argv[], int tar, struct tar_t *header);

void test_uid1(char *argv[], int tar, struct tar_t *header);

void test_gid1(char *argv[], int tar, struct tar_t *header);

void test_size1(char *argv[], int tar, struct tar_t *header);

void test_mtime1(char *argv[], int tar, struct tar_t *header);

void test_typeflag1(char *argv[], int tar, struct tar_t *header);

void test_linkname1(char *argv[], int tar, struct tar_t *header);

void test_magic1(char *argv[], int tar, struct tar_t *header);

void test_version1(char *argv[], int tar, struct tar_t *header);

void test_uname1(char *argv[], int tar, struct tar_t *header);

void test_gname1(char *argv[], int tar, struct tar_t *header);

void test_0byte(char *argv[], int tar, struct tar_t *header);

void test_chksum_MAX_multiple(char *argv[], int tar, struct tar_t *header);

void test_chksum_field_overflow(char *argv[], int tar, struct tar_t *header);

void test_medium_size1(char *argv[], int tar, struct tar_t *header);

void test_linked_linkname(char *argv[], int tar, struct tar_t *header);


#endif //SRC_TEST_H
