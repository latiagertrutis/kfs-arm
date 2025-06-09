#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_usart.h"
int main(void)
{
    HAL_Init();

    /* HAL_USART_Init(); */

    static int sum = 42; // Expect 0 according to C standard

    if (sum >= 0) {
        while (1);
    }
    else {
        return 0;
    }
}
