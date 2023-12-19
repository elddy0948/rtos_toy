#pragma once
#ifndef HAL_REALVIEWPB_UART_H
#define HAL_REALVIEWPB_UART_H

typedef unsigned int uint32_t;

typedef union UARTDR_t
{
    uint32_t all;
    // : means bit-fields
    struct
    {
        uint32_t DATA:8;
        uint32_t FE:1;
        uint32_t PE:1;
        uint32_t BE:1;
        uint32_t OE:1;
        uint32_t RES:4;
    } bits;
} UARTDR_t;

typedef union UARTRSR
{
    uint32_t all;

    struct
    {
        uint32_t FE:1;
        uint32_t PE:1;
        uint32_t BE:1;
        uint32_t OE:1;
        uint32_t RES:4;
        uint32_t CLR:8;
    } bits;
} UARTRSR;

typedef union UARTECR
{
    uint32_t all;
    struct
    {
        uint32_t FE:1;
        uint32_t PE:1;
        uint32_t BE:1;
        uint32_t OE:1;
        uint32_t RES:4;
        uint32_t CLR:8;
    } bits;
} UARTECR;

/* FLAG REGISTER */
typedef union UARTFR
{
    uint32_t all;

    struct bits
    {
        uint32_t CTS:1;
        uint32_t DSR:1;
        uint32_t DCD:1;
        uint32_t BUSY:1;
        uint32_t RXFE:1;
        uint32_t TXFF:1;
        uint32_t RXFF:1;
        uint32_t TXFE:1;
        uint32_t RI:1;
        uint32_t RES:7;
    };
} UARTFR;

/* IrDA LOW-POWER COUNTER REGISTER */
typedef union UARTILPR
{
    uint32_t all;
    struct bits
    {
        uint32_t ILPDVSR:8; // 0 is illegal value
    };
} UARTILPR;

/* INTEGER PART OF THE BAUD RATE DIVISOR VALUE */
typedef union UARTIBRD
{
    uint32_t all;
    struct bits
    {
        uint32_t BAUD_DIVINT:16;
    };
} UARTIBRD;

/* FRACTIONAL BAUD RATE DIVISOR VALUE */
typedef union UARTFBRD
{
    uint32_t all;
    struct bits
    {
        uint32_t BAUD_DIVFRAC:6;
    };
} UARTFBRD;

/* UART LINE CONTROL REGISTER */
typedef union UARTLCR_H
{
    uint32_t all;
    struct bits
    {
        uint32_t BRK:1;
        uint32_t PEN:1;
        uint32_t EPS:1;
        uint32_t STP2:1;
        uint32_t FEN:1;
        uint32_t WLEN:2;
        uint32_t SPS:1;
        uint32_t RESERVED:8;
    };
}UARTLCR_H;

/* UART CONTROL REGISTER */
typedef union UARTCR
{
    uint32_t all;
    struct bits
    {
        uint32_t UARTEN:1;
        uint32_t SIREN:1;
        uint32_t SIRLP:1;
        uint32_t RESERVED:4;
        uint32_t LBE:1;
        uint32_t TXE:1;
        uint32_t RXE:1;
        uint32_t DTR:1;
        uint32_t RTS:1;
        uint32_t OUT1:1;
        uint32_t OUT2:1;
        uint32_t RTSEN:1;
        uint32_t CTSEN:1;
    };
} UARTCR;

/* INTERRUPT FIFO LEVEL SELECT REGISTER */
typedef union UARTIFLS
{
    uint32_t all;
    struct bits
    {
        uint32_t TXIFLSEL:3;
        uint32_t RXIFLSEL:3;
        uint32_t RESERVED:10;
    };
} UARTIFLS;

/* INTERRUPT MASK SET/CLEAR REGISTER */
typedef union UARTIMSC
{
    uint32_t all;
    struct bits
    {
        uint32_t RIMIM:1;
        uint32_t CTSMIM:1;
        uint32_t DCDMIM:1;
        uint32_t DSRMIM:1;
        uint32_t RXIM:1;
        uint32_t TXIM:1;
        uint32_t RTIM:1;
        uint32_t FEIM:1;
        uint32_t PEIM:1;
        uint32_t BEIM:1;
        uint32_t OEIM:1;
        uint32_t RESERVED:5;
    };
} UARTIMSC;

/* RAW INTERRUPT STATUS REGISTER */
typedef union UARTRIS
{
    uint32_t all;
    struct bits 
    {
        uint32_t RIRMIS:1;
        uint32_t CTSRMIS:1;
        uint32_t DCDRMIS:1;
        uint32_t DSRRMIS:1;
        uint32_t RXRIS:1;
        uint32_t TXRIS:1;
        uint32_t RTRIS:1;
        uint32_t FERIS:1;
        uint32_t PERIS:1;
        uint32_t BERIS:1;
        uint32_t OERIS:1;
        uint32_t RESERVED:5;
    };
} UARTRIS;

/* MASKED INTERRUPT STATUS REGISTER */
typedef union UARTMIS
{
    uint32_t all;
    struct bits
    {
        uint32_t RIMMIS:1;
        uint32_t CTSMMIS:1;
        uint32_t DCDMMIS:1;
        uint32_t DSRMMIS:1;
        uint32_t RXMIS:1;
        uint32_t TXMIS:1;
        uint32_t RTMIS:1;
        uint32_t FEMIS:1;
        uint32_t PEMIS:1;
        uint32_t BEMIS:1;
        uint32_t OEMIS:1;
        uint32_t RESERVED:5;
    };
} UARTMIS;

/* INTERRUPT CLEAR REGISTER AND WRITE-ONLY */
typedef union UARTICR
{
    uint32_t all;
    struct bits
    {
        uint32_t RIMIC:1;
        uint32_t CTSMIC:1;
        uint32_t DCDMIC:1;
        uint32_t DSRMIC:1;
        uint32_t RXIC:1;
        uint32_t TXIC:1;
        uint32_t RTIC:1;
        uint32_t FEIC:1;
        uint32_t PEIC:1;
        uint32_t BEIC:1;
        uint32_t OEIC:1;
        uint32_t RESERVED:5;
    };
} UARTICR;

typedef union UARTDMACR
{
    uint32_t all;
    struct
    {
        uint32_t RXDMAE:1;
        uint32_t TXDMAE:1;
        uint32_t DMAONERR:1;
        uint32_t RESERVED:13;
    } bits;
} UARTDMACR;

typedef struct PL011_t
{
    UARTDR_t uartdr;        // 0x000
    UARTRSR uartrsr;        // 0x004    
    uint32_t reserved0[4];  // 0x008 - 0x014
    UARTFR uartfr;          // 0x018
    uint32_t reserved1;     // 0x01C
    UARTILPR uartilpr;      // 0x020
    UARTIBRD uartibrd;      // 0x024
    UARTFBRD uartfbrd;      // 0x028
    UARTLCR_H uartlcr_h;    // 0x02C
    UARTCR  uartcr;         // 0x030
    UARTIFLS uartifls;      // 0x034
    UARTIMSC uartimsc;      // 0x038
    UARTRIS uartris;        // 0x03C
    UARTMIS uartmis;        // 0x040
    UARTICR uarticr;        // 0x044
    UARTDMACR uartdmacr;    // 0x048
} PL011_t;

#define UART_BASE_ADDRESS0  0x10009000
#define UART_INTERRUPT0     44

#endif /* HAL_REALVIEWPB_UART_H */