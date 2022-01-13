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
#include "example_ulp_gpio.h"

#define Membrane_LED_Red GPIO_NUM_17
#define Membrane_LED_Green GPIO_NUM_5
#define Membrane_LED_Yellow GPIO_NUM_11
#define Membrane_button GPIO_NUM_18

extern void wait(int);


int main (void)
{
    // interrupt_setup(18); //WIP
    // //Blink an LED every time the ULP co-processor wakes up
    example_ulp_gpio_init(Membrane_LED_Yellow);
    example_ulp_gpio_output_enable(Membrane_LED_Yellow);
    example_ulp_gpio_output_level(Membrane_LED_Yellow, 1);
    wait(150000);
    example_ulp_gpio_output_level(Membrane_LED_Yellow, 0);
    example_ulp_gpio_deinit(Membrane_LED_Yellow);
    // ulp_riscv_wakeup_main_processor();
    return 0;
}
