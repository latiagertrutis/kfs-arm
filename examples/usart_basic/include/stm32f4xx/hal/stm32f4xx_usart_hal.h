#ifndef STM32F4XX_USART_HAL
#define STM32F4XX_USART_HAL

#include "stm32f4xx.h"

#include <stdint.h>

int usart_init(USART_TypeDef * usart, uint32_t baud);
char usart_putchar(char c);
char usart_getchar();
char *usart_puts(char *s);

#endif
