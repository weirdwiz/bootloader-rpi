CC = aarch64-elf-gcc
LD = aarch64-elf-ld
OBJCPY = aarch64-elf-objcopy

SOURCE = src/
BUILD = build/

CFLAGS = -Wall -O2 -ffreestanding
LDFLAGS  = -nostdlib -nostdinc -nostartfiles

SRCS = $(patsubst $(SOURCE)%.c,$(BUILD)%.o, $(wildcard $(SOURCE)*.c))
OBJS = $(SRCS:.c=.o)

all: $(BUILD)kernel8.img


$(BUILD)%.o: $(SOURCE)%.S $(BUILD)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(BUILD)font_psf.o: $(SOURCE)font.psf
	aarch64-elf-ld -r -b binary -o $(BUILD)font_psf.o $(SOURCE)font.psf

$(BUILD)font_sfn.o: $(SOURCE)font.sfn
	aarch64-elf-ld -r -b binary -o $(BUILD)font_sfn.o $(SOURCE)font.sfn


OBJS += $(BUILD)boot.o $(BUILD)font_psf.o $(BUILD)font_sfn.o

$(BUILD)%.o: $(SOURCE)%.c $(BUILD)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(BUILD)kernel8.elf: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -T link.ld -o  $@


$(BUILD)kernel8.img: $(BUILD)kernel8.elf
	$(OBJCPY) -O binary $< $@

$(BUILD):
	mkdir $@

run:
	qemu-system-aarch64 -M raspi3 -kernel $(BUILD)kernel8.img -serial stdio
