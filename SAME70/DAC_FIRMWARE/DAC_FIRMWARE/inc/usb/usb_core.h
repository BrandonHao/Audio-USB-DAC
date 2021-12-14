#ifndef USB_CORE_H_
#define USB_CORE_H_

#include <stdint.h>

#define EP_COUNT            0x04

#define EP_CONTROL          0x00
#define EP_AUDIO_CONTROL    0x01
#define EP_AUDIO_STREAM     0x02
#define EP_AUDIO_FEEDBACK   0x03

typedef struct{
    uint8_t ep_num;
    uint8_t ep_type;
    uint8_t *fifo_addr;
    uint8_t *data_buf;
    uint16_t max_packet_size;
    uint16_t max_buf_len;
    uint16_t data_len;
}usb_ep_t;

extern usb_ep_t endpoints[EP_COUNT];

void usb_init(void);

#endif