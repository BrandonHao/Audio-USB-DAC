#ifndef USB_DEFS_H_
#define USB_DEFS_H_

#include "usb_types.h"

#define USB_EP_OUT(addr)            ((addr) | 0x00)
#define USB_EP_IN(addr)             ((addr) | 0x80)

/* Get the LSB of a uint16_t */
#define LSB_16(x)                   (x & 0xFF)
/* Get the MSB of a uint16_t */
#define MSB_16(x)                   ((x >> 8) & 0xFF)

/* Device Descriptor */
#define USB_DEV_DESC_SIZE           sizeof(usbDevDesc_t)
#define USB_DEV_DESC_TYPE           0x01
#define USB_DEV_210                 0x0200

#define USB_EP_DESC_SIZE            sizeof(usbEpDesc_t)
#define USB_EP_DESC_TYPE            0x05

#define USB_ASSOC_DESC_SIZE         sizeof(usbIfaceAssocDesc_t)
#define USB_ASSOC_DESC_TYPE         0x0B
#define USB_AUDIO_IFACE_CLASS       0x01
#define USB_AUDIO_IFACE_PROTOCOL    0x20

#define USB_IFACE_DESC_SIZE         sizeof(usbIfaceDesc_t)
#define USB_IFACE_DESC_TYPE         4

#define USB_CTR_DESC_SIZE           sizeof(usbCtrIfaceHeader_t)
#define USB_CTR_DESC_TYPE           0x24
#define USB_CTR_DESC_SUBTYPE        0x01
#define USB_CTR_ADC                 0x0200
#define USB_CTR_DESC_CAT            0x0A
#define USB_CTR_TOTAL_LEN           (USB_CTR_DESC_SIZE + USB_CTR_IN_DESC_SIZE \
                                     + USB_CTR_OUT_DESC_SIZE + \
                                    USB_CTR_FEAT_DESC_SIZE + USB_EP_DESC_SIZE \
                                    + sizeof(usbCtrlIfaceClock_t))

#define USB_CTR_IN_DESC_SIZE        sizeof(usbCtrIfaceInTerm_t)
#define USB_CTR_IN_DESC_TYPE        USB_CTR_DESC_TYPE
#define USB_CTR_IN_DESC_SUBTYPE     0x02
#define USB_CTR_IN_TERM_ID          0x01
#define USB_CTR_IN_TERM_TYPE        0x0101
#define USB_CTR_IN_ASSOC_TERM       0x00
#define USB_CTR_IN_SOURCE_ID        0x12
#define USB_CTR_IN_NR_CHAN          0x00
#define USB_CTR_IN_CHAN_CONFIG      0x00000000
#define USB_CTR_IN_CHAN_NAMES       0x00
#define USB_CTR_IN_CONTROLS         0x0040

#define USB_CTR_OUT_DESC_SIZE       sizeof(usbCtrIfaceOutTerm_t)
#define USB_CTR_OUT_DESC_TYPE       USB_CTR_DESC_TYPE
#define USB_CTR_OUT_DESC_SUBTYPE    0x03
#define USB_CTR_OUT_TERM_ID         0x02
#define USB_CTR_OUT_TERM_TYPE       0x0301
#define USB_CTR_OUT_SOURCE_ID       0x03
#define USB_CTR_OUT_CSOURCE_ID      0x04

#define USB_CTR_FEAT_DESC_SIZE      sizeof(usbCtrIfaceFeat_t)
#define USB_CTR_FEAT_DESC_TYPE      USB_CTR_DESC_TYPE
#define USB_CTR_FEAT_DESC_SUBTYPE   0x06
#define USB_CTR_FEAT_UNIT_ID        0x03
#define USB_CTR_FEAT_SOURCE_ID      0x02
#define USB_CTR_FEAT_BM_CTR_0       0x00000003
#define USB_CTR_FEAT_BM_CTR_1       0x00000000
#define USB_CTR_FEAT_BM_CTR_2       0x00000000

#define USB_CTR_EP_MAX_PK_SIZE      0x0006
#define USB_CTR_EP_INTERVAL         0x04

#define USB_STREAM_GEN_DESC_SIZE    sizeof(usbStreamGenDesc_t)
#define USB_STREAM_DESC_TYPE        USB_CTR_DESC_TYPE
#define USB_STREAM_GEN_DESC_STYPE   0x01
#define USB_STREAM_GEN_TERM_LINK    0x01
#define USB_STREAM_CONTROLS         0x05
#define USB_STREAM_FORMATS          0x00000001
#define USB_STREAM_NR_CHANNELS      0x02
#define USB_STREAM_CHAN_CONFIG      0x00000003
#define USB_STREAM_ICHANNEL_NAMES   0x00

#define USB_STRM_FORMAT_DESC_SIZE   sizeof(usbStreamFormatDesc_t)
#define USB_STRM_FORMAT_DESC_TYPE   USB_CTR_DESC_TYPE
#define USB_STRM_FORMAT_DESC_STYPE  0x02
#define USB_STREAM_FORMAT_TYPE      0x01
#define USB_STRM_FORMAT_SLOT_SIZE   0x02
#define USB_STRM_FORMAT_BIT_RES     0x10

#define USB_STREAM_EP_DESC_ATTR     0x05
#define USB_FEEDBACK_EP_DESC_ATTR   0x11

#define USB_AU_STREAM_EP_DESC_TYPE  0x25

#define USB_CONFIG_DESC_SIZE        (sizeof(usbConfigDesc_t) + USB_ASSOC_DESC_SIZE + USB_IFACE_DESC_SIZE + USB_CTR_DESC_SIZE + USB_CTR_IN_DESC_SIZE + USB_CTR_OUT_DESC_SIZE + USB_CTR_FEAT_DESC_SIZE + sizeof(usbCtrlIfaceClock_t) + USB_EP_DESC_SIZE + USB_IFACE_DESC_SIZE + USB_IFACE_DESC_SIZE + USB_STREAM_GEN_DESC_SIZE + USB_STRM_FORMAT_DESC_SIZE + USB_EP_DESC_SIZE + sizeof(usbAudioStreamEpDesc_t) + USB_EP_DESC_SIZE)

#endif