#include "sd.h"
#include "gpio.h"

typedef struct {
	unsigned char BS_jmpBootp[3];
	char BS_OEMName[8];
	unsigned char BPB_BytsPerSec[2];
	unsigned char BPB_SecPerClus;
	unsigned short BPB_RsvdSecCnt;
	unsigned char BPB_NumFATs;
	unsigned short BPB_RootEntCnt;
	unsigned short BPB_TotSec16;
	unsigned char BPB_Media;
	unsigned short BPB_FATSz16;
	unsigned short BPB_SecPerTrk;
	unsigned short BPB_NumHeads;
	unsigned int BPB_HiddSec;
	unsigned int BPB_TotSec32;
	unsigned char BS_DrvNum;
	unsigned char BS_Reserved1;
	unsigned char BS_BootSig;
	unsigned int BS_VolID;
	char BS_VolLab[11];
	char BS_FilSysType[8];
} BPB;


