#include "util.h"

/*|-----------------------------------------------------------------|*/
/*|                TEST with name (duplicate header)                |*/
/*|-----------------------------------------------------------------|*/
// This test checks if the extractor can handle large length values and
// if it crashes or shows unexpected behavior when processing such values
// in the len field. It tests this with a set of random large length values.
void test_name(char *argv[], int tar, struct tar_t *header) {
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
            if(ret==1){
                printf("duplicate header name bugged = %s\n", header->name);
                system("cp archive.tar success_name_duplicateHeader.tar");
                return;
            }else{
                remove(header->name);
            }
        }
    }
}
