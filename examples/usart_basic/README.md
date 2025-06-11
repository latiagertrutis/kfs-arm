# STM32F4 Example of USART without using the HAL library

Basic example of how to configure the STM32f4-discovery board, for use of the USART1 in blocking mode without using the ST HAL library

## Test With QEMU

In order to test without the real hardware you must have `qemu-system-arm` installed. The following command will start the emultaion in a halted state, and open a gdb server at port `:3333`. Besides that it will open a serial console at `/dev/pts/<n>` mapped to the `USART2`. A qemu prompt will show. In order to start the emulation type `c` (continue). Or connect o the gdb server from `arm-none-eabi-gdb`:

```
$ qemu-system-arm -gdb tcp::3333 \
        -S \
        -cpu cortex-m4 \
        -machine olimex-stm32-h405 \
        -serial null \
        -serial pty \
        -nographic \
        -kernel example_boot.elf
QEMU 10.0.0 monitor - type 'help' for more information
char device redirected to /dev/pts/6 (label serial1)
(qemu) c
```

To connect to the serial you can use any terminal emulation tool, for example, `picocom`. You will see something like this:

```
$ picocom /dev/pts/6
picocom v3.1

port is        : /dev/pts/6
flowcontrol    : none
baudrate is    : 9600
parity is      : none
databits are   : 8
stopbits are   : 1
escape is      : C-a
local echo is  : no
noinit is      : no
noreset is     : no
hangup is      : no
nolock is      : no
send_cmd is    : sz -vv
receive_cmd is : rz -vv -E
imap is        :
omap is        :
emap is        : crcrlf,delbs,
logfile is     : none
initstring     : none
exit_after is  : not set
exit is        : no

Type [C-a] [C-h] to see available commands
Terminal ready

*** baud: 115200

*** baud: 115200 ***
Hello 42!
```

> NOTE: Remember to set baud rate to 115200!

A simple wrapper has been created in the makefile under the sub-command `make test HALT=yes`.
