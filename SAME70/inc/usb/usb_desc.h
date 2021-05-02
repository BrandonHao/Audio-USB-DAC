#ifndef USB_DESC_H_
#define USB_DESC_H_

#include <stdint.h>
#include "usb_types.h"

extern const uint8_t sd_vendor[];
extern const uint8_t sd_product[];
extern const uint8_t sd_serial[];
extern const uint8_t sd_lang_ID[];

extern const uint8_t dev_desc[];
extern const uint8_t config_desc[];

extern const uint8_t vendor_desc_size;
extern const uint8_t product_desc_size;
extern const uint8_t serial_desc_size;
extern const uint8_t lang_ID_desc_size;

extern const uint8_t dev_desc_size;
extern const uint8_t config_desc_size;

#endif