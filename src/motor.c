#include "motor.h"
#include "pwm.h"
#include "uart.h"

void MOTOR_Init(){
    GPIO_InitTypeDef GPIO_InitStruct;

    // GPIO Ports Clock Enable
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Configure GPIO pin : PB6 PB7 PB3
    GPIO_InitStruct.Pin = MOTOR_AIN1|MOTOR_AIN2|MOTOR_BIN1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Configure GPIO pins : PA15
    GPIO_InitStruct.Pin = MOTOR_BIN2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOB, MOTOR_AIN1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, MOTOR_AIN2, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, MOTOR_BIN1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, MOTOR_BIN2, GPIO_PIN_RESET);
    _motor_sense_l = FREE;
    _motor_sense_r = FREE;
}

void motor_set_sense(motor_t motor, motor_sense_t sense){
    if (motor == MOTOR_L){
        if(sense == BACKWARD){
            HAL_GPIO_WritePin(GPIOB, MOTOR_AIN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, MOTOR_AIN2, GPIO_PIN_SET);
            _motor_sense_r = BACKWARD;
            send_uart("Motor R ATRAS");


        }
        else if (sense == FORWARD){
            HAL_GPIO_WritePin(GPIOB, MOTOR_AIN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, MOTOR_AIN2, GPIO_PIN_RESET);
            _motor_sense_r = FORWARD;
            send_uart("Motor R ADELANTE");
        }
        else if (sense == BRAKE){
            HAL_GPIO_WritePin(GPIOB, MOTOR_AIN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, MOTOR_AIN2, GPIO_PIN_SET);
            _motor_sense_r = BRAKE;
        }
        else if (sense == FREE){
            HAL_GPIO_WritePin(GPIOB, MOTOR_AIN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, MOTOR_AIN2, GPIO_PIN_RESET);
            _motor_sense_r = FREE;
        }
    }
    else if (motor == MOTOR_R){
        if(sense == FORWARD){
            HAL_GPIO_WritePin(GPIOB, MOTOR_BIN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, MOTOR_BIN2, GPIO_PIN_SET);
            _motor_sense_l = FORWARD;
            send_uart("Motor L ADELANTE");

        }
        else if (sense == BACKWARD){
            HAL_GPIO_WritePin(GPIOB, MOTOR_BIN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, MOTOR_BIN2, GPIO_PIN_RESET);
            _motor_sense_l = BACKWARD;
            send_uart("Motor L ATRAS");

        }
        else if (sense == BRAKE){
            HAL_GPIO_WritePin(GPIOB, MOTOR_BIN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, MOTOR_BIN2, GPIO_PIN_SET);
            _motor_sense_l = BRAKE;
        }
        else if (sense == FREE){
            HAL_GPIO_WritePin(GPIOB, MOTOR_BIN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, MOTOR_BIN2, GPIO_PIN_RESET);
            _motor_sense_l = FREE;
        }
    }
}

void motor_set_speed(motor_t motor, int16_t speed){
    if(speed > 0){
        motor_set_sense(motor, FORWARD);
        send_uart("set speed fwd\n\r");
    }
    else{
        speed *= -1;
        motor_set_sense(motor, BACKWARD);
        send_uart("set speed bwd\n\r");

    }
    if(speed > 1000) speed = 1000;
    if(motor == MOTOR_L) set_pwm(PWM_2, speed);
    if(motor == MOTOR_R) set_pwm(PWM_1, speed);
}
