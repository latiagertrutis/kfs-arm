#include "stm32f4xx.h"
#include "hal/stm32f4xx_usart_hal.h"

int main(void)
{
    char c;

    usart_init(USART2, 115200);

    usart_puts("Hello 42!\r\n");

    while (1) {
        c = usart_getchar();
        if (c < 0) {
            usart_puts("Error in getchar!\r\n");
            continue;
        }

        switch (c) {
        case 32 ... 126:
            usart_putchar(c);
            break;
        case '\r':
            usart_puts("\r\n");
            break;
        case '\b':
        case 127:
            usart_puts("\b \b");
            break;
        }
    }
}
