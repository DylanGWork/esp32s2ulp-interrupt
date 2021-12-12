/* ULP riscv example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include "esp_sleep.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/sens_reg.h"
#include "soc/rtc_periph.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "esp32s2/ulp.h"
#include "esp32s2/ulp_riscv.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_sleep.h"
#include "stdbool.h"

#include "ulp_main.h"

extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t ulp_main_bin_end[]   asm("_binary_ulp_main_bin_end");

static void init_ulp_program(void);
void setup_ulp();

#define Membrane_button GPIO_NUM_18

void app_main(void)
{
     setup_ulp();

    //Setup membrane 
    rtc_gpio_init(Membrane_button);
    rtc_gpio_set_direction(Membrane_button, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_set_direction_in_sleep(Membrane_button, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pulldown_dis(Membrane_button);
    rtc_gpio_pullup_en(Membrane_button);
    rtc_gpio_hold_en(Membrane_button);
    // const int ext_wakeup_pin_1  = 18;
    // const uint64_t ext_wakeup_pin_1_mask  = 1ULL << ext_wakeup_pin_1;
    // esp_sleep_enable_ext1_wakeup(ext_wakeup_pin_1_mask , 1);
    printf("Entering in deep sleep and uploaded by flash\n\n");
    vTaskDelay(25);
    ESP_ERROR_CHECK( esp_sleep_enable_ulp_wakeup()); 
    esp_deep_sleep_start();
}

static void init_ulp_program(void)
{
    esp_err_t err = ulp_riscv_load_binary(ulp_main_bin_start, (ulp_main_bin_end - ulp_main_bin_start));
    ESP_ERROR_CHECK(err);

    /* The first argument is the period index, which is not used by the ULP-RISC-V timer
     * The second argument is the period in microseconds, which gives a wakeup time period of: 20ms
     */

    ulp_set_wakeup_period(0, 2000000);

    /* Start the program */
    err = ulp_riscv_run();
    ESP_ERROR_CHECK(err);
}


void setup_ulp(){
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
    /* not a wakeup from ULP, load the firmware */
    if (cause == ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG) {
        printf("Co-processor Crashed \n");
    }
    if (cause == ESP_SLEEP_WAKEUP_ULP) {
        printf("Woke-up intentionally by ULP  \n");
    }
        if (cause == ESP_SLEEP_WAKEUP_EXT1) {
        printf("Woke-up intentionally by EXT1\n");
        
    }
    init_ulp_program();

}

