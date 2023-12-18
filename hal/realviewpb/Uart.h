#pragma once
#ifndef HAL_REALVIEWPB_UART_H
#define HAL_REALVIEWPB_UART_H

typedef union UARTDR_t
{
    unsigned int all;
    // : means bit-fields
    // TODO: - read PL011 data sheet page 50~ then make register
    struct
    {
        unsigned int DATA:8;
        unsigned int FE:1;
    } bits;
};

// TODO: - UARTSR
// uint32_t reserved0[4] // 0x008 - 0x014
// TODO: - UARTFR
// ...
// TODO: - ~UARTDMACR

typedef struct PL011_t
{
    // TODO: - BASE ADDRESS FOR REGISTER
};

#endif /* HAL_REALVIEWPB_UART_H */