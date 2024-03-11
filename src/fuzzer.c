#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "util.h"


int basic(char* argv[]);
int medium(char* argv[]);
int linked(char *argv[]);
int dir(char *argv[]);


int main(int argc, char* argv[]) {
    if (argc < 2)
        return -1;

    basic(argv);
    medium(argv);
    linked(argv);
    dir(argv);
}


int basic(char* argv[]){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    header = (struct tar_t *) malloc(sizeof(struct tar_t));

    //create a copy of the archive and perform test on the copied one
    system("cp archives/archive_basic.tar archives/archive.tar");
    if ((tar = open("archives/archive.tar", O_RDWR, O_SYNC)) == -1) {
        printf("Error opening file!\n");
        return -1;
    }

    //read of the first header
    if (read(tar, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        goto finally;
    }


    test_name1(argv, tar, header);
    test_name2(argv, tar, header);

    test_mode1(argv, tar, header);

    test_uid1(argv, tar, header);

    test_gid1(argv, tar, header);

    test_size1(argv, tar, header);

    test_mtime1(argv, tar, header);

    test_typeflag1(argv, tar, header);

    test_linkname1(argv, tar, header);

    test_magic1(argv, tar, header);

    test_version1(argv, tar, header);

    test_uname1(argv, tar, header);

    test_gname1(argv, tar, header);

    test_0byte(argv, tar, header);

    test_chksum_MAX_multiple(argv, tar, header);

    test_chksum_field_overflow(argv, tar, header);


    finally:

    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}


int medium(char* argv[]){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    header = (struct tar_t *) malloc(sizeof(struct tar_t));

    //create a copy of the archive and perform test on the copied one
    system("cp archives/archive_medium.tar archives/archive.tar");
    if ((tar = open("archives/archive.tar", O_RDWR, O_SYNC)) == -1) {
        printf("Error opening file!\n");
        return -1;
    }

    //read of the first header
    if (read(tar, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        goto finally;
    }

    test_medium_size1(argv, tar, header);

    test_medium_nonASCII_data(argv, tar, header);

    finally:
    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}

int linked(char *argv[]){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    header = (struct tar_t *) malloc(sizeof(struct tar_t));

    //create a copy of the archive and perform test on the copied one
    system("cp archives/archive_linked.tar archives/archive.tar");
    if ((tar = open("archives/archive.tar", O_RDWR, O_SYNC)) == -1) {
        printf("Error opening file!\n");
        return -1;
    }

    //read of the first header
    if (read(tar, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        goto finally;
    }

    test_linked_linkname(argv, tar, header);

    finally:
    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}


int dir(char *argv[]){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    header = (struct tar_t *) malloc(sizeof(struct tar_t));

    //create a copy of the archive and perform test on the copied one
    system("cp archives/archive_dir.tar archives/archive.tar");
    if ((tar = open("archives/archive.tar", O_RDWR, O_SYNC)) == -1) {
        printf("Error opening file!\n");
        return -1;
    }

    //read of the first header
    if (read(tar, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        goto finally;
    }

    test_dir_adding_data(argv, tar, header);

    finally:
    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}