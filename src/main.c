#include "stm32f1xx_hal.h"
#include "msp.h"
#include "sysclock.h"
#include "error.h"
#include "uart.h"
#include "pwm.h"
#include "gpio.h"
#include "motor.h"
#include "infrared.h"

char text_buffer[200];

static void MX_ADC1_Init(void);
void setup(void);
void update_pid(void);
void delay(uint16_t time);

int main(void) {
    setup();

    //set_sense(MOTOR_R, FREE);
    //set_sense(MOTOR_L, FREE);
    set_led(LED_GREEN, LED_ON);


    //while (!get_button(BUTTON_START));
    //set_led(LED_GREEN, LED_OFF);
    //delay(1000);

    set_sense(MOTOR_R, BACKWARD);
    set_sense(MOTOR_L, BACKWARD);

    //set_led(LED_GREEN, LED_ON);
    set_led(LED_IR_TFL, LED_ON);
    set_led(LED_IR_TFR, LED_ON);
    set_led(LED_IR_TSL, LED_ON);
    set_led(LED_IR_TSR, LED_ON);


    while(!get_button(BUTTON_START));
    set_led(LED_GREEN, LED_OFF);
    set_pwm(PWM_2, 999);
    set_pwm(PWM_1, 999);
    while(1){
        set_sense(MOTOR_R, BACKWARD);
        set_sense(MOTOR_L, FORWARD);
        delay(150);
        set_sense(MOTOR_R, FREE);
        set_sense(MOTOR_L, FREE);
        delay(500);
        set_sense(MOTOR_R, FORWARD);
        set_sense(MOTOR_L, BACKWARD);
        delay(150);
        set_sense(MOTOR_R, FREE);
        set_sense(MOTOR_L, FREE);
        delay(500);

    }
    /*while (1){
        uint32_t value_ref = 0;
        uint32_t value = 0;
        set_led(LED_IR_TSR, LED_ON);
        value = get_ir(SENSOR_IR_TSR);
        delay(5);

        set_led(LED_IR_TSR, LED_OFF);
        value -= get_ir(SENSOR_IR_TSR);
        delay(5);

        //value = get_ir(SENSOR_IR_TSR) - value;


        if(value>1100){
            set_led(LED_GREEN, LED_OFF);
        }
        else{
            set_led(LED_GREEN, LED_ON);
        }
        //set_led(LED_GREEN, LED_OFF);
        //set_led(LED_IR_TFR, LED_OFF);
        //set_led(LED_IR_TFL, LED_OFF);
        //set_led(LED_IR_TSR, LED_OFF);
        //set_led(LED_IR_TSL, LED_OFF);
        //delay(1000);
        //set_led(LED_GREEN, LED_ON);
        //set_led(LED_IR_TFR, LED_ON);
        //set_led(LED_IR_TFL, LED_ON);
        //set_led(LED_IR_TSR, LED_ON);
        //set_led(LED_IR_TSL, LED_ON);

        sprintf(text_buffer,"IR: %d\t\n\r", value-value_ref); send_uart(text_buffer);

        delay(100);
    }*/
}

void delay(uint16_t time){
    HAL_Delay(time*20);
}

void setup(void){
    HAL_Init();
    SystemClock_Config();

    // Peripheral setup
    LED_Init();
    UART_Init();
    PWM_Init();
    MOTOR_Init();
    IR_Init();
}

void SysTick_Handler(void){ // function executed each 10us
    static uint16_t task_tick = 0;

    switch (task_tick++) { // each case is executed each 10us
        case 0:
            //update_pid();
            task_tick=0;
            break;
        case 1:
            break;
    }
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}
