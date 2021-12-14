#ifndef USB_TYPES_H_
#define USB_TYPES_H_

#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint16_t    bcdUSB;
    uint8_t     bDeviceClass;
    uint8_t     bDeviceSubClass;
    uint8_t     bDeviceProtocol;
    uint8_t     bMaxPacketSize0;
    uint16_t    idVendor;
    uint16_t    idProduct;
    uint16_t    bcdDevice;
    uint8_t     iManufacturer;
    uint8_t     iProduct;
    uint8_t     iSerialNumber;
    uint8_t     bNumConfigurations;
}
usbDevDesc_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bFirstInterface;
    uint8_t     bInterfaceCount;
    uint8_t     bFunctionClass;
    uint8_t     bFunctionSubClass;
    uint8_t     bFunctionProtocol;
    uint8_t     iIfaceAssoc;
}
usbIfaceAssocDesc_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bInterfaceNumber;
    uint8_t     bAlternateSetting;
    uint8_t     bNumEndpoints;
    uint8_t     bInterfaceClass;
    uint8_t     bInterfaceSubClass;
    uint8_t     bInterfaceProtocol;
    uint8_t     iInterface;
}
usbIfaceDesc_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint16_t    bcdAdc;
    uint8_t     bCategory;
    uint16_t    wTotalLength;
    uint8_t     bmControls;
}
usbCtrIfaceHeader_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint16_t    bTerminalId;
    uint16_t    wTerminalType;
    uint8_t     bAssocTerminal;
    uint8_t     bCSourceId;
    uint8_t     bNrChannels;
    uint32_t    bmChannelConfig;
    uint8_t     iChannelNames;
    uint8_t     bmControls;
    uint8_t     iTerminal;
}
usbCtrIfaceInTerm_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint16_t    bTerminalId;
    uint16_t    wTerminalType;
    uint8_t     bAssocTerminal;
    uint8_t     bSourceID;
    uint8_t     bCSourceId;
    uint8_t     bmControls;
    uint8_t     iTerminal;
}usbCtrIfaceOutTerm_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint8_t    bClockID;
    uint8_t     bmAttributes;
    uint8_t     bmControls;
    uint8_t     bAssocTerminal;
    uint8_t     iClock;
}usbCtrlIfaceClock_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint8_t     bUnitId;
    uint8_t     bSourceID;
    uint32_t    bmControls0;
    uint32_t    bmControls1;
    uint32_t    bmControls2;
    uint8_t     iFeature;
}
usbCtrIfaceFeat_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint8_t     bTerminalLink;
    uint8_t     bmControls;
    uint8_t     bFormatType;
    uint32_t    bmFormats;
    uint8_t     bNrChannels;
    uint32_t    bmChannelConfig;
    uint8_t     iChannelNames;
}
usbStreamGenDesc_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint8_t     bFormatType;
    uint8_t     bSubSlotSize;
    uint8_t     bBitResolution;
}
usbStreamFormatDesc_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bEndpointAddress;
    uint8_t     bmAttributes;
    uint16_t    wMaxPacketSize;
    uint8_t     bInterval;
}
usbEpDesc_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint8_t     bmAttributes;
    uint8_t     bmControls;
    uint8_t     bLockDelayUnits;
    uint16_t    wLockDelay;
}usbAudioStreamEpDesc_t;

typedef struct __attribute__((packed)) {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint16_t    wTotalLength;
    uint8_t     bNumInterfaces;
    uint8_t     bConfigValue;
    uint8_t     iConfig;
    uint8_t     bmAttr;
    uint8_t     bMaxPower;
}usbConfigDesc_t;

#endif