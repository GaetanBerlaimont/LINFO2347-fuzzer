#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "util.h"


int launch(int argc, char* argv[]){
    int rv = 0;
    char cmd[51];
    strncpy(cmd, argv[1], 25);
    cmd[26] = '\0';
    strncat(cmd, " archive.tar", 25);
    char buf[33];
    FILE *fp;

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }

    if(fgets(buf, 33, fp) == NULL) {
        //printf("No output\n");
        goto finally;
    }
    if(strncmp(buf, "*** The program has crashed ***\n", 33)) {
        printf("Not the crash message\n");
        goto finally;
    } else {
        printf("Crash message\n");
        rv = 1;
        goto finally;
    }
    finally:
    if(pclose(fp) == -1) {
        printf("Command not found\n");
        rv = -1;
    }
    return rv;
}

unsigned int calculate_checksum(struct tar_t* entry){
    // use spaces for the checksum bytes while calculating the checksum
    memset(entry->chksum, ' ', 8);

    // sum of entire metadata
    unsigned int check = 0;
    unsigned char* raw = (unsigned char*) entry;
    for(int i = 0; i < 512; i++){
        check += raw[i];
    }

    snprintf(entry->chksum, sizeof(entry->chksum), "%06o0", check);

    entry->chksum[6] = '\0';
    entry->chksum[7] = ' ';
    return check;
}

int setup(int fd, struct tar_t *header){
    if(close(fd) == -1) {
        printf("Command not found\n");
    }
    remove("archive.tar");
    system("cp archive_basic.tar archive.tar");
    if ((fd = open("archive.tar", O_RDWR, O_SYNC)) == -1) {
        printf("Error opening file!\n");
        return -1;
    }
    //read of the first header
    if (read(fd, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        if(close(fd) == -1) {
            printf("Command not found\n");
        }
        return -1;
    }
    return 0;
}

int fillHeader(int argc, char* argv[], int fd, struct tar_t *header, int wich_elem, int size){
    int ret;
    char * H;
    switch (wich_elem) {
        case NAME:
            H = header->name;
            break;
        case MODE:
            H = header->mode;
            break;
        case UID:
            H = header->uid;
            break;
        case GID:
            H = header->gid;
            break;
        case SIZE:
            H = header->size;
            break;
        case MTIME:
            H = header->mtime;
            break;
        case LINKNAME:
            H = header->linkname;
            break;
        case MAGIC:
            H = header->magic;
            break;
        case VERSION:
            H = header->version;
            break;
        case UNAME:
            H = header->uname;
            break;
        case GNAME:
            H = header->gname;
            break;
        default : 
            printf("error wrong input\n");
            return -1;
    }
    for (int pos = 0; pos < size; pos++)
    {
        for (char val = -128; val < 127; val++)
        {
            H[pos] = val;

            calculate_checksum(header);
            lseek(fd,0,SEEK_SET);// we need to get the fd pointer at the begining of the file to write on the same place (because we read previously)
            if (write(fd, (void*) header, sizeof(struct tar_t)) == -1) {
                printf("Error writing file!\n");
                return -1;
            }
            ret = launch(argc,argv);// we found a succesfull crash
            if (ret == 1){
                return 1;
            }
        }
    }
    return 0;
}