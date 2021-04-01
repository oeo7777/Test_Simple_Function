#include<stdio.h>
#include<stdlib.h>
#include <string.h>

char s[2] = {2, 5};

int File_Out(void){

    printf("p1 = %d, p2 = %d \n", s[0], s[1]);


    FILE *pf = fopen("/home/sam.tsai/code/Test_Simple_Function/f1.txt","w");
    fwrite(s, 1, strlen(s), pf);
    
    fclose(pf);


}
