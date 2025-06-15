.PHONY: all clean

TARGET = example_boot.elf

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
QEMU = qemu-system-arm

HAL =	$(addprefix driver/hal/stm32f4xx/,usart/usart.c)
SRC =	src/main.c board/stm32f407vg/startup.c \
	$(HAL)


OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

LD_SCRIPT = ./scripts/stm32f4.ld

INCLUDE_DIRS = 	-Iinclude -Iinclude/stm32f4xx
CPPFLAGS = 	-mcpu=cortex-m4 -mthumb -g -O0 -std=c11 \
		-fno-builtin \
		$(INCLUDE_DIRS)

# Add this to use newlib nano when it is needed
# --specs=nosys.specs \
# --specs=nano.specs \

LDFLAGS =	-mcpu=cortex-m4 \
		-mthumb \
		-fno-builtin \
		-nostdlib \
		-nodefaultlibs \
		-T $(LD_SCRIPT)

all: $(TARGET)

$(TARGET): $(LD_SCRIPT) $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM -MT '$(@:.d=.o)' $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(DEP)

clean:
	@rm -rf $(TARGET) $(OBJ) $(DEP)

test: $(TARGET)
	$(QEMU) -gdb tcp::3333 \
		$(if $(HALT),-S) \
		-cpu cortex-m4 \
		-machine olimex-stm32-h405 \
		-serial null \
		-serial pty \
		-nographic \
		-kernel $(TARGET)
