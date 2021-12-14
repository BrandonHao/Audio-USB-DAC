#ifndef DEBUG_UART_H_
#define DEBUG_UART_H_
#include "stdint.h"

void uart_init(void);
void uart_write(uint8_t *buf, uint8_t size);

#endif