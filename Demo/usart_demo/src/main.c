#include "flash.h"
#include "gpio.h"
#include "rcc.h"
#include "stm32f1xx.h"
#include "systick.h"
#include "usart.h"

void clkInit(void);
void resetCtrl(void);

int main(void)
{
    clkInit();

    // Enable gpio clock
    gpio_clock_enable_portc();
    // Configure PC13 as output
    gpio_config_output_pin(GPIOC, 13, OUTPUT_PP, S50);

    /* Loop forever */
    while (1) {
        gpio_pin_toggle(GPIOC, 13);
        delay_ms(1000);
    }
}

void clkInit(void)
{
    //	**********	RCC Configuration	**********	//

    // Enable Prefetch buffer
    flash_enable_prefetch_buffer();

    // Enable HSE and wait till HSE ready
    rcc_hse_enable();

    // Swich to HSE temporarily
    rcc_set_sysclk(HSE_CLK);

    // Disable HSI
    rcc_hsi_disable();

    // Set PLL multiplication to 9
    rcc_set_pllmul(PLLMUL_9);

    // Set HSE as PLL source
    rcc_set_pllsrc(HSE_CLK);

    // Set APB1, APB2, and AHB Prescalers
    rcc_set_ppre1_prescaler(DIV_2);
    rcc_set_ppre2_prescaler(DIV_1);
    rcc_set_ahb_prescaler(DIV_1);

    // Enable PLL and wait until PLL is ready
    rcc_pll_enable();

    // Set PLL as Clock source and wait till PLL is CLK source
    rcc_set_sysclk(PLL_CLK);

    // Update System Core Clock
    SystemCoreClockUpdate();
    systick_init();
}
