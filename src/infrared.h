#ifndef INFRARED_H
#define INFRARED_H

#include "stm32f1xx_hal.h"

#define SENSOR_IR_TFL       3
#define SENSOR_IR_TFR       7
#define SENSOR_IR_TSL       4
#define SENSOR_IR_TSR       8
#define SENSOR_IR_BFL       1
#define SENSOR_IR_BFR       2
#define SENSOR_IR_BBL       6
#define SENSOR_IR_BBR       5

uint32_t _adc_buf[8];

DMA_HandleTypeDef hdma_adc1;
ADC_HandleTypeDef hadc1;
ADC_ChannelConfTypeDef _sConfig;

void IR_Init();
uint32_t get_ir(uint8_t ir);


#endif // INFRARED_H
