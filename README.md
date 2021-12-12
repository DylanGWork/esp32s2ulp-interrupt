| Supported Targets | ESP32-S2 |
| ----------------- | -------- |

# DylanGWork

This is the repository of the firmware for the ESP32-S2 interrupt while using the ULP Risc-v Co-processor.

This code blinks an LED every 2 seconds using the Risc-v Co-processor.
A button interrupt is setup in the main processor (waiting for ULP interrupts to be easily available in the esp-idf framework, it's in the technical reference guide but with no implementation instructions).

When the interrupt is active, the LED's no longer blink.

How do we allow for EXT1 to be used while the Risc-v Co-processor is operating?


