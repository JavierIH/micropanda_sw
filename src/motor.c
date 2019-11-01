#include "motor.h"

void MOTOR_Init(){
    GPIO_InitTypeDef GPIO_InitStruct;

    // GPIO Ports Clock Enable
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Configure GPIO pin : PB6 PB7 PB3
    GPIO_InitStruct.Pin = MOTOR_R_IN1|MOTOR_R_IN2|MOTOR_L_IN1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Configure GPIO pins : PA15
    GPIO_InitStruct.Pin = MOTOR_L_IN2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOB, MOTOR_R_IN1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, MOTOR_R_IN2, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, MOTOR_L_IN1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, MOTOR_L_IN2, GPIO_PIN_RESET);
    _motor_sense_l = FREE;
    _motor_sense_r = FREE;
}

void set_sense(motor_t motor, motor_sense_t sense){
    if (motor == MOTOR_R){
        if(sense == BACKWARD){
            HAL_GPIO_WritePin(GPIOB, MOTOR_R_IN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, MOTOR_R_IN2, GPIO_PIN_SET);
            _motor_sense_r = FORWARD;
        }
        else if (sense == FORWARD){
            HAL_GPIO_WritePin(GPIOB, MOTOR_R_IN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, MOTOR_R_IN2, GPIO_PIN_RESET);
            _motor_sense_r = BACKWARD;
        }
        else if (sense == BRAKE){
            HAL_GPIO_WritePin(GPIOB, MOTOR_R_IN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, MOTOR_R_IN2, GPIO_PIN_SET);
            _motor_sense_r = BRAKE;
        }
        else if (sense == FREE){
            HAL_GPIO_WritePin(GPIOB, MOTOR_R_IN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, MOTOR_R_IN2, GPIO_PIN_RESET);
            _motor_sense_r = FREE;
        }
    }
    else if (motor == MOTOR_L){
        if(sense == FORWARD){
            HAL_GPIO_WritePin(GPIOB, MOTOR_L_IN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, MOTOR_L_IN2, GPIO_PIN_RESET);
            _motor_sense_l = FORWARD;
        }
        else if (sense == BACKWARD){
            HAL_GPIO_WritePin(GPIOB, MOTOR_L_IN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, MOTOR_L_IN2, GPIO_PIN_SET);
            _motor_sense_l = BACKWARD;
        }
        else if (sense == BRAKE){
            HAL_GPIO_WritePin(GPIOB, MOTOR_L_IN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, MOTOR_L_IN2, GPIO_PIN_SET);
            _motor_sense_l = BRAKE;
        }
        else if (sense == FREE){
            HAL_GPIO_WritePin(GPIOB, MOTOR_L_IN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, MOTOR_L_IN2, GPIO_PIN_RESET);
            _motor_sense_l = FREE;
        }
    }
}
