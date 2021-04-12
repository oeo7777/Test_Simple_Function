#ifndef _caL_CheckSum_H_
#define _caL_CheckSum_H_

/************************************************************************
* Utility functions
************************************************************************/

typedef struct checksum{
	unsigned int csValue;
	short int csWidth;
	short int csChunkSize;
} CSU;

void init_CS(CSU *cs, short int width, short int chunkSize);
unsigned int getCheckSum(CSU *cs);
void putChunk(CSU *cs, unsigned int chunk);

extern CSU checkSum_Cal;
extern int Load_and_cal_checksum(void);
#endif