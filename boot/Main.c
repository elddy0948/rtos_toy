#include "stdint.h"

#include "HalUart.h"

static void Hw_init(void);

void main(void)
{
    uint8_t i = 0;
    uint8_t flag = 0;

    char* test_str = "Hello";

    Hw_init();


    while (1) {
        if (!flag)
        {
            for (i = 0; test_str[i]; ++i)
            {
                Hal_uart_put_char(test_str[i]);
            }
            Hal_uart_put_char('\n');
            flag = 1;
        }
    }
}

static void Hw_init(void)
{
    Hal_uart_init();
}