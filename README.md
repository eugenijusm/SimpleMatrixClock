# SimpleMatrixClock
Simple Arduino and MAX7219 matrices based clock. It doesn't have fancy features like 12/24h support, alarm, animations etc. But these are rather useless in daily use; just showing hours and minutes is way more practical :)
Requirements were rather simple:
* don't reset when there is no power
* be visible from relatively long distance (thus bulky font)
* adjust brightness according to environment lighting.
There is a simple menu to set the time after RTC battery is replaced.

Electronically it's just a set of modules connected together:
![Schematic](https://raw.githubusercontent.com/eugenijusm/SimpleMatrixClock/master/Construction/Schematic.png)

PSU should be around 5V 2A. 1A is a bit to weak to drive 4 matrices at high brightness.
Some of the pins can be rebinded in config.h

Physically it looks like this:
![Looks](https://raw.githubusercontent.com/eugenijusm/SimpleMatrixClock/master/Construction/Looks.jpg)
10x15 photo frame is used. Front glass is tinted with 50% car glass film to make matrix display more distinctive. Even darker film might work even better; but then LDR probably should be located somewhere else.
