#include "stm32f1xx_hal.h"
#include "msp.h"
#include "sysclock.h"
#include "error.h"
#include "uart.h"
#include "pwm.h"
#include "gpio.h"
#include "motor.h"
#include "infrared.h"

#define DETECTION       1700
#define LINE            1700
#define MAX_ROT_SPEED   50
#define MAX_FWD_SPEED   50

char text_buffer[200];

uint32_t ir_bbl, ir_bbr, ir_bfl, ir_bfr;
uint32_t ir_tsl, ir_tsr, ir_tfl, ir_tfr;
uint32_t ir_tsl_off, ir_tsr_off, ir_tfl_off, ir_tfr_off;


static void MX_ADC1_Init(void);
void setup(void);
void update_pid(void);
void delay(uint16_t time);

int main(void) {
    setup();
    set_led(LED_GREEN, LED_ON);
    while(!get_button(BUTTON_START));
    set_led(LED_GREEN, LED_OFF);
    delay(5000);
    uint8_t last_side; // 0 if enemy was at left, 1 if enemy was at right

    //motor_set_sense(MOTOR_L, BACKWARD);
    //motor_set_sense(MOTOR_R, BACKWARD);

    while (1){
        if(ir_tfl > DETECTION && ir_tfr > DETECTION){ //enemy
            //sprintf(text_buffer,"ADELANTE\n\r", ir_tfr); send_uart(text_buffer);
            motor_set_speed(MOTOR_L, 1000);
            motor_set_speed(MOTOR_R, 1000);

        }
        else if(ir_tfl > DETECTION){ //enemy
            //corregir despacio a izquierda
            //sprintf(text_buffer,"IZQUIERDA  SUAVE\n\r", ir_tfr); send_uart(text_buffer);
            motor_set_speed(MOTOR_R, 300);
            motor_set_speed(MOTOR_L, -300);
            last_side = 0;
        }
        else if(ir_tfr > DETECTION){ //enemy
            //corregir despacio a derecha
            //sprintf(text_buffer,"DERECHA SUAVE\n\r", ir_tfr); send_uart(text_buffer);
            motor_set_speed(MOTOR_R, -300);
            motor_set_speed(MOTOR_L, 300);
            last_side = 1;
        }
        //else if(ir_bfl > LINE && ir_bfr > LINE){ //white line
            //atras
        //}
        //else if(ir_bbl > LINE && ir_bbr > LINE){
            //adelante
        //}
        else if(ir_tsl > DETECTION){
            //girar rapido a izquierda
            //sprintf(text_buffer,"IZQUIERDA RAPIDO\n\r", ir_tfr); send_uart(text_buffer);
            last_side = 0;

        }
        else if(ir_tsr > DETECTION){
            //girar rapido a derecha
            //sprintf(text_buffer,"DERECHA RAPIDO\n\r", ir_tfr); send_uart(text_buffer);
            last_side = 1;

        }
        else{
            //girar to loco
            if(last_side){
                //sprintf(text_buffer,"BUSCA DERECHA\n\r", ir_tfr); send_uart(text_buffer);
            }else{
                //sprintf(text_buffer,"BUSCA IZQUIERDA\n\r", ir_tfr); send_uart(text_buffer);
            }
                motor_set_sense(MOTOR_L, FREE);
                motor_set_sense(MOTOR_R, FREE);
        }

        //sprintf(text_buffer,"IR TFL: %lu\t\n\r", ir_tfl); send_uart(text_buffer);
        //sprintf(text_buffer,"IR TFR: %lu\t\n\r", ir_tfr); send_uart(text_buffer);
        //sprintf(text_buffer,"IR TSL: %lu\t\n\r", ir_tsl); send_uart(text_buffer);
        //sprintf(text_buffer,"IR TSR: %lu\t\n\n\r", ir_tsr); send_uart(text_buffer);
        //delay(200);
    }

}

void delay(uint16_t time){
    HAL_Delay(time*10);
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

void SysTick_Handler(void){ // function executed each 100us
    static uint16_t task_tick = 0;

    switch (task_tick++) { // 100us between tasks
        case 0:
            ir_tsl_off = get_ir(SENSOR_IR_TSL);
            ir_tsr_off = get_ir(SENSOR_IR_TSR);
            ir_tfl_off = get_ir(SENSOR_IR_TFL);
            ir_tfr_off = get_ir(SENSOR_IR_TFR);
            set_led(LED_IR_TFR, LED_ON);
            set_led(LED_IR_TFL, LED_ON);
            set_led(LED_IR_TSR, LED_ON);
            set_led(LED_IR_TSL, LED_ON);
            break;

        case 1:
            ir_bbl = get_ir(SENSOR_IR_BBL);
            ir_bbr = get_ir(SENSOR_IR_BBR);
            ir_bfl = get_ir(SENSOR_IR_BFR);
            ir_bfr = get_ir(SENSOR_IR_BFR);
            break;

        case 10:
            ir_tsl = -get_ir(SENSOR_IR_TSL) + ir_tsl_off;
            ir_tsr = -get_ir(SENSOR_IR_TSR) + ir_tsr_off;
            ir_tfl = -get_ir(SENSOR_IR_TFL) + ir_tfl_off;
            ir_tfr = -get_ir(SENSOR_IR_TFR) + ir_tfr_off;
            set_led(LED_IR_TFR, LED_OFF);
            set_led(LED_IR_TFL, LED_OFF);
            set_led(LED_IR_TSR, LED_OFF);
            set_led(LED_IR_TSL, LED_OFF);
            break;

        case 19:
            task_tick=0;
            break;
        /*case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;*/
    }
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}
