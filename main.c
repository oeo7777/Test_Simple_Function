#include <stdio.h>

#include "caL_CheckSum.h"
extern void File_Out();


void main(void){
    printf("hollow \n");

    //File_Out();
    Load_and_cal_checksum();
    
    printf("checksum %x\n", checkSum_Cal.csValue);
}
