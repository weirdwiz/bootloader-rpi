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

OBJS += $(BUILD)boot.o

$(BUILD)%.o: $(SOURCE)%.c $(BUILD)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(BUILD)kernel8.elf: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -T link.ld -o  $@


$(BUILD)kernel8.img: $(BUILD)kernel8.elf
	$(OBJCPY) -O binary $< $@

$(BUILD):
	mkdir $@
