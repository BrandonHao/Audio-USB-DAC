#include "debug_uart.h"
#include <same70.h>

#define BAUD_RATE       1000000U

uint8_t uart_buf[257];
uint8_t *curr_index;
uint16_t data_size;

void irq_handler_uart0(void){
    if(curr_index - uart_buf == data_size){
        UART0->UART_IDR.bit.TXRDY = 1;
    }
    UART0->UART_THR.bit.TXCHR = *(curr_index++);
}

void uart_init(void){
    PMC->PMC_PCER0.reg |= PMC_PCER0_PID7;
    PIOA->PIO_ABCDSR[0].bit.P10 = 0;
    PIOA->PIO_ABCDSR[1].bit.P10 = 1;
    PIOA->PIO_PDR.bit.P10 = 1;

    UART0->UART_BRGR.reg = 10;
    UART0->UART_CR.bit.TXEN = 1;
}

void uart_write(uint8_t *buf, uint8_t size){
    uint8_t i = 0;
    for(; i < size; i++){
        *(uart_buf + i) = *(buf + i);
    }
    *(uart_buf + i + 1) = '\r';
    *(uart_buf + i + 2) = '\n';
    data_size = size + 2;
    curr_index = uart_buf;

    UART0->UART_THR.bit.TXCHR = *(curr_index++);
    while(!UART0->UART_SR.bit.TXRDY);
    UART0->UART_THR.bit.TXCHR = *(curr_index++);
    UART0->UART_IER.bit.TXRDY = 1;
}