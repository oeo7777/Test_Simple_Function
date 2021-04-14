/************************************************************************
* Lattice Semiconductor Corp. Copyright 2008
*
* Utility functions
*
************************************************************************/
#include <stdio.h>
#include <string.h>
#include "caL_CheckSum.h"

CSU checkSum_Cal;
unsigned short currentByte = 0;

void init_CS(CSU *cs, short int width, short int chunkSize){
	cs->csWidth = width;
	cs->csChunkSize = chunkSize;
	cs->csValue = 0;
}

unsigned int getCheckSum(CSU *cs){
	unsigned int mask = 0xFFFFFFFF;

	mask >>= (32 - cs->csWidth);
	return (cs->csValue & mask);
}

void putChunk(CSU *cs, unsigned int chunk){
	unsigned int mask = 0xFFFFFFFF;

	mask >>= (32 - cs->csChunkSize);
	cs->csValue += (chunk & mask);
}

unsigned int jed_file_paser_header(FILE *jed_fd)
{
	//file
	char tmp_buf[160];


	//Header paser
	while (fgets(tmp_buf, 120, jed_fd) != NULL) {
		//printf("[jed_file_paser_header] %s \n", tmp_buf);
		if (tmp_buf[0] == 0x4C) { // "L"
			//printf("[jed_file_paser_header] enter break \n");
			break;
		}else{
			; //printf("[jed_file_paser_header] tmp[0] %x\n", tmp_buf[0]);
		}
	}

	return 0;
}

int Load_and_cal_checksum(char *out_name){
	FILE *dataFile = fopen(out_name,"rb");
	int byteOut, cnt=0, row, line, i;

	if(!dataFile || feof(dataFile)){
		printf("[Load_and_cal_checksum] load file error or eof\n");
		return 0;
	}

	init_CS(&checkSum_Cal, 16, 8);

	/* read a byte and store in *byteOut */
	while(1){
		byteOut = fgetc(dataFile);
		//if(byteOut == 0x30 || byteOut == 0x31){
			if(byteOut != 0xffffffff){
				putChunk(&checkSum_Cal, (unsigned int) byteOut);
				cnt++;
			}
		//}

		if((checkSum_Cal.csValue & 0xffff) == 0xA828){
			line = cnt / 130;
			printf("checksum %x, line %d, cnt = %d\n", checkSum_Cal.csValue, line, cnt);
		}

		if(byteOut == 0xffffffff){
			if((checkSum_Cal.csValue & 0xffff) >= 0xA828){
				printf("diff + %x, checksum %x\n", (checkSum_Cal.csValue & 0xffff) - 0xA828, checkSum_Cal.csValue);
			}else{
				printf("diff - %x, checksum %x\n", 0xA828 - (checkSum_Cal.csValue & 0xffff) , checkSum_Cal.csValue);
			}
			line = cnt / 130;
			printf("line %d, cnt %d  ", line, cnt);
			return 0;
		}
	}
	
	fclose(dataFile);
}

int Load_and_cal_Fuse_checksum(char *out_name){
	FILE *dataFile = fopen(out_name,"rb");
	int byteOut, value=0, tmp, cnt=0, row, line, i;

	if(!dataFile || feof(dataFile)){
		printf("[Load_and_cal_checksum] load file error or eof\n");
		return 0;
	}

	init_CS(&checkSum_Cal, 16, 8);
	i = 0;
	while(1){
		byteOut = fgetc(dataFile);
		if(byteOut == 0x30 || byteOut == 0x31){
			tmp = (byteOut == 0x31) ? 1 : 0;
			value |= (tmp << i);
			i++;
			if(i>=8){
				putChunk(&checkSum_Cal, (unsigned int) value);
				value = 0;
				i = 0;
				cnt++;
			}
		}

		//if(cnt > 10)
		//	return 0;

		if(byteOut == 0xffffffff){
			if((checkSum_Cal.csValue & 0xffff) >= 0xA828){
				printf("diff + %x, checksum %x\n", (checkSum_Cal.csValue & 0xffff) - 0xA828, checkSum_Cal.csValue);
			}else{
				printf("diff - %x, checksum %x\n", 0xA828 - (checkSum_Cal.csValue & 0xffff) , checkSum_Cal.csValue);
			}
			line = cnt / 130;
			printf("line %d, cnt %d  ", line, cnt);
			return 0;
		}
	}
	fclose(dataFile);
}