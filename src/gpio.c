#include "gpio.h"

void LED_Init(){
    GPIO_InitTypeDef GPIO_InitStruct;

    // GPIO Ports Clock Enable
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();


    // Configure GPIO pin : PA8
    GPIO_InitStruct.Pin = LED_IR_TSR;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configure GPIO pin : PB12 PB13 PB14 PB15
    GPIO_InitStruct.Pin = LED_GREEN|LED_IR_TFL|LED_IR_TFR|LED_IR_TSL;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Configure GPIO pins : PC13
    GPIO_InitStruct.Pin = BUTTON_START;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void set_led(uint16_t led_pin, GPIO_PinState state){
    if(led_pin == LED_GREEN) {
        HAL_GPIO_WritePin(GPIOB, led_pin, state);
    }
    else if(led_pin == LED_IR_TFL) {
        HAL_GPIO_WritePin(GPIOB, led_pin, state);
    }
    else if(led_pin == LED_IR_TFR) {
        HAL_GPIO_WritePin(GPIOB, led_pin, state);
    }
    else if(led_pin == LED_IR_TSL) {
        HAL_GPIO_WritePin(GPIOB, led_pin, state);
    }
    else if(led_pin == LED_IR_TSR) {
        HAL_GPIO_WritePin(GPIOA, led_pin, state);
    }
}

GPIO_PinState get_button(uint16_t button_pin){
    if(button_pin == BUTTON_START) {
        return HAL_GPIO_ReadPin(BUTTON_START_PORT, BUTTON_START);
    }
}
