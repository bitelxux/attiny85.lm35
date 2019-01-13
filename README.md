# attiny85.lm35
Basic example of attiny85 reading lm35 temperature.

Using arduino IDE and arduino UNO board as attiny85 programmer,
this example shows how to read value from lm35 temperature sensor.

Initial approach was using pin 2 on attiny85 but whatever I tried,
1023 was always read from the pin. Even with nothing connected to
it. May be the chip I was trying was broken? Once I moved the
sensor to pin 3 every thing worked as expected.
