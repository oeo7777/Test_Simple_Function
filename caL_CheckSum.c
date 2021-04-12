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


int Load_and_cal_checksum(void){
	FILE *dataFile = fopen("./j1.jed","rb");
	int byteOut, cnt=0;

	if(!dataFile || feof(dataFile)){
		printf("[Load_and_cal_checksum] load file error or eof\n");
		return 0;
	}

	init_CS(&checkSum_Cal, 16, 8);

	/* read a byte and store in *byteOut */
	while(1){
		byteOut = fgetc(dataFile);
/*		if(byteOut == 0xd || byteOut == 0xa){
			;
		}else{
			putChunk(&checkSum_Cal, (unsigned int) byteOut);
			cnt++;
		}
*/
		//if(byteOut == 0x30 || byteOut == 0x31){
			putChunk(&checkSum_Cal, (unsigned int) byteOut);
			cnt++;
		//}

		if(cnt <= 50){
			printf("byteOut %x, checksum %x, cnt %d\n", byteOut, checkSum_Cal.csValue, cnt);
		}

		if(cnt >= 1441255){
			printf("byteOut %x, checksum %x, cnt %d\n", byteOut, checkSum_Cal.csValue, cnt);
		}
		if(feof(dataFile)){
			printf("byteOut %x, checksum %x, cnt %d\n", byteOut, checkSum_Cal.csValue, cnt);
			return 0;
		}
	}
	
}