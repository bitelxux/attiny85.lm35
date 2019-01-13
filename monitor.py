import serial

port = '/dev/ttyUSB0'
ard = serial.Serial(port, 9600)
while True:
    print ard.readline()[:-1]
