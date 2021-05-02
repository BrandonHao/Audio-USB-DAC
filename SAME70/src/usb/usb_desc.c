#include "usb_desc.h"
#include "usb_defs.h"
#include "std_inc.h"

#define WVAL(x)         (x & 0xFF), ((x >> 8) & 0xFF)
#define WVAL_32(x)      (x & 0xFF), ((x >> 8) & 0xFF), ((x >> 16) & 0xFF), ((x >> 24) & 0xFF)

/* USB String Descriptors */
const uint8_t sd_vendor[] = {
	0x18, // Size,
	0x03, // Descriptor type
	'B', 0, 'r', 0, 'a', 0, 'n', 0, 'd', 0, 'o', 0, 'n', 0, ' ', 0, 'H', 0,
	'a', 0, 'o', 0
};

const uint8_t sd_product[] = {
	0x08, // Size,
	0x03, // Descriptor type
	'D', 0, 'A', 0, 'C', 0
};

const uint8_t sd_serial[] = {
	0x16, // Size,
	0x03, // Descriptor type
	'1',0,'2',0,'3',0,'4',0,'5',0,'6',0,'7',0,'8',0,'9',0,'0',0
};

const uint8_t sd_lang_ID[] = {
		0x04, // Size,
		0x03, // Descriptor type
		0x09, 0x04
};

/* Device Descriptor */
const uint8_t dev_desc[] = {
    USB_DEV_DESC_SIZE,	/* Size of the device desc */
    USB_DEV_DESC_TYPE,
    WVAL(USB_DEV_210),
    0xEF,				/* Device class (IFace Defined) */
    0x02,				/* Device subclass (IFace Defined) */
    0x01,				/* Device protocol (IFace Defined) */
    0x40,				/* EP 0 max packet size (8 bytes) */
    WVAL(0x0001),				/* Vendor ID (0 for now) */
    WVAL(0x0001),				/* Product ID (0 for now) */
    WVAL(0x0001),				/* Device release number (1 for now) */
    0x01,				/* MFG string index */
    0x02,				/* Product string index */
    0x00,				/* Serial number string index */
    0x01				/* Number of configurations */
};

const uint8_t config_desc[] = {
    //Config Desc
    sizeof(usbConfigDesc_t),
    0x02,
    WVAL(USB_CONFIG_DESC_SIZE),
    0x02,
    0x01,
    0x00,
    0x80,
    0x32,
    //Config End
    //Interface Association Desc
    USB_ASSOC_DESC_SIZE,
    USB_ASSOC_DESC_TYPE,
    0x00,						/* Index of first iface in this assoc */
    0x02,						/* Num of interfaces */
    USB_AUDIO_IFACE_CLASS,
    0x00,						/* Function subclass (none) */
    USB_AUDIO_IFACE_PROTOCOL,
    0x00,						/* iFunction */
    //Interface Association End
    //Control Interface Desc
    USB_IFACE_DESC_SIZE,
    USB_IFACE_DESC_TYPE,
    0x00,						/* Iface num 0 */
    0x00,						/* Alternate settings (none) */
    0x01,						/* 1 EP */
    0x01,						/* Audio interface class */
    0x01,						/* Control subclass */
    USB_AUDIO_IFACE_PROTOCOL,
    0x04,
    //Control Interface End
    //Control Header Desc
    USB_CTR_DESC_SIZE,
    USB_CTR_DESC_TYPE,
    USB_CTR_DESC_SUBTYPE,
    WVAL(USB_CTR_ADC),
    USB_CTR_DESC_CAT,
    WVAL(USB_CTR_TOTAL_LEN),
    0x00,
    //Control Header End
    //In Term Desc
    USB_CTR_IN_DESC_SIZE,
    USB_CTR_IN_DESC_TYPE,
    USB_CTR_IN_DESC_SUBTYPE,
    USB_CTR_IN_TERM_ID,
    WVAL(USB_CTR_IN_TERM_TYPE),
    USB_CTR_IN_ASSOC_TERM,
    0x04,
    USB_CTR_IN_NR_CHAN,
    WVAL_32(USB_CTR_IN_CHAN_CONFIG),
    USB_CTR_IN_CHAN_NAMES,
    WVAL(USB_CTR_IN_CONTROLS),
    0x00,
    //In Term End
    //Out Term Desc
    USB_CTR_OUT_DESC_SIZE,
    USB_CTR_OUT_DESC_TYPE,
    USB_CTR_OUT_DESC_SUBTYPE,
    USB_CTR_OUT_TERM_ID,
    WVAL(USB_CTR_OUT_TERM_TYPE),
    0x00,
    USB_CTR_OUT_SOURCE_ID,
    USB_CTR_OUT_CSOURCE_ID,
    0x00,
    0x00,
    0x00,
    //Out Term End
    //Feat Unit Desc
    USB_CTR_FEAT_DESC_SIZE,
    USB_CTR_FEAT_DESC_TYPE,
    USB_CTR_FEAT_DESC_SUBTYPE,
    USB_CTR_FEAT_UNIT_ID,
    USB_CTR_FEAT_SOURCE_ID,
    WVAL_32(USB_CTR_FEAT_BM_CTR_0),
    WVAL_32(USB_CTR_FEAT_BM_CTR_1),
    WVAL_32(USB_CTR_FEAT_BM_CTR_2),
    0x00,
    //Feat Unit End
    //Clock Source Desc
    sizeof(usbCtrlIfaceClock_t),
    USB_CTR_FEAT_DESC_TYPE,
    0x0A,
    0x04,
    0x03,
    0x07,
    0x00,
    0x00,
    //Clock Source End
    //Control EP Desc
    USB_EP_DESC_SIZE,
    USB_EP_DESC_TYPE,
    USB_EP_IN(0x01),
    0x03,
    WVAL(USB_CTR_EP_MAX_PK_SIZE),
    USB_CTR_EP_INTERVAL,
    //Control EP End
    //Alt Stream Interface Desc
    USB_IFACE_DESC_SIZE,
    USB_IFACE_DESC_TYPE,
    0x01,
    0x00,
    0x00,
    0x01,
    0x02,
    0x20,
    0x00,
    //Alt Stream Interface End
    //Stream Interface Desc
    USB_IFACE_DESC_SIZE,
    USB_IFACE_DESC_TYPE,
    0x01,
    0x01,
    0x02,
    0x01,
    0x02,
    0x20,
    0x00,
    //Stream Interface End
    //AS General Desc
    USB_STREAM_GEN_DESC_SIZE,
    USB_STREAM_DESC_TYPE,
    USB_STREAM_GEN_DESC_STYPE,
    USB_STREAM_GEN_TERM_LINK,
    USB_STREAM_CONTROLS,
    0x01,
    WVAL_32(USB_STREAM_FORMATS),
    USB_STREAM_NR_CHANNELS,
    WVAL_32(USB_STREAM_CHAN_CONFIG),
    USB_STREAM_ICHANNEL_NAMES,
    //AS General End
    //Stream Format Desc
    USB_STRM_FORMAT_DESC_SIZE,
    USB_STREAM_DESC_TYPE,
    USB_STRM_FORMAT_DESC_STYPE,
    USB_STREAM_FORMAT_TYPE,
    USB_STRM_FORMAT_SLOT_SIZE,
    USB_STRM_FORMAT_BIT_RES,
    //Stream Format End
    //Stream EP Desc
    USB_EP_DESC_SIZE,
    USB_EP_DESC_TYPE,
    USB_EP_OUT(0x02),
    USB_STREAM_EP_DESC_ATTR,
    WVAL(0x0068),
    0x01,
    //Stream EP End
    //Stream EP Info Desc
    0x08,
    USB_AU_STREAM_EP_DESC_TYPE,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    //Stream EP Info End
    //Stream Feedback Desc
    USB_EP_DESC_SIZE,
    USB_EP_DESC_TYPE,
    USB_EP_IN(0x03),
    USB_FEEDBACK_EP_DESC_ATTR,
    WVAL(0x0004),
    0x04
    //Stream Feedback End
};

const uint8_t vendor_desc_size = sizeof(sd_vendor);
const uint8_t product_desc_size = sizeof(sd_product);
const uint8_t serial_desc_size = sizeof(sd_serial);
const uint8_t lang_ID_desc_size = sizeof(sd_lang_ID);

const uint8_t dev_desc_size = sizeof(dev_desc);
const uint8_t config_desc_size = sizeof(config_desc);
