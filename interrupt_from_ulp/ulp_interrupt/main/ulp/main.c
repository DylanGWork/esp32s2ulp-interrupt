/* ULP-RISC-V example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.

   This code runs on ULP-RISC-V  coprocessor
*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "ulp_riscv/ulp_riscv.h"
#include "ulp_riscv/ulp_riscv_utils.h"
#include "ulp_riscv/ulp_riscv_gpio.h"

volatile int cnt = 0;
#define Membrane_LED_Red GPIO_NUM_5
#define Membrane_LED_Green GPIO_NUM_17
#define Membrane_LED_Yellow GPIO_NUM_11

// uint32_t ulp_end;
extern void wait(int);


int main (void)
{
    ulp_riscv_gpio_init(Membrane_LED_Yellow);
    ulp_riscv_gpio_output_enable(Membrane_LED_Yellow);
    ulp_riscv_gpio_output_level(Membrane_LED_Yellow, 1);
    wait(150000);
    ulp_riscv_gpio_output_level(Membrane_LED_Yellow, 0);
    ulp_riscv_gpio_output_disable(Membrane_LED_Yellow);
    ulp_riscv_gpio_deinit(Membrane_LED_Yellow);
    ulp_riscv_delay_cycles(10000000);
    ulp_riscv_wakeup_main_processor();
    // ulp_end =1;
    ulp_riscv_shutdown();
    /* ulp_riscv_halt() is called automatically when main exits */
    return 0;
}