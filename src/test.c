#include "util.h"


void test_name1(char *argv[], int fd, struct tar_t *header) {
    setup(fd, header,BASIC);

    for (int j = 0; j < 100; j++) {
        //range of all non ASCII char [127,283]
        for (int val = 127; val < 283; val++) {
            header->name[j] = val;

            calculate_checksum(header);

            //write new name but after the current fd pointer -> we duplicate the first header
            //lseek(fd,0,SEEK_SET);
            if (write(fd, (void*) header, sizeof(struct tar_t)) == -1) {
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


void test_name2(char *argv[], int fd, struct tar_t *header) {

    setup(fd,header,BASIC);

    for (int j = 0; j < 100 ; j++){//replace 1 by 100
        //range of all non ASCII char [127,283]
        for (int val = 127; val < 283; val++) {
            header->name[j] = val;

            calculate_checksum(header);

            //this time we set the fd pointer back to the begining of the archive
            lseek(fd,0,SEEK_SET);
            if (write(fd, (void*) header, sizeof(struct tar_t)) == -1) {
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


void test_mode1(char *argv[], int fd, struct tar_t *header) {
    setup(fd,header,BASIC);

    int ret = fillHeader(argv,fd,header,MODE,8,0);

    if (ret == 1){
        printf("mode bugged : %s\n",header->mode);
        system("cp archives/archive.tar success_mode.tar");
    }
}


void test_uid1(char *argv[], int fd, struct tar_t *header) {

    setup(fd,header,BASIC);

    int ret = fillHeader(argv,fd,header,UID,8,0);

    if(ret == 1){
        printf("uid bugged : %s\n",header->uid);
        system("cp archives/archive.tar success_uid.tar");
    }
}


void test_gid1(char *argv[], int fd, struct tar_t *header) {
    setup(fd,header,BASIC);

    int ret = fillHeader(argv,fd,header,GID,8,0);

    if(ret == 1){
        printf("gid bugged : %s\n",header->gid);
        system("cp archives/archive.tar success_gid.tar");
    }
}


void test_size1(char *argv[], int fd, struct tar_t *header) {

    setup(fd,header,BASIC);

    int ret = fillHeader(argv,fd,header,SIZE,12,0);

    if(ret == 1){
        printf("size bugged : %s\n",header->size);
        system("cp archives/archive.tar success_size.tar");
    }
}

void test_mtime1(char *argv[], int fd, struct tar_t *header) {

    setup(fd,header,BASIC);

    int ret = fillHeader(argv,fd,header,MTIME,12,0);

    if(ret == 1){
        printf("mtime bugged : %s\n",header->mtime);
        system("cp archives/archive.tar success_mtime.tar");
    }
}


void test_typeflag1(char *argv[], int fd, struct tar_t *header) {

    setup(fd,header,BASIC);

    for (char val = -128; val < 127; val++) {
        header->typeflag = val;

        calculate_checksum(header);
        lseek(fd,0,SEEK_SET);
        if (write(fd, (void*) header, sizeof(struct tar_t)) == -1) {
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

void test_linkname1(char *argv[], int fd, struct tar_t *header) {

    setup(fd,header,BASIC);

    int ret = fillHeader(argv,fd,header,LINKNAME,100,0);

    if(ret == 1){
        printf("linkname bugged : %s\n",header->linkname);
        system("cp archives/archive.tar success_linkname.tar");
    }
}

void test_magic1(char *argv[], int fd, struct tar_t *header) {

    setup(fd,header,BASIC);

    int ret = fillHeader(argv,fd,header,MAGIC,6,0);

    if(ret == 1){
        printf("magic bugged : %s\n",header->magic);
        system("cp archives/archive.tar success_magic.tar");
    }
}

void test_version1(char *argv[], int fd, struct tar_t *header) {
    setup(fd,header,BASIC);

    int ret = fillHeader(argv,fd,header,VERSION,2,0);

    if(ret == 1){
        printf("version bugged : %s\n",header->version);
        system("cp archives/archive.tar success_version.tar");
    }
}

void test_uname1(char *argv[], int fd, struct tar_t *header) {
    setup(fd,header,BASIC);

    int ret = fillHeader(argv,fd,header,UNAME,32,0);

    if(ret == 1){
        printf("uname bugged : %s\n",header->uname);
        system("cp archives/archive.tar success_uname.tar");
    }
}

void test_gname1(char *argv[], int fd, struct tar_t *header) {
    setup(fd,header,BASIC);

    int ret = fillHeader(argv,fd,header,GNAME,32,0);

    if(ret == 1){
        printf("gname bugged : %s\n",header->gname);
        system("cp archives/archive.tar success_gname.tar");
    }
}

void test_0byte(char *argv[], int fd, struct tar_t *header) {

    setup(fd,header,BASIC);
    char tab[512];
    for (int i = 0; i < 512; i++)
    {
        tab[i] = '\0';
    }
    lseek(fd,0,SEEK_SET);
    write(fd,tab,512);

    int ret = launch(argv);
    if(ret == 1){
        printf("header with all 0 bugged ");
        system("cp archives/archive.tar success_empty.tar");
    }
}


void test_chksum_MAX_multiple(char *argv[], int fd, struct tar_t *header)
{
    setup(fd, header,BASIC);

//------first we ensure that the first case is the maximum possible value--------------
    sprintf(header->chksum,"%o",2097151);//'7777777'

    lseek(fd,0,SEEK_SET);
    if (write(fd, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error writing file!\n");
        return;
    }

    int ret = launch(argv);

    //handle case if we found a succesfull attack
    if(ret==1){
        printf("cheksum bugged = %s\n", header->chksum);
        system("cp archives/archive.tar archives/success_cheksum.tar");
        return;
    }

//----------after we test 10 times for some big value----------------------
    int counter = 0;
    while(ret == 0 && counter < 10) {
        int upper = 2097151; // max octal number for 7 char
        int lower = 0;
        int rand_int = (random() % (upper - lower + 1)) + lower;

        sprintf(header->chksum, "%o", rand_int);

        lseek(fd, 0, SEEK_SET);
        if (write(fd, (void *) header, sizeof(struct tar_t)) == -1) {
            printf("Error writing file!\n");
            return;
        }

        ret = launch(argv);

        if (ret == 1) {
            printf("cheksum bugged = %s\n", header->chksum);
            system("cp archives/archive.tar success_cheksum.tar");
            return;
        }
        counter++;
    }
}



void test_chksum_field_overflow(char *argv[], int fd, struct tar_t *header)
{
    setup(fd, header,BASIC);

    int ret;

    for(int i = 8; (i < 120) && (ret != 1); i++)
    {

        for(int pos = 0; (pos < i-1) ;pos++) {
            int upper = 55; //'7'
            int lower = 48; //'0'
            header->chksum[pos] = lower + (rand() % (upper - lower));
        }
        header->chksum[i-1] = '\0';


        lseek(fd,0,SEEK_SET);
        if (write(fd, (void*) header, sizeof(struct tar_t)) == -1) {
            printf("Error writing file!\n");
            return;
        }


        ret = launch(argv);

        if(ret==1){
            printf("cheksum bugged = %s\n", header->chksum);
            system("cp archives/archive.tar success_cheksum.tar");
            return;
        }
    }
}


void test_medium_size1(char *argv[], int fd, struct tar_t *header) {
//---------------modify first header-------------------

    int ret = fillHeader( argv, fd, header, SIZE, 12,1);

    if(ret == 1){
        printf("size bugged : %s\n",header->size);
        system("cp archives/archive.tar success_size.tar");
    }

//---------------modify second header-----------------
    setup(fd,header,MEDIUM);
    // go to next header
    int ONE = 1;
    if(TAR_INT(header->size)%512 == 0){
        ONE = 0;
    }
    lseek(fd,(TAR_INT(header->size)/512 + ONE) *512,SEEK_CUR);

    //read next header
    if (read(fd, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        return;
    }

    printf("second header name : %s\n",header->name);

    ret = fillHeader( argv, fd, header, SIZE, 12, 1);
    if(ret == 1){
        printf("size bugged : %s\n",header->size);
        system("cp archives/archive.tar success_size.tar");
    }
}

void test_medium_nonASCII_data(char *argv[], int fd,  struct tar_t *header){
//------------first test on first file----------
    int ret;
    setup(fd, header, MEDIUM);

    //fd pointer is already pointing after the first header

    char buffer[256];
    for (int i = 0; i < 256; i++)
    {
        buffer[i] = i;//fill with whatever character
    }

    if (write(fd, (void *) buffer, 256) == -1) {
        printf("Error writing file!\n");
        return;
    }
    
    ret = launch(argv);
    if(ret == 1){
        printf("non ACSII content bugged \n");
        system("cp archives/archive.tar success_nonASCII_content.tar");
    }


//---------second test on second file----------

    // go after next header
    lseek(fd, 0, SEEK_SET);
    int ONE = 1;
    if(TAR_INT(header->size)%512 == 0){
        ONE = 0;
    }
    lseek(fd,(TAR_INT(header->size)/512 + ONE + 2) *512,SEEK_CUR);


    if (write(fd, (void *) buffer, 256) == -1) {
        printf("Error writing file!\n");
        return;
    }
    
    ret = launch(argv);
    if(ret == 1){
        printf("non ACSII content bugged \n");
        system("cp archives/archive.tar success_nonASCII_content.tar");
    }
}


void test_linked_linkname(char *argv[], int fd, struct tar_t *header) {
    int ret = fillHeader(argv,fd,header,LINKNAME,100,0);
    if(ret == 1){
        printf("linkname bugged : %s\n",header->linkname);
        system("cp archives/archive.tar success_linkname.tar");
    }
}

void test_dir_adding_data(char* argv[], int fd, struct tar_t *header){
    int ret =0;

    //set size to 500
    header->size[10] = '0';
    header->size[9] = '0';
    header->size[8] = '5';

    calculate_checksum(header);

    lseek(fd, 0, SEEK_SET);
    if (write(fd, (void *) header, sizeof(struct tar_t)) == -1) {
        printf("Error writing file!\n");
        return;
    }

    //buffer who will contain the data
    char bonus[500];

    for (int pos = 0; pos < 500; pos++)
    {
        bonus[pos] = pos;
    }
    
    //write the data after the headers
    if (write(fd, (void *) bonus, 500) == -1) {
        printf("Error writing file!\n");
        return;
    }

    ret = launch(argv);

    if (ret == 1) {
        printf("dir bugged\n");
        system("cp archives/archive.tar success_size+data.tar");
    }


    //Second test by overwriting the 00 byte until the end

    for (int i = 0; i < 20; i++)
    {
        if (write(fd, (void *) bonus, 500) == -1) {
            printf("Error writing file!\n");
            return;
        }
    }

    ret = launch(argv);

    if (ret == 1) {
        printf("dir bugged\n");
        system("cp archives/archive.tar success_padding_overwriting.tar");
        return;
    }
    
}

