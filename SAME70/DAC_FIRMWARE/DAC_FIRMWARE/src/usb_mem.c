#include "usb_mem.h"

void memset(void *ptr, uint8_t val, uint32_t len) {
    uint8_t *tmp_ptr = (uint8_t *)(ptr);
    for(uint32_t i = 0; i < len; i++) {
        *(tmp_ptr++) = 0;
    }
}
