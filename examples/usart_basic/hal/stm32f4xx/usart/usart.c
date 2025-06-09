#include "stm32f407xx.h"
#include "stm32f4xx.h"

#include <stdint.h>
#include <stddef.h>

extern uint32_t SystemCoreClock;

static USART_TypeDef *usart = NULL;

int usart_init(USART_TypeDef * usart_conf, uint32_t baud)
{
    uint32_t c;

    if (usart_conf == NULL) {
        return -1;
    }

    RCC->AHB1ENR	|= RCC_AHB1ENR_GPIOAEN; //enable RCC for port A
    GPIOA->MODER 	|= GPIO_MODER_MODER2_1; // PA2 is Alt fn mode (serial TX in this case)
    GPIOA->AFR[0] 	|= (7 << GPIO_AFRL_AFSEL2_Pos) ; // That alt fn is alt 7 for PA2
    GPIOA->MODER 	|= GPIO_MODER_MODER3_1; // PA3 is Alt fn mode (serial RX in this case)
    GPIOA->AFR[0] 	|= (7 << GPIO_AFRL_AFSEL3_Pos) ; // Alt fn for PA3 is same as for PA2
    RCC->APB1ENR  |=  RCC_APB1ENR_USART2EN; // enable RCC for USART2

    usart = usart_conf;

    /* Set uart baud rate (with mantissa and exponent) */
    usart->BRR = ((((SystemCoreClock / baud) / 16) << USART_BRR_DIV_Mantissa_Pos) |
                  (((SystemCoreClock / baud) % 16) << USART_BRR_DIV_Fraction_Pos));

    /* Enable USART transmit and receive */
    usart->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;

    /* clear garbage if any */
    while (usart->SR & USART_SR_RXNE) {c = usart->DR;}

    return 0;
}

char usart_putchar(char c)
{
    if (usart == NULL) {
        return -1;
    }

    while (!(usart->SR & USART_SR_TXE)); // wait until we are able to transmit
    usart->DR = c; // transmit the character

    return c;
}

char usart_getchar()
{
    if (usart == NULL) {
        return -1;
    }

    while (!(usart->SR & USART_SR_RXNE)); // wait until we are able to transmit

    return usart->DR; // transmit the character
}

char *usart_puts(char *s)
{
    if (usart == NULL) {
        return NULL;
    }

    while (*s != '\0') {
        usart_putchar(*s++);
    }

    return s;
}
