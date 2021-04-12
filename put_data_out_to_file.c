#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define Len_s    2
unsigned int s[Len_s] = {0xcdbd0acf, 0xdcabab}; //{11111111111111111011110110110011, 11111111111111110011101100000000};
unsigned char s1[8] = {0x30, 0x31, 0x31, 0x30, 0x30, 0x31};

int File_Out(void){
    char design_buf[] = {"DESIGN NAME: /tmp/lattice.jed"};
    char device_buf[] = {"DEVICE NAME: LCMXO2-7000HE\r\n"};
    char create_buf[] = {"CREATED: BMC get file.jed via JTAG\r\n"};
    char create_date[] = {"Tue MAR 07 14:07:04 2021"};
    unsigned char row_ASSIC[2];
    int result = 0;
    
    printf("p1 = %x, p2 = %x \n", s[0], s[1]);

    row_ASSIC[0] = 0xd;
	row_ASSIC[1] = 0xa;


    FILE *pf = fopen("./f1.txt","w");
    result = fwrite(s1, 1, sizeof(s1), pf);
    printf("File_Out result %x \n", result);

    result |= fwrite(design_buf, 1, (sizeof(design_buf)-1), pf); //沒有指定固定size時會自動將 null 加入
    result |= fwrite(row_ASSIC, 1, sizeof(row_ASSIC), pf);
    result |= fwrite(device_buf, 1, (sizeof(device_buf)-1), pf);
    result |= fwrite(create_buf, 1, sizeof(create_buf), pf);
    
    fclose(pf);

    if(result != 0){
        printf("File_Out error \n");
    }


}
