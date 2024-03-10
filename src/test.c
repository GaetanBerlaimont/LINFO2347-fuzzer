#include "util.h"

/*|-----------------------------------------------------------------|*/
/*|                TEST with name (duplicate header)                |*/
/*|-----------------------------------------------------------------|*/
// This test checks if the extractor can handle large length values and
// if it crashes or shows unexpected behavior when processing such values
// in the len field. It tests this with a set of random large length values.
void test_name1(char *argv[], int tar, struct tar_t *header) {
    setup(tar, header,BASIC);

    for (int j = 0; j < 100; j++) {
        //range of all non ASCII char [127,283]
        for (int val = 127; val < 283; val++) {
            header->name[j] = val;

            calculate_checksum(header);

            //write new name but after the current fd pointer -> we duplicate the first header
            //lseek(tar,0,SEEK_SET);
            if (write(tar, (void*) header, sizeof(struct tar_t)) == -1) {
                printf("Error writing file!\n");
                return;
            }

            int ret = launch(argv);

            //handle case if we found a succesfull attack
            if (ret==1) {
                printf("duplicate header name bugged = %s\n", header->name);
                system("cp archives/archive.tar success_name_duplicateHeader.tar");
                return;
            }
            else {
                remove(header->name);
            }
        }
    }
}

/*|-----------------------------------------------------------------|*/
/*|                          TEST with name                         |*/
/*|-----------------------------------------------------------------|*/
void test_name2(char *argv[], int tar, struct tar_t *header) {

    setup(tar,header,BASIC);

    for (int j = 0; j < 100 ; j++){//replace 1 by 100
        //range of all non ASCII char [127,283]
        for (int val = 127; val < 283; val++) {
            header->name[j] = val;

            calculate_checksum(header);

            //this time we set the fd pointer back to the begining of the archive
            lseek(tar,0,SEEK_SET);
            if (write(tar, (void*) header, sizeof(struct tar_t)) == -1) {
                printf("Error writing file!\n");
                return;
            }

            int ret = launch(argv);

            //handle case if we found a succesfull attack
            if (ret==1) {
                printf("name bugged = %s\n",header->name);
                system("cp archives/archive.tar success_name.tar");
                return;
            }
            else {
                remove(header->name);
            }
        }
    }
}

/*|-----------------------------------------------------------------|*/
/*|                          TEST with mode                         |*/
/*|-----------------------------------------------------------------|*/
void test_mode1(char *argv[], int tar, struct tar_t *header) {
    setup(tar,header,BASIC);

    int ret = fillHeader(argv,tar,header,MODE,8,0);

    if (ret == 1){
        printf("mode bugged : %s\n",header->mode);
        system("cp archives/archive.tar success_mode.tar");
    }
}

/*|-----------------------------------------------------------------|*/
/*|                          TEST with uid                          |*/
/*|-----------------------------------------------------------------|*/
void test_uid1(char *argv[], int tar, struct tar_t *header) {

    setup(tar,header,BASIC);

    int ret = fillHeader(argv,tar,header,UID,8,0);

    if(ret == 1){
        printf("uid bugged : %s\n",header->uid);
        system("cp archives/archive.tar success_uid.tar");
    }
}

/*|-----------------------------------------------------------------|*/
/*|                          TEST with gid                          |*/
/*|-----------------------------------------------------------------|*/
void test_gid1(char *argv[], int tar, struct tar_t *header) {
    setup(tar,header,BASIC);

    int ret = fillHeader(argv,tar,header,GID,8,0);

    if(ret == 1){
        printf("gid bugged : %s\n",header->gid);
        system("cp archives/archive.tar success_gid.tar");
    }
}

/*|-----------------------------------------------------------------|*/
/*|                          TEST with size                         |*/
/*|-----------------------------------------------------------------|*/
void test_size1(char *argv[], int tar, struct tar_t *header) {

    setup(tar,header,BASIC);

    int ret = fillHeader(argv,tar,header,SIZE,12,0);

    if(ret == 1){
        printf("size bugged : %s\n",header->size);
        system("cp archives/archive.tar success_size.tar");
    }
}

/*|-----------------------------------------------------------------|*/
/*|                          TEST with mtime                        |*/
/*|-----------------------------------------------------------------|*/
void test_mtime1(char *argv[], int tar, struct tar_t *header) {

    setup(tar,header,BASIC);

    int ret = fillHeader(argv,tar,header,MTIME,12,0);

    if(ret == 1){
        printf("mtime bugged : %s\n",header->mtime);
        system("cp archives/archive.tar success_mtime.tar");
    }
}

/*|-----------------------------------------------------------------|*/
/*|                        TEST with typeflag                       |*/
/*|-----------------------------------------------------------------|*/
void test_typeflag1(char *argv[], int tar, struct tar_t *header) {

    setup(tar,header,BASIC);

    for (char val = -128; val < 127; val++) {
        header->typeflag = val;

        calculate_checksum(header);
        lseek(tar,0,SEEK_SET);
        if (write(tar, (void*) header, sizeof(struct tar_t)) == -1) {
            printf("Error writing file!\n");
            return;
        }

        int ret = launch(argv);

        //handling case we found succes crash
        if (ret == 1){
            printf("typeflag bugged : %c\n",header->typeflag);
            system("cp archives/archive.tar success_typeflag.tar");
            return;
        }
    }
}

/*|-----------------------------------------------------------------|*/
/*|                        TEST with linkname                       |*/
/*|-----------------------------------------------------------------|*/
void test_linkname1(char *argv[], int tar, struct tar_t *header) {

    setup(tar,header,BASIC);

    int ret = fillHeader(argv,tar,header,LINKNAME,100,0);

    if(ret == 1){
        printf("linkname bugged : %s\n",header->linkname);
        system("cp archives/archive.tar success_linkname.tar");
    }
}

/*|-----------------------------------------------------------------|*/
/*|                          TEST with magic                        |*/
/*|-----------------------------------------------------------------|*/
void test_magic1(char *argv[], int tar, struct tar_t *header) {

    setup(tar,header,BASIC);

    int ret = fillHeader(argv,tar,header,MAGIC,6,0);

    if(ret == 1){
        printf("magic bugged : %s\n",header->magic);
        system("cp archives/archive.tar success_magic.tar");
    }
}

/*|-----------------------------------------------------------------|*/
/*|                         TEST with version                       |*/
/*|-----------------------------------------------------------------|*/
void test_version1(char *argv[], int tar, struct tar_t *header) {
    setup(tar,header,BASIC);

    int ret = fillHeader(argv,tar,header,VERSION,2,0);

    if(ret == 1){
        printf("version bugged : %s\n",header->version);
        system("cp archives/archive.tar success_version.tar");
    }
}

/*|-----------------------------------------------------------------|*/
/*|                          TEST with uname                        |*/
/*|-----------------------------------------------------------------|*/
void test_uname1(char *argv[], int tar, struct tar_t *header) {
    setup(tar,header,BASIC);

    int ret = fillHeader(argv,tar,header,UNAME,32,0);

    if(ret == 1){
        printf("uname bugged : %s\n",header->uname);
        system("cp archives/archive.tar success_uname.tar");
    }
}

/*|-----------------------------------------------------------------|*/
/*|                          TEST with gname                        |*/
/*|-----------------------------------------------------------------|*/
void test_gname1(char *argv[], int tar, struct tar_t *header) {
    setup(tar,header,BASIC);

    int ret = fillHeader(argv,tar,header,GNAME,32,0);

    if(ret == 1){
        printf("gname bugged : %s\n",header->gname);
        system("cp archives/archive.tar success_gname.tar");
    }
}

/*|-----------------------------------------------------------------|*/
/*|                       TEST with all byte 0                      |*/
/*|-----------------------------------------------------------------|*/
void test_0byte(char *argv[], int tar, struct tar_t *header) {

    setup(tar,header,BASIC);
    char tab[512];
    for (int i = 0; i < 512; i++)
    {
        tab[i] = '\0';
    }
    lseek(tar,0,SEEK_SET);
    write(tar,tab,512);

    int ret = launch(argv);
    if(ret == 1){
        printf("header with all 0 bugged ");
        system("cp archives/archive.tar success_empty.tar");
    }
}

// Tess vulnerablility related to handling large checksum values in the tar header.
// Generates random octal numbers within maximum range
// for a 7-character checksum and calls chksum_single_test with each value.
void test_chksum_MAX_multiple(char *argv[], int tar, struct tar_t *header)
{
    setup(tar, header,BASIC);

    sprintf(header->chksum,"%o",2097151);//'7777777'

    lseek(tar,0,SEEK_SET);
    if (write(tar, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error writing file!\n");
        return;
    }

    int ret = launch(argv);

    //handle case if we found a succesfull attack
    if(ret==1){
        printf("cheksum bugged = %s\n", header->chksum);
        system("cp archive.tar success_cheksum.tar");
        return;
    }

    int counter = 0;
    while(ret == 0 && counter < 10) {
        int upper = 2097151; // max octal number for 7 char
        int lower = 0;
        int rand_int = (random() % (upper - lower + 1)) + lower;

        sprintf(header->chksum, "%o", rand_int);

        lseek(tar, 0, SEEK_SET);
        if (write(tar, (void *) header, sizeof(struct tar_t)) == -1) {
            printf("Error writing file!\n");
            return;
            if (ret == 1) {
                printf("cheksum bugged = %s\n", header->chksum);
                system("cp archive.tar success_cheksum.tar");
                return;
            }
            counter++;
        }
    }
}


// This function tests vulnerablility for handling very long checksum strings in the tar header.
void test_chksum_field_overflow(char *argv[], int tar, struct tar_t *header)
{
    setup(tar, header,BASIC);

    int ret;

    for(int i = 8; (i < 120) && (ret != 1); i++)
    {

        for(int pos = 0; (pos < i-1) ;pos++) {
            int upper = 55; //'7'
            int lower = 48; //'0'
            header->chksum[pos] = lower + (rand() % (upper - lower));
        }
        header->chksum[i-1] = '\0';


        lseek(tar,0,SEEK_SET);
        if (write(tar, (void*) header, sizeof(struct tar_t)) == -1) {
            printf("Error writing file!\n");
            return;
        }


        ret = launch(argv);

        if(ret==1){
            printf("cheksum bugged = %s\n", header->chksum);
            system("cp archive.tar success_cheksum.tar");
            return;
        }
    }
}




