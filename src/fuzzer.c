#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "util.h"

/**
 * Perform test based on the archive "archive_basic.tar" wich contain only an empty ".txt" file.
 * The first test duplicate the header with non ASCII name value.
 * The others tests are simple, just try for every field all possible characters (256 different value)
 * @param argv: the argument passed from the main fct
 * @return 0 if nothing wrong happened, -1 otherwise.
 */
int basic(char* extractor);

/**
 * Perform test based on the archive "archive_medium.tar" which contain 2 ."txt" files with data.
 * This will test if the extractor can cope with different size value for 2 files.
 * @param argv: the argument passed from the main fct
 * @return 0 if nothing wrong happened, -1 otherwise.
 */
int medium(char* extractor);

/**
 * Perform test based on the archive "archive_linked.tar" which contain a ."txt" file with data and a simbolic link for that file.
 * Test whether the extractor can manage an archive with a simbolinc link that point to wrong name (aka linkname).
 * Test also the case where the simbolic link point to iself.
 * @param argv: the argument passed from the main fct
 * @return 0 if nothing wrong happened, -1 otherwise.
 */
int linked(char* extractor);

/**
 * Perform test based on the archive "archive_dir.tar" which contain only an empty folder.
 * The first test will add size and data to the folder which normaly can't have, and the second test will replace
 * all the 0x0 bytes of the end of the archive by some value.
 * @param argv: the argument passed from the main fct
 * @return 0 if nothing wrong happened, -1 otherwise.
 */
int dir(char* extractor);


int main(int argc, char* argv[]) {
    if (argc < 2)
        return -1;

    basic(argv[1]);
    medium(argv[1]);
    linked(argv[1]);
    dir(argv[1]);
}


int basic(char* extractor){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    header = (struct tar_t *) malloc(sizeof(struct tar_t));

    //create a copy of the archive and perform test on the copied one
    system("cp arc/archive_basic.tar arc/archive.tar");
    if ((tar = open("arc/archive.tar", O_RDWR, O_SYNC)) == -1) {
        printf("Error opening file!\n");
        return -1;
    }

    //read of the first header
    if (read(tar, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        goto finally;
    }


    test_name1(extractor, tar, header);
    test_name2(extractor, tar, header);

    test_mode1(extractor, tar, header);

    test_uid1(extractor, tar, header);

    test_gid1(extractor, tar, header);

    test_size1(extractor, tar, header);

    test_mtime1(extractor, tar, header);

    test_typeflag1(extractor, tar, header);

    test_linkname1(extractor, tar, header);

    test_magic1(extractor, tar, header);

    test_version1(extractor, tar, header);

    test_uname1(extractor, tar, header);

    test_gname1(extractor, tar, header);

    test_0byte(extractor, tar, header);

    test_chksum_MAX_multiple(extractor, tar, header);

    test_chksum_field_overflow(extractor, tar, header);


    finally:

    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}


int medium(char* extractor){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    header = (struct tar_t *) malloc(sizeof(struct tar_t));

    //create a copy of the archive and perform test on the copied one
    system("cp arc/archive_medium.tar arc/archive.tar");
    if ((tar = open("arc/archive.tar", O_RDWR, O_SYNC)) == -1) {
        printf("Error opening file!\n");
        return -1;
    }

    //read of the first header
    if (read(tar, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        goto finally;
    }

    test_medium_size1(extractor, tar, header);

    test_medium_nonASCII_data(extractor, tar, header);

    finally:
    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}

int linked(char* extractor){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    header = (struct tar_t *) malloc(sizeof(struct tar_t));

    //create a copy of the archive and perform test on the copied one
    system("cp arc/archive_linked.tar arc/archive.tar");
    if ((tar = open("arc/archive.tar", O_RDWR, O_SYNC)) == -1) {
        printf("Error opening file!\n");
        return -1;
    }

    //read of the first header
    if (read(tar, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        goto finally;
    }

    test_linked_linkname(extractor, tar, header);

    finally:
    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}


int dir(char* extractor){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    header = (struct tar_t *) malloc(sizeof(struct tar_t));

    //create a copy of the archive and perform test on the copied one
    system("cp arc/archive_dir.tar arc/archive.tar");
    if ((tar = open("arc/archive.tar", O_RDWR, O_SYNC)) == -1) {
        printf("Error opening file!\n");
        return -1;
    }

    //read of the first header
    if (read(tar, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        goto finally;
    }

    test_dir_adding_data(extractor, tar, header);

    finally:
    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}