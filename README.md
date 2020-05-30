# SimpleMatrixClock
Simple Arduino and MAX7219 matrices based simple clock. This implementation doesn't have fancy bells and whistles like 12/24h support, alarm, animations etc.
Requirements were rather simple: don't reset when there is no power, be visible from relatively long distance (thus bulky font) and adjust brightness according to environment lighting.

Electronically it's basically just a set of modules connected together:
![Schematic](https://raw.githubusercontent.com/eugenijusm/SimpleMatrixClock/master/Construction/Schematic.png)
PSU should be around 5V 2A. 1A is a bit to weak to drive 4 matrices at high brightness.
Some of the pins can be rebinded in config.h
