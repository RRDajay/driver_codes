#include "gpio.h"

uint8_t pinPos[16] = {
    // For CRL
    (0x00),
    (0x04),
    (0x08),
    (0x0C),
    (0x10),
    (0x14),
    (0x18),
    (0x1C),
    // For CRH
    (0x00),
    (0x04),
    (0x08),
    (0x0C),
    (0x10),
    (0x14),
    (0x18),
    (0x1C),
};

// for i=0 i<16 i++
// (0x00 + 0x04*(i)) % 0x20

void gpio_clock_enable_af(void)
{
    (RCC->APB2ENR |= 1 << RCC_APB2ENR_AFIOEN_Pos);
}
void gpio_clock_enable_porta(void)
{
    (RCC->APB2ENR |= 1 << RCC_APB2ENR_IOPAEN_Pos);
}
void gpio_clock_enable_portb(void)
{
    (RCC->APB2ENR |= 1 << RCC_APB2ENR_IOPBEN_Pos);
}
void gpio_clock_enable_portc(void)
{
    (RCC->APB2ENR |= 1 << RCC_APB2ENR_IOPCEN_Pos);
}
void gpio_clock_enable_portd(void)
{
    (RCC->APB2ENR |= 1 << RCC_APB2ENR_IOPDEN_Pos);
}
void gpio_clock_enable_porte(void)
{
    (RCC->APB2ENR |= 1 << RCC_APB2ENR_IOPEEN_Pos);
}

void gpio_config_output_pin(GPIO_TypeDef* port,
    uint8_t pinNumber,
    OUTPUT_MODE_TYPES outputModeTypes,
    PIN_SPEED pinSpeed)
{
    if (pinNumber >= 8) {
        switch (outputModeTypes) {
        case OUTPUT_PP:
            port->CRH &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRH |= ((OUTPUT_PP << (pinPos[pinNumber] + 2)) | (pinSpeed << pinPos[pinNumber]));
            break;

        case OUTPUT_OD:
            port->CRH &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRH |= ((OUTPUT_OD << (pinPos[pinNumber] + 2)) | (pinSpeed << pinPos[pinNumber]));
            break;

        case OUTPUT_AF_PP:
            port->CRH &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRH |= ((OUTPUT_AF_PP << (pinPos[pinNumber] + 2)) | (pinSpeed << pinPos[pinNumber]));
            break;

        case OUTPUT_AF_OD:
            port->CRH &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRH |= ((OUTPUT_AF_OD << (pinPos[pinNumber] + 2)) | (pinSpeed << pinPos[pinNumber]));
            break;

        default:
            break;
        }
    }

    else {
        switch (outputModeTypes) {
        case OUTPUT_PP:
            port->CRL &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRL |= ((OUTPUT_PP << (pinPos[pinNumber] + 2)) | (pinSpeed << pinPos[pinNumber]));
            break;

        case OUTPUT_OD:
            port->CRL &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRL |= ((OUTPUT_OD << (pinPos[pinNumber] + 2)) | (pinSpeed << pinPos[pinNumber]));
            break;

        case OUTPUT_AF_PP:
            port->CRL &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRL |= ((OUTPUT_AF_PP << (pinPos[pinNumber] + 2)) | (pinSpeed << pinPos[pinNumber]));
            break;

        case OUTPUT_AF_OD:
            port->CRL &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRL |= ((OUTPUT_AF_OD << (pinPos[pinNumber] + 2)) | (pinSpeed << pinPos[pinNumber]));
            break;

        default:
            break;
        }
    }
}

void gpio_config_input_pin(GPIO_TypeDef* port,
    uint8_t pinNumber,
    INPUT_MODE_TYPES inputModeTypes)
{
    if (pinNumber >= 8) {
        switch (inputModeTypes) {
        case ANALOG_MODE:
            port->CRH &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRH |= ((ANALOG_MODE << (pinPos[pinNumber] + 2)) | (0 << pinPos[pinNumber]));
            break;

        case FLOATING_INPUT:
            port->CRH &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRH |= ((FLOATING_INPUT << (pinPos[pinNumber] + 2)) | (0 << pinPos[pinNumber]));
            break;

        case INPUT_PU_PD:
            port->CRH &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRH |= ((INPUT_PU_PD << (pinPos[pinNumber] + 2)) | (0 << pinPos[pinNumber]));
            break;

        default:
            break;
        }
    }

    else {
        switch (inputModeTypes) {
        case ANALOG_MODE:
            port->CRL &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRL |= ((ANALOG_MODE << (pinPos[pinNumber] + 2)) | (0 << pinPos[pinNumber]));
            break;

        case FLOATING_INPUT:
            port->CRL &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRL |= ((FLOATING_INPUT << (pinPos[pinNumber] + 2)) | (0 << pinPos[pinNumber]));
            break;

        case INPUT_PU_PD:
            port->CRL &= ~((3 << (pinPos[pinNumber] + 2)) | (3 << pinPos[pinNumber]));
            port->CRL |= ((INPUT_PU_PD << (pinPos[pinNumber] + 2)) | (0 << pinPos[pinNumber]));
            break;

        default:
            break;
        }
    }
}

void gpio_pin_reset(GPIO_TypeDef* port, uint8_t pinNumber)
{
    // Clear BSx Bit
    port->BSRR &= ~(1 << pinNumber);

    // Reset Pin by setting the BRy bit
    port->BSRR |= (1 << (pinNumber + 16));
}

void gpio_pin_set(GPIO_TypeDef* port, uint8_t pinNumber)
{
    // Clear BRy Bit
    port->BSRR &= ~(1 << (pinNumber + 16));

    // Set Pin by setting BSx bit
    port->BSRR |= (1 << pinNumber);
}

void gpio_pin_toggle(GPIO_TypeDef* port, uint8_t pinNumber)
{
    // toggles the output data register
    port->ODR ^= (1 << pinNumber);
}

bool gpio_pin_read(GPIO_TypeDef* port, uint8_t pinNumber)
{
    // put the value of IDR in temp
    uint16_t temp = port->IDR;

    // bitmask the temp to read the specific pin value
    return temp & (0x1 << pinNumber);
}
