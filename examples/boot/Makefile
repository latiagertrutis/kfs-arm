.PHONY: all clean

TARGET = example_boot.elf

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc

SRCS = main.c board/stm32f407vg/startup.c
OBJS = $(SRCS:.c=.o)
LD_SCRIPT = ./scripts/stm32f4.ld

CPPFLAGS = -mcpu=cortex-m4 -mthumb -g -O0 -std=c11
LDFLAGS =	-mcpu=cortex-m0 \
		-mthumb \
		-nostartfiles \
		--specs=nosys.specs \
		--specs=nano.specs \
		-T $(LD_SCRIPT)

all: $(TARGET)

$(TARGET): $(LD_SCRIPT) $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf $(TARGET) $(OBJS)
