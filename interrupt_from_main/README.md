| Supported Targets | ESP32-S2 |
| ----------------- | -------- |

# DylanGWork

This is the repository of the firmware for the ESP32-S2 interrupt while using the ULP Risc-v Co-processor.

This code blinks an LED every 2 seconds using the Risc-v Co-processor.
A button interrupt is setup in the main processor (waiting for ULP interrupts to be easily available in the esp-idf framework, it's in the technical reference guide but with no implementation instructions).

When the interrupt is active, the LED's no longer blink.

How do we allow for EXT1 to be used while the Risc-v Co-processor is operating?

Answer:
The file sleep_modes.c line 143 needs to be changed from the value of 17 to 22.

Change:
typedef struct {
    esp_sleep_pd_option_t pd_options[ESP_PD_DOMAIN_MAX];
    uint64_t sleep_duration;
    uint32_t wakeup_triggers : 15;
    uint32_t ext1_trigger_mode : 1;
    **uint32_t ext1_rtc_gpio_mask : 17;**
    uint32_t ext0_trigger_level : 1;
    uint32_t ext0_rtc_gpio_num : 5;
    uint32_t gpio_wakeup_mask : 6;
    uint32_t gpio_trigger_mode : 6;
    uint32_t sleep_time_adjustment;
    uint32_t ccount_ticks_record;
    uint32_t sleep_time_overhead_out;
    uint32_t rtc_clk_cal_period;
    uint64_t rtc_ticks_at_sleep_start;
} sleep_config_t;

To:
typedef struct {
    esp_sleep_pd_option_t pd_options[ESP_PD_DOMAIN_MAX];
    uint64_t sleep_duration;
    uint32_t wakeup_triggers : 15;
    uint32_t ext1_trigger_mode : 1;
    **uint32_t ext1_rtc_gpio_mask : 22;**
    uint32_t ext0_trigger_level : 1;
    uint32_t ext0_rtc_gpio_num : 5;
    uint32_t gpio_wakeup_mask : 6;
    uint32_t gpio_trigger_mode : 6;
    uint32_t sleep_time_adjustment;
    uint32_t ccount_ticks_record;
    uint32_t sleep_time_overhead_out;
    uint32_t rtc_clk_cal_period;
    uint64_t rtc_ticks_at_sleep_start;
} sleep_config_t;
