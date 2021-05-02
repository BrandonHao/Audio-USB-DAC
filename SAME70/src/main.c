/**
 *
 */

//-----------------------------------------------------------------------------
#include <same70.h>
#include "hal_gpio.h"
#include "usb_core.h"

//-----------------------------------------------------------------------------
static void sys_init(void) {
    // Disable watchdog
    WDT->WDT_MR.reg = WDT_MR_WDDIS;

    // Set flash wait states to maximum for 150 MHz operation
    EFC->EEFC_FMR.reg = EEFC_FMR_FWS(5) | EEFC_FMR_CLOE;

    // Enable 12 MHz Xtal
    PMC->CKGR_MOR.reg = CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTST(8) |
                    CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN;
    while (!(PMC->PMC_SR.reg & PMC_SR_MOSCXTS));

    PMC->CKGR_MOR.reg = CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTST(8) |
                    CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCSEL;
    while (!(PMC->PMC_SR.reg & PMC_SR_MOSCSELS));

    // Setup PLL (12 MHz * 25 = 300 MHz)
    PMC->CKGR_PLLAR.reg = CKGR_PLLAR_ONE | CKGR_PLLAR_MULA(25-1) |
                      CKGR_PLLAR_PLLACOUNT(0x3f) | CKGR_PLLAR_DIVA(1);
    while (!(PMC->PMC_SR.reg & PMC_SR_LOCKA));

    // Switch main clock to PLL (two step process)
    PMC->PMC_MCKR.reg = PMC_MCKR_CSS_MAIN_CLK | PMC_MCKR_MDIV_PCK_DIV2;
    while (!(PMC->PMC_SR.reg & PMC_SR_MCKRDY));

    PMC->PMC_MCKR.reg = PMC_MCKR_CSS_PLLA_CLK | PMC_MCKR_MDIV_PCK_DIV2;
    while (!(PMC->PMC_SR.reg & PMC_SR_MCKRDY));

    // Enable PIOA, PIOB, PIOC, PIOD and PIOE
    PMC->PMC_PCER0.reg = PMC_PCER0_PID10 | PMC_PCER0_PID11 | PMC_PCER0_PID12 |
                     PMC_PCER0_PID16 | PMC_PCER0_PID17;

    // Disable altenate functions on some pins
    MATRIX->CCFG_SYSIO.reg |= CCFG_SYSIO_SYSIO4;
}

static void NVIC_Initialize( void )
{
    /* Priority 0 to 7 and no sub-priority. 0 is the highest priority */
    NVIC_SetPriorityGrouping( 0x04 );

    /* Enable NVIC Controller */
    __DMB();
    __enable_irq();
}

//-----------------------------------------------------------------------------
int main(void) {
    sys_init();
    NVIC_Initialize();
    usb_init();
    while (1) {
    }

    return 0;
}

