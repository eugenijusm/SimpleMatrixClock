# SimpleMatrixClock
Simple Arduino and MAX7219 matrices based simple clock. This implementation doesn't have fancy bells and whistles like 12/24h support, alarm, animations etc.
Requirements were rather simple: don't reset when there is no power, be visible from relatively long distance (thus bulky font) and adjust brightness according to environment lighting.

Schematic will come later when/if I'll find time to learn how to work with KiCad or EasyEDA.
Basically it's just a set of modules connected together:
* Arduino Mini Pro
* RTC I2C module (e.g. DS3231) SDA to A4; SCL to A5
* Four MAX7219 matrices; Data to D4; CLK to D6; CS to D6
* LDR from Vcc to A0 and pull-down 10K resistor
* two single touch buttons
* PSU 5V 2A. 1A is a bit to weak to drive 4 matrices at high brightness
Some of the pins can be rebinded in config.h
