#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f1xx_hal.h"
#include "pwm.h"

typedef enum {MOTOR_R, MOTOR_L} motor_t;
typedef enum {FORWARD, BACKWARD, BRAKE, FREE} motor_sense_t;

#define MOTOR_BIN1              GPIO_PIN_3
#define MOTOR_BIN2              GPIO_PIN_15
#define MOTOR_AIN1              GPIO_PIN_6
#define MOTOR_AIN2              GPIO_PIN_7

#define MOTOR_BIN1_PORT         GPIOB
#define MOTOR_BIN2_PORT         GPIOA
#define MOTOR_AIN1_PORT         GPIOB
#define MOTOR_AIN2_PORT         GPIOB

int32_t _motor_speed_l;
int32_t _motor_speed_r;
motor_sense_t _motor_sense_l;
motor_sense_t _motor_sense_r;

void MOTOR_Init();
void motor_set_sense(motor_t motor, motor_sense_t sense);
void motor_set_speed(motor_t motor, int16_t speed);
//void update_speed(motor_t motor);
//int32_t get_speed(motor_t motor);



#endif // MOTOR_H
