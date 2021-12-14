#include "usb_core.h"
#include <same70.h>
#include "usb_desc.h"
#include "usb_iso.h"
#include "usb_aud_ctr.h"

/* USB Standard Request Type Codes */
#define USB_REQ_TYPE_HOST_TO_DEV        0x00
#define USB_REQ_TYPE_DEV_TO_HOST        0x80
#define USB_REQ_TYPE_STANDARD           0x00
#define USB_REQ_TYPE_CLASS              0x20
#define USB_REQ_TYPE_VENDOR             0x40
#define USB_DEVICE_REQ_MASK             0x00
#define USB_INTERFACE_REQ_MASK          0x01
#define USB_EP_REQ_MASK                 0x02

/* USB Standard Request Codes */
#define USB_REQUEST_GET_STATUS			0x00
#define USB_REQUEST_CLEAR_FEATURE		0x01
#define USB_REQUEST_SET_FEATURE			0x03
#define USB_REQUEST_SET_ADDRESS			0x05
#define USB_REQUEST_GET_DESCRIPTOR		0x06
#define USB_REQUEST_SET_DESCRIPTOR		0x07
#define USB_REQUEST_GET_CONFIGURATION	0x08
#define USB_REQUEST_SET_CONFIGURATION	0x09
#define USB_REQUEST_GET_INTERFACE		0x0A
#define USB_REQUEST_SET_INTERFACE		0x0B
#define USB_REQUEST_SYNC_FRAME			0x0C

/* USB Descriptor Types */
#define USB_DEVICE_DESC_TYPE			0x01
#define USB_CFG_DESC_TYPE			    0x02
#define USB_STR_DESC_TYPE			    0x03
#define USB_IFACE_DESC_TYPE			    0x04
#define USB_EP_DESC_TYPE				0x05
#define USB_DEVICE_QR_DESC_TYPE		    0x06
#define USB_OSPEED_CFG_DESC_TYPE		0x07
#define USB_IFACE_PWR_DESC_TYPE		    0x08
#define USB_REPORT_DESC_TYPE			0x22

#define USB_DPRAM_BASE      0xA0100000u

uint8_t ctr_buf[64];
uint8_t audio_ctr_buf[64];
uint8_t feedback_buf[8];

usb_ep_t endpoints[EP_COUNT] = {
    {
        .ep_num = EP_CONTROL,
        .fifo_addr = (uint8_t*)&((volatile uint8_t(*)[0x8000])USB_DPRAM_BASE)[EP_CONTROL],
        .data_buf = ((uint8_t *)ctr_buf),
        .max_packet_size = 64,
        .max_buf_len = 64
    },
    {
        .ep_num = EP_AUDIO_CONTROL,
        .fifo_addr = (uint8_t*)&((volatile uint8_t(*)[0x8000])USB_DPRAM_BASE)[EP_AUDIO_CONTROL],
        .data_buf = (uint8_t *)audio_ctr_buf,
        .max_packet_size = 64,
        .max_buf_len = 64
    },
    {
        .ep_num = EP_AUDIO_STREAM,
        .fifo_addr = (uint8_t*)&((volatile uint8_t(*)[0x8000])USB_DPRAM_BASE)[EP_AUDIO_STREAM],
        .data_buf = 0,
        .max_packet_size = 256,
        .max_buf_len = 0
    },
    {
        .ep_num = EP_AUDIO_FEEDBACK,
        .fifo_addr = (uint8_t*)&((volatile uint8_t(*)[0x8000])USB_DPRAM_BASE)[EP_AUDIO_FEEDBACK],
        .data_buf = (uint8_t *)feedback_buf,
        .max_packet_size = 8,
        .max_buf_len = 8
    }
};

uint8_t dev_configured;

typedef union{
    struct{
        uint8_t L;
        uint8_t H;
    }byte;
    uint16_t val_16;
}uint16_union_t;

typedef struct {
    uint8_t request_type;
    uint8_t request;
    uint16_union_t value;
    uint16_union_t index;
    uint16_union_t length;
}setup_packet_t;


static setup_packet_t parse_setup_packet(uint8_t ep_num) {
    setup_packet_t ret_val = { 0 };

    if(endpoints[ep_num].data_len == 0 || ep_num > 10){
        return ret_val;
    }

    ret_val = *((setup_packet_t *)(endpoints[ep_num].data_buf));

    return ret_val;
}

static void send_usb_data(const uint8_t ep_num, const uint8_t* buf, uint16_t len) {
    uint8_t *destination = endpoints[ep_num].fifo_addr;
    uint8_t packet_size = endpoints[ep_num].max_packet_size;
    uint16_t count = 0;

    if(len == 0){
        USBHS->USBHS_DEVEPTICR[ep_num].bit.TXINIC = 1;
        USBHS->USBHS_DEVEPTIDR[ep_num].bit.FIFOCONC = 1;
        while(!USBHS->USBHS_DEVEPTISR[ep_num].bit.TXINI || (!USBHS->USBHS_DEVEPTIMR[ep_num].bit.FIFOCON && ep_num));
        return;
    }

    while(count < len){
        for (uint16_t i = 0; i < packet_size && count < len; i++) {
            *(destination + count) = *(buf + count);
            count++;
        }
        USBHS->USBHS_DEVEPTICR[ep_num].bit.TXINIC = 1;
        USBHS->USBHS_DEVEPTIDR[ep_num].bit.FIFOCONC = 1;
        while(!USBHS->USBHS_DEVEPTISR[ep_num].bit.TXINI || (!USBHS->USBHS_DEVEPTIMR[ep_num].bit.FIFOCON && ep_num));
    }

}

static void get_descriptor(setup_packet_t* setup) {
    switch (setup->value.byte.H) {
    case USB_DEVICE_DESC_TYPE:
        send_usb_data(0, dev_desc,
            setup->length.val_16 > dev_desc_size ?
            dev_desc_size : setup->length.val_16);
        break;

    case USB_CFG_DESC_TYPE:
        send_usb_data(0, config_desc,
            setup->length.val_16 > config_desc_size ?
            config_desc_size : setup->length.val_16);
        break;

    case USB_STR_DESC_TYPE:
        switch (setup->value.byte.L) {
        case 0x00:
            send_usb_data(0, sd_lang_ID,
                setup->length.val_16 > lang_ID_desc_size ?
                lang_ID_desc_size : setup->length.val_16);
            break;
        case 0x01:
            send_usb_data(0, sd_vendor,
                setup->length.val_16 > vendor_desc_size ?
                vendor_desc_size : setup->length.val_16);
            break;
        case 0x02:
            send_usb_data(0, sd_product,
                setup->length.val_16 > product_desc_size ?
                product_desc_size : setup->length.val_16);
            break;
        default:
            send_usb_data(0, 0, 0);
        }
        break;
    default:
        send_usb_data(0, 0, 0);
        break;
    }
}

static void get_usb_data(uint8_t ep_num) {
    uint16_t byte_count = USBHS->USBHS_DEVEPTISR[ep_num].bit.BYCT;
    uint8_t *destination = endpoints[ep_num].data_buf;
    uint8_t *source = endpoints[ep_num].fifo_addr;

    for (uint16_t i = 0; i < byte_count; i++) {
        *(destination + i) = *(source + i);
    }

    endpoints[ep_num].data_len = byte_count & 0x0A;
}

static void handle_ep_req(setup_packet_t *packet){
    switch (packet->request)
    {
    case USB_REQUEST_GET_STATUS:
        send_usb_data(0, 0, 0);
        break;
    case USB_REQUEST_CLEAR_FEATURE:
        send_usb_data(0, 0, 0);
        break;
    case USB_REQUEST_SET_FEATURE:
        send_usb_data(0, 0, 0);
        break;
    case USB_REQUEST_SYNC_FRAME:
        break;
    default:
        break;
    }
}

static void handle_interface_req(setup_packet_t *packet){
    switch (packet->request)
    {
    case USB_REQUEST_GET_STATUS:
        send_usb_data(0, 0, 0);
        break;
    case USB_REQUEST_CLEAR_FEATURE:
        send_usb_data(0, 0, 0);
        break;
    case USB_REQUEST_SET_FEATURE:
        send_usb_data(0, 0, 0);
        break;
    case USB_REQUEST_GET_INTERFACE:
        send_usb_data(0, 0, 0);
        break;
    case USB_REQUEST_SET_INTERFACE:
        send_usb_data(0, 0, 0);
    default:
        break;
    }
}

static void handle_device_req(setup_packet_t *packet){
    switch (packet->request)
    {
    case USB_REQUEST_GET_STATUS:
        break;
    case USB_REQUEST_CLEAR_FEATURE:
        send_usb_data(0, 0, 0);
        break;
    case USB_REQUEST_SET_FEATURE:
        break;
    case USB_REQUEST_SET_ADDRESS:
        USBHS->USBHS_DEVCTRL.bit.UADD = packet->value.val_16;
        USBHS->USBHS_DEVCTRL.bit.ADDEN = 0;
        send_usb_data(0, 0, 0);
        USBHS->USBHS_DEVCTRL.bit.ADDEN = 1;
        break;
    case USB_REQUEST_GET_DESCRIPTOR:
        get_descriptor(packet);
        break;
    case USB_REQUEST_SET_DESCRIPTOR:
        break;
    case USB_REQUEST_GET_CONFIGURATION:
		send_usb_data(0, &dev_configured, 1);
        break;
    case USB_REQUEST_SET_CONFIGURATION:
        dev_configured = 1;
        send_usb_data(0, 0, 0);
        break;
    default:
        break;
    }
}

static void handle_status_packet(setup_packet_t *setup){

    if(setup->request_type & USB_EP_REQ_MASK){
        handle_ep_req(setup);
    }
    else if(setup->request_type & USB_INTERFACE_REQ_MASK){
        handle_interface_req(setup);
    }
    else{
        handle_device_req(setup);
    }
}

static void handle_control_data(void){
    USBHS->USBHS_DEVEPTICR[0].bit.RXOUTIC = 1;
    return;
}

static void handle_control_ep(void) {
    get_usb_data(0);
    setup_packet_t setup = parse_setup_packet(0);
    USBHS->USBHS_DEVEPTICR[0].bit.RXSTPIC = 1;
    USBHS->USBHS_DEVEPTICR[0].bit.RXOUTIC = 1;

    if(setup.request_type & USB_REQ_TYPE_CLASS){
        handle_aud_ctr_ep();
    }
    else if(setup.request_type & USB_REQ_TYPE_VENDOR){
        handle_aud_ctr_ep();
    }
    handle_status_packet(&setup);
}

static uint8_t init_endpoints(void) {
    USBHS->USBHS_DEVEPT.bit.EPEN1 = 1;
    USBHS->USBHS_DEVEPTCFG[1].reg |= USBHS_DEVEPTCFG_EPTYPE_INTRPT |
        USBHS_DEVEPTCFG_EPSIZE_8_BYTE |
        USBHS_DEVEPTCFG_EPDIR_IN |
        USBHS_DEVEPTCFG_EPBK_1_BANK;

    USBHS->USBHS_DEVEPTCFG[1].reg |= USBHS_DEVEPTCFG_ALLOC;
    if (!USBHS->USBHS_DEVEPTISR[1].bit.CFGOK) {
        return 1;
    }

    USBHS->USBHS_DEVEPT.bit.EPEN2 = 1;
    USBHS->USBHS_DEVEPTCFG[2].reg |= USBHS_DEVEPTCFG_EPTYPE_ISO |
        USBHS_DEVEPTCFG_EPSIZE_256_BYTE |
        USBHS_DEVEPTCFG_EPDIR_OUT |
        USBHS_DEVEPTCFG_EPBK_3_BANK;

    USBHS->USBHS_DEVEPTCFG[2].reg |= USBHS_DEVEPTCFG_ALLOC;
    if (!USBHS->USBHS_DEVEPTISR[2].bit.CFGOK) {
        return 1;
    }

    USBHS->USBHS_DEVEPT.bit.EPEN3 = 1;
    USBHS->USBHS_DEVEPTCFG[3].reg |= USBHS_DEVEPTCFG_EPTYPE_ISO |
        USBHS_DEVEPTCFG_EPSIZE_8_BYTE |
        USBHS_DEVEPTCFG_EPDIR_IN |
        USBHS_DEVEPTCFG_EPBK_1_BANK;

    USBHS->USBHS_DEVEPTCFG[3].reg |= USBHS_DEVEPTCFG_ALLOC;
    if (!USBHS->USBHS_DEVEPTISR[3].bit.CFGOK) {
        return 1;
    }
}

static void usb_wakeup_handler(void){
    USBHS->USBHS_DEVEPTIER[0].reg |= USBHS_DEVEPTIER_RXSTPES | USBHS_DEVEPTIER_RXOUTES;
    USBHS->USBHS_DEVIER.bit.PEP_0 = 1;

    USBHS->USBHS_DEVEPTIER[1].reg |= USBHS_DEVEPTIER_RXSTPES | USBHS_DEVEPTIER_RXOUTES;
    USBHS->USBHS_DEVIER.bit.PEP_1 = 1;

    USBHS->USBHS_DEVEPTIER[2].reg |= USBHS_DEVEPTIER_RXSTPES | USBHS_DEVEPTIER_RXOUTES;
    USBHS->USBHS_DEVIER.bit.PEP_2 = 1;

    USBHS->USBHS_DEVEPTIER[3].reg |= USBHS_DEVEPTIER_RXSTPES | USBHS_DEVEPTIER_RXOUTES;
    USBHS->USBHS_DEVIER.bit.PEP_3 = 1;

    init_endpoints();

    USBHS->USBHS_DEVICR.reg |= USBHS_DEVICR_WAKEUPC | USBHS_DEVICR_EORSTC;
}

void usb_init(void) {
    USBHS->USBHS_CTRL.reg = USBHS_CTRL_UIMOD_DEVICE | USBHS_CTRL_USBE;
    USBHS->USBHS_DEVICR.bit.SUSPC = 1;
    PMC->CKGR_UCKR.bit.UPLLEN = 1;

    PMC->PMC_USB.bit.USBS = 1;

    // Enable USB Clock
    PMC->PMC_PCER1.bit.PID34 = 1;

    PMC->PMC_SCER.bit.USBCLK = 1;

    while (!PMC->PMC_SR.bit.LOCKU);

    USBHS->USBHS_CTRL.reg = USBHS_CTRL_UIMOD_DEVICE | USBHS_CTRL_USBE;

    while(!USBHS->USBHS_SR.bit.CLKUSABLE);

    USBHS->USBHS_DEVEPT.bit.EPEN0 = 1;
    USBHS->USBHS_DEVEPTCFG[0].bit.EPSIZE = USBHS_DEVEPTCFG_EPSIZE_64_BYTE_Val;
    USBHS->USBHS_DEVEPTCFG[0].bit.ALLOC = 1;
    if (!USBHS->USBHS_DEVEPTISR[0].bit.CFGOK) {
        return 1;
    }

    init_endpoints();

    USBHS->USBHS_DEVIER.bit.WAKEUPES = 1;
    USBHS->USBHS_DEVCTRL.bit.DETACH = 0;

    NVIC_EnableIRQ(USBHS_IRQn);
    NVIC_SetPriority(USBHS_IRQn, 1);
}

void irq_handler_usbhs(void) {
    uint32_t isr_reg = USBHS->USBHS_DEVISR.reg;
    if(isr_reg & USBHS_DEVISR_WAKEUP){
        usb_wakeup_handler();
    }
    if (isr_reg & USBHS_DEVISR_PEP_0) {
        handle_control_ep();
    }
    if (isr_reg & USBHS_DEVISR_PEP_1){
        handle_aud_ctr_ep();
    }
    if (isr_reg & USBHS_DEVISR_PEP_2){
        handle_aud_ctr_ep();
    }
}
