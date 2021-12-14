/**
 *
 */

 //-----------------------------------------------------------------------------
#include <same70.h>
#include "hal_gpio.h"
#include "usb_core.h"
#include "debug_uart.h"

#define RESET_FLAG_ADDR     (IRAM_ADDR + IRAM_SIZE - 4U)
#define RESET_MASK          0xB00B1234

static void full_reset(void){
    volatile uint32_t *flag_addr = (uint32_t *)RESET_FLAG_ADDR;
    if(GPBR->SYS_GPBR[0].reg != RESET_MASK){
        GPBR->SYS_GPBR[0].reg = RESET_MASK;
        WDT->WDT_MR.bit.WDV = 1;
    }
    else{
        GPBR->SYS_GPBR[0].reg = 0;
    }
}

//-----------------------------------------------------------------------------
static void sys_init(void) {

    // Disable watchdog
    WDT->WDT_MR.bit.WDDIS = 1;

    // Set flash wait states to maximum for 150 MHz operation
    EFC->EEFC_FMR.reg = EEFC_FMR_FWS(6) | EEFC_FMR_CLOE;

    // Enable 12 MHz Xtal
    PMC->CKGR_MOR.reg |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTST(20) | CKGR_MOR_MOSCXTEN;
    while (!PMC->PMC_SR.bit.MOSCXTS);

    PMC->CKGR_MOR.reg |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCSEL;
    while (!PMC->PMC_SR.bit.MOSCXTS || !PMC->CKGR_MCFR.bit.MAINFRDY);

    // Setup PLL (12 MHz * 25 = 300 MHz)
    PMC->CKGR_PLLAR.reg = CKGR_PLLAR_ONE | CKGR_PLLAR_MULA(25 - 1) |
        CKGR_PLLAR_PLLACOUNT(0x3f) | CKGR_PLLAR_DIVA(1);
    while (!PMC->PMC_SR.bit.LOCKA);

    PMC->PMC_MCKR.reg |= PMC_MCKR_MDIV_PCK_DIV2;
    while (!PMC->PMC_SR.bit.MCKRDY);

    PMC->PMC_MCKR.bit.CSS = PMC_MCKR_CSS_PLLA_CLK_Val;
    while (!PMC->PMC_SR.bit.MCKRDY);

    // Enable PIOA, PIOB, PIOC, PIOD and PIOE
    PMC->PMC_PCER0.reg |= PMC_PCER0_PID10 | PMC_PCER0_PID11 | PMC_PCER0_PID12 |
        PMC_PCER0_PID16 | PMC_PCER0_PID17;

    // Disable altenate functions on some pins
    MATRIX->CCFG_SYSIO.reg |= CCFG_SYSIO_SYSIO4;
}

static void NVIC_Initialize(void)
{
    /* Priority 0 to 7 and no sub-priority. 0 is the highest priority */
    NVIC_SetPriorityGrouping(0x04);

    /* Enable NVIC Controller */
    __DMB();
    __enable_irq();
}

//-----------------------------------------------------------------------------
int main(void) {
    //full_reset();
    NVIC_Initialize();
    sys_init();
    uart_init();
    uint8_t temp[3] = "abc";
    uart_write(temp, 3);
    //usb_init();
    while (1) {
    }

    return 0;
}

