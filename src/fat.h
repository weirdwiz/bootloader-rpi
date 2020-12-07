int fat_getpartition(void);
unsigned int fat_getcluster(char *fn);
char *fat_readfile(unsigned int cluster);
