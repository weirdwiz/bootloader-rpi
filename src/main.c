#include "uart.h"
#include "sd.h"
#include "fat.h"

void main()
{
    unsigned int cluster;
    uart_init();
    lfb_init();

    lfb_print(80, 80, "Bootloader project");


    if(sd_init()==SD_OK) {
        if(fat_getpartition()) {
                cluster=fat_getcluster("NORMAL IMG");
		lfb_print(80, 160, "got the image");
                void (*foo)(void) = (void (*)()) fat_readfile(cluster);
		foo();
		lfb_print(80, 170, "not loaded");

        } else {
            uart_puts("FAT partition not found???\n");
        }
    }
    while(1) {
        uart_send(uart_getc());
    }
}
