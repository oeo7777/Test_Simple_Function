#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define Len_s    2
unsigned int s[Len_s] = {0xcdbd0acf, 0xdcabab}; //{11111111111111111011110110110011, 11111111111111110011101100000000};
unsigned char s1[8] = {0x30, 0x31, 0x31};

int File_Out(void){

    printf("p1 = %x, p2 = %x \n", s[0], s[1]);


    FILE *pf = fopen("/home/sam.tsai/code/Test_Simple_Function/f1.txt","w");
    fwrite(s1, 1, sizeof(s1), pf);
    
    fclose(pf);


}
