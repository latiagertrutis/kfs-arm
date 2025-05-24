.PHONY: all clean

TARGET = example_boot.elf

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld

SRCS = main.c
OBJS = $(SRCS:.c=.o)
LD_SCRIPT = ./scripts/stm32f4.ld

CPPFLAGS = -mcpu=cortex-m4 -mthumb -g -O0
LDFLAGS = -T $(LD_SCRIPT) --verbose

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf $(TARGET) $(OBJS)
