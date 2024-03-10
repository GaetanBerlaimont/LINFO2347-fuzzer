#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


int basic(int argc, char* argv[]);
int medium(int argc, char* argv[]);

int name = 0;
int mode = 0;
int uid = 0;
int gid = 0;
int size = 0;
int mtime = 0;
int typeflag = 0;
int linkname = 0;
int magic = 0;
int version = 0;
int uname = 0;
int gname = 0;

int main(int argc, char* argv[])
{
    if (argc < 2)
        return -1;

    //perform test on basic archive
    basic(argc,argv);
    medium(argc,argv);

}


int basic(int argc, char* argv[]){
    //initialisation variable
    int tar;// folder
    struct tar_t *header;
    int ret;
    header = (struct tar_t *) malloc(sizeof(struct tar_t));

    //create a copy of the archive and perform test on the copied one
    system("cp archive_basic.tar archive.tar");
    if ((tar = open("archive.tar", O_RDWR, O_SYNC)) == -1) {
        printf("Error opening file!\n");
        return -1;
    }

    //read of the first header
    if (read(tar, (void*) header, sizeof(struct tar_t)) == -1) {
        printf("Error reading file!\n");
        goto finally;
    }
/*|-----------------------------------------------------------------|*/
/*|                TEST with name (duplicate header)                |*/
/*|-----------------------------------------------------------------|*/
    for (int j = 0; j < 100; j++){
        //range of all non ASCII char [127,283]
        for (int val = 127; val < 283; val++)
        {
            header->name[j] = val;

            calculate_checksum(header);

            //write new name but after the current fd pointer -> we duplicate the first header
            //lseek(tar,0,SEEK_SET);
            if (write(tar, (void*) header, sizeof(struct tar_t)) == -1) {
                printf("Error writing file!\n");
                goto name_step;
            }        

            ret = launch(argc,argv);

            //handle case if we found a succesfull attack
            if(ret==1){
                printf("duplicate header name bugged = %s\n",header->name);
                system("cp archive.tar success_name_duplicateHeader.tar");
                goto name_step;
            }else{
                remove(header->name);
            }
        }
    }
    name_step:
/*|-----------------------------------------------------------------|*/
/*|                          TEST with name                         |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    for (int j = 0; j < 100; j++){//replace 1 by 100
        //range of all non ASCII char [127,283]
        for (int val = 127; val < 283; val++)
        {           
            header->name[j] = val;

            calculate_checksum(header);

            //this time we set the fd pointer back to the begining of the archive
            lseek(tar,0,SEEK_SET);
            if (write(tar, (void*) header, sizeof(struct tar_t)) == -1) {
                printf("Error writing file!\n");
                goto mode_step;
            }        

            ret = launch(argc,argv);

            //handle case if we found a succesfull attack
            if(ret==1){
                printf("name bugged = %s\n",header->name);
                system("cp archive.tar success_name.tar");
                name = 1;
                goto mode_step;
            }else{
                remove(header->name);
            }
        }
    }
    mode_step:
/*|-----------------------------------------------------------------|*/
/*|                          TEST with mode                         |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    ret = fillHeader(argc,argv,tar,header,MODE,8);

    if(ret == 1){
        printf("mode bugged : %s\n",header->mode);
        system("cp archive.tar success_mode.tar");
        mode = 1;
    }

/*|-----------------------------------------------------------------|*/
/*|                          TEST with uid                          |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    ret = fillHeader(argc,argv,tar,header,UID,8);
    
    if(ret == 1){
        printf("uid bugged : %s\n",header->uid);
        system("cp archive.tar success_uid.tar");
        uid = 1;
    }

/*|-----------------------------------------------------------------|*/
/*|                          TEST with gid                          |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    ret = fillHeader(argc,argv,tar,header,GID,8);
    
    if(ret == 1){
        printf("gid bugged : %s\n",header->gid);
        system("cp archive.tar success_gid.tar");
        gid = 1;
    }

/*|-----------------------------------------------------------------|*/
/*|                          TEST with size                         |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    ret = fillHeader(argc,argv,tar,header,SIZE,12);
    
    if(ret == 1){
        printf("size bugged : %s\n",header->size);
        system("cp archive.tar success_size.tar");
        size = 1;
    }

/*|-----------------------------------------------------------------|*/
/*|                          TEST with mtime                        |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    ret = fillHeader(argc,argv,tar,header,MTIME,12);
    
    if(ret == 1){
        printf("mtime bugged : %s\n",header->mtime);
        system("cp archive.tar success_mtime.tar");
        mtime = 1;
    }

/*|-----------------------------------------------------------------|*/
/*|                        TEST with typeflag                       |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    for (char val = -128; val < 127; val++)
    {
        header->typeflag = val;

        calculate_checksum(header);
        lseek(tar,0,SEEK_SET);
        if (write(tar, (void*) header, sizeof(struct tar_t)) == -1) {
            printf("Error writing file!\n");
            goto linkname_step;
        }

        ret = launch(argc,argv);

        //handling case we found succes crash
        if (ret == 1){
            printf("typeflag bugged : %c\n",header->typeflag);
            system("cp archive.tar success_typeflag.tar");
            typeflag = 1;
            goto linkname_step;
        }
    }
    linkname_step:

/*|-----------------------------------------------------------------|*/
/*|                        TEST with lnikname                       |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    ret = fillHeader(argc,argv,tar,header,LINKNAME,100);
    
    if(ret == 1){
        printf("linkname bugged : %s\n",header->linkname);
        system("cp archive.tar success_linkname.tar");
        linkname = 1;
    }

/*|-----------------------------------------------------------------|*/
/*|                          TEST with magic                        |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    ret = fillHeader(argc,argv,tar,header,MAGIC,6);
    
    if(ret == 1){
        printf("magic bugged : %s\n",header->magic);
        system("cp archive.tar success_magic.tar");
        magic = 1;
    }

/*|-----------------------------------------------------------------|*/
/*|                         TEST with version                       |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    ret = fillHeader(argc,argv,tar,header,VERSION,2);
    
    if(ret == 1){
        printf("version bugged : %s\n",header->version);
        system("cp archive.tar success_version.tar");
        version = 1;
    }

/*|-----------------------------------------------------------------|*/
/*|                          TEST with uname                        |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    ret = fillHeader(argc,argv,tar,header,UNAME,32);
    
    if(ret == 1){
        printf("uname bugged : %s\n",header->uname);
        system("cp archive.tar success_uname.tar");
        uname = 1;
    }

/*|-----------------------------------------------------------------|*/
/*|                          TEST with gname                        |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);

    ret = fillHeader(argc,argv,tar,header,GNAME,32);
    
    if(ret == 1){
        printf("gname bugged : %s\n",header->gname);
        system("cp archive.tar success_gname.tar");
        gname = 1;
    }

/*|-----------------------------------------------------------------|*/
/*|                       TEST with all byte 0                      |*/
/*|-----------------------------------------------------------------|*/
    setup(tar,header);
    char tab[512];
    for (int i = 0; i < 512; i++)
    {
        tab[i] = '\0';
    }
    lseek(tar,0,SEEK_SET);
    write(tar,tab,512);

    ret = launch(argc,argv);
    if(ret == 1){
        printf("header with all 0 bugged ");
        system("cp archive.tar success_empty.tar");
    }
    

    finally:
    if(close(tar) == -1) {
        printf("Command not found\n");
    }
    free(header);
    header=NULL;
    return 0;
}


int medium(int argc, char* argv[]){




    return 0;
}