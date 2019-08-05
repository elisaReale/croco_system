# croco_system
Developing a software with hall sensors and led on an arduino nano, to sense small magnets interaction and make them turn on and off specific leds based on the polarity of the magnets, or the side to which the magnets approaches.

## croco_led_hall_9.ino
Is the "simple" version, where there is a timer that counts 10 seconds after the sensing and automatically shut down the led. This was made to cope with the bad sensor that didn't work (btw, I fixed it).

## croco_led_hall_8.ino
Is the code present on the croco board right now. It counts how many seconds you stay close to the sensors, and if you stay for 10 seconds it shut down the led. If you don't, it restart the counting each time you get away from a sensor and come back. 

## future work
The best thing would be to implementa a code with a counter that keeps track of how much time you stood on each tooth-side, until you reach the ten seconds, but in the remaining time I had I couldn't figure out how to do that.
