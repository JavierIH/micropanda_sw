#ifndef LED_H
#define LED_H

#include "stm32f1xx_hal.h"

#define LED_GREEN               GPIO_PIN_12
#define BUTTON_START            GPIO_PIN_12

#define LED_IR_TFL               GPIO_PIN_15
#define LED_IR_TFR               GPIO_PIN_14
#define LED_IR_TSL               GPIO_PIN_13
#define LED_IR_TSR               GPIO_PIN_8

#define LED_GREEN_PORT          GPIOB
#define BUTTON_START_PORT       GPIOA

#define LED_ON                  GPIO_PIN_SET
#define LED_OFF                 GPIO_PIN_RESET

void GPIO_Init();
void set_led(uint16_t led_pin, GPIO_PinState state);
GPIO_PinState get_button(uint16_t button_pin);


#endif // LED_H
