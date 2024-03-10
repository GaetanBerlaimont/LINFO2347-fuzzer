#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "util.h"


int basic(int argc, char* argv[]);
int medium(int argc, char* argv[]);
int linked(int argc, char *argv[]);


int main(int argc, char* argv[])
{
    if (argc < 2)
        return -1;

    //perform test on basic archive
    basic(argc,argv);
    //medium(argc,argv);
    //linked(argc,argv);

}


int basic(int argc, char* argv[]){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    int ret;
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


    finally:

    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}


int medium(int argc, char* argv[]){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    int ret;
    int ONE;
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
/*|-----------------------------------------------------------------|*/
/*|                          TEST with size                         |*/
/*|-----------------------------------------------------------------|*/

    //---------modify first header--------------
    ret = fillHeader( argv, tar, header, SIZE, 12,1);

    if(ret == 1){
        printf("size bugged : %s\n",header->size);
        system("cp archives/archive.tar success_size.tar");
    }

    //---------modify second header-----------
    setup(tar,header,MEDIUM);
    // go to next header
    ONE = 1;
    if(TAR_INT(header->size)%512 == 0){
        ONE = 0;
    }
    lseek(tar,(TAR_INT(header->size)/512 + ONE) *512,SEEK_CUR);

    //read next header
    if (read(tar, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        goto finally;
    }

    printf("second header name : %s\n",header->name);

    ret = fillHeader( argv, tar, header, SIZE, 12, 1);
    if(ret == 1){
        printf("size bugged : %s\n",header->size);
        system("cp archives/archive.tar success_size.tar");
    }




    finally:
    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}

int linked(int argc, char *argv[]){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    int ret;
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
/*|-----------------------------------------------------------------|*/
/*|                        TEST with linkname                       |*/
/*|-----------------------------------------------------------------|*/
    ret = fillHeader(argv,tar,header,LINKNAME,100,0);
    if(ret == 1){
        printf("lnikname bugged : %s\n",header->linkname);
        system("cp archives/archive.tar success_linkname.tar");
    }




    finally:
    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}