CC = aarch64-elf-gcc
LD = aarch64-elf-ld
OBJCPY = aarch64-elf-objcopy
CFLAGS = -Wall -O2 -ffreestanding
FLAGS  = -nostdlib -nostdinc -nostartfiles

SRCS = $(wildcard ./src/*.c)
OBJS = $(SRCS:.c=.o)

all: kernel8.img

boot.o: boot.S
	$(CC) $(CFLAGS) $(FLAGS) -c $< -o $@

OBJS+= boot.o

%.o: %.c
	$(CC) $(CFLAGS) $(FLAGS) -c $< -o $@

kernel8.elf: link.ld $(OBJS)
	$(LD) $(FLAGS) $(OBJS) -T $< -o  $@


kernel8.img: kernel8.elf
	$(OBJCPY) -O binary $< $@

