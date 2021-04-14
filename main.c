#include <stdio.h>
#include <string.h>

#include "caL_CheckSum.h"
extern void File_Out();


void main(int argc, char *argv[]){
    printf("hollow \n");

    char out_name[100] = "";
    strcpy(out_name, argv[1]);

    printf("out [%s]\n", out_name);

    //File_Out();
    //Load_and_cal_checksum(out_name);
    Load_and_cal_Fuse_checksum(out_name);
    
    printf("checksum %x\n", checkSum_Cal.csValue);
}
