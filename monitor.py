#!/usr/bin/python

import serial

ser = serial.Serial('/dev/ttyUSB0', 9600)

while True:
    linea = ser.readline()
    print linea[:-1]
