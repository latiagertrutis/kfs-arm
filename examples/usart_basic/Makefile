.PHONY: all clean

TARGET = example_boot.elf

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc

HAL =	$(addprefix hal/stm32f4xx/,usart/usart.c)
SRC =	src/main.c board/stm32f407vg/startup.c \
	$(HAL)


OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

LD_SCRIPT = ./scripts/stm32f4.ld

INCLUDE_DIRS = 	-Iinclude/stm32f4xx
CPPFLAGS = 	-mcpu=cortex-m4 -mthumb -g -O0 -std=c11 \
		$(INCLUDE_DIRS)

LDFLAGS =	-mcpu=cortex-m0 \
		-mthumb \
		-nostartfiles \
		--specs=nosys.specs \
		--specs=nano.specs \
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
	@rm -rf $(TARGET) $(OBJ)
