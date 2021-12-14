#include "usb_iso.h"
#include <same70.h>
#include "usb_core.h"

typedef struct{
    uint8_t *buffer;
    uint8_t *head;
    uint8_t *tail;
    uint16_t len;
} circular_buf_t;

uint8_t audio_bytes[8192];

circular_buf_t usb_audio_buf = {
    .buffer = (uint8_t *)&audio_bytes,
    .head =  (uint8_t *)&audio_bytes,
    .tail = (uint8_t *)&audio_bytes,
    .len = 8192
};

static void read_iso_data(void){
    uint16_t byte_count = USBHS->USBHS_DEVEPTISR[2].bit.BYCT;
    uint8_t *source = endpoints[2].fifo_addr;

    while(byte_count--){
        *(usb_audio_buf.tail++) = *(source++);
    }
}

void handle_stream_data(void){
    USBHS->USBHS_DEVEPTICR[2].bit.RXOUTIC = 1;
    if(usb_audio_buf.buffer - usb_audio_buf.tail < USBHS->USBHS_DEVEPTISR[2].bit.BYCT){
        usb_audio_buf.tail = usb_audio_buf.buffer;
    }
    read_iso_data();
    USBHS->USBHS_DEVEPTIDR[2].bit.FIFOCONC = 1;
}
