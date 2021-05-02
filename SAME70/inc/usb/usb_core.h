#ifndef USB_CORE_H_
#define USB_CORE_H_

#include <stdint.h>

typedef struct{
    uint8_t ep_num;
    uint8_t ep_type;
    uint8_t *fifo_addr;
    uint8_t data_buf[1024];
    uint8_t max_packet_size;
    uint16_t data_len;
}usb_ep_t;

uint8_t usb_reset_handler(void);
void usb_init(void);

#endif