#include "flash.h"
#include "gpio.h"
#include "rcc.h"
#include "stm32f1xx.h"
#include "usart.h"

#if defined(__RTOS__)
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#else
#include "systick.h"
#endif

void clkInit(void);
void resetCtrl(void);

#ifdef __TASKS_DEMO__
extern void main_tasks();
#endif

#ifdef __QUEUE_DEMO__
extern void main_queue();
#endif

#ifdef __SOFTWARE_TIMER_DEMO__
extern void main_software_timers();
#endif

#ifdef __MUTEX_DEMO__
extern void main_mutex();
#endif

int main()
{

#ifdef __TASKS_DEMO__
    main_tasks();
#endif

#ifdef __QUEUE_DEMO__
    main_queue();
#endif

#ifdef __SOFTWARE_TIMER_DEMO__
    main_software_timers();
#endif

#ifdef __MUTEX_DEMO__
    main_mutex();
#endif

#if !(defined(__RTOS__))

    // Initializes RCC and Flash prebuffer
    clkInit();

    // Initialize GPIOC clock and pin 13 as output
    rcc_iopc_clock_enable();
    gpio_config_output_pin(GPIOC, 13, OUTPUT_OD,
        S50); // Configure PC13 as output

    while (1) {
        // usart_send_string(USART1, "Hello World\n");
#if __SEMIHOSTING__
        printf("Hello World\n");
#endif
        gpio_pin_toggle(GPIOC, 13);
        delay_ms(1000);
    }
#endif
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

#if !(defined(__RTOS__))
    systick_init();
#endif
}

void resetCtrl(void)
{
    if (usart_read(USART1) == 'r') {
        usart_send_string(USART1, "\n\t****MICROCONTROLLER RESET!!****\t\n");
        for (uint32_t i = 0; i < 10000000; i++)
            __NOP();
        NVIC_SystemReset();
    }
}