import serial
import time

ser = serial.Serial('/dev/ttyACM0')
for x in range(5):
    ser.write(b'0')
    time.sleep(1)
    ser.write(b'1')
    time.sleep(1)
    ser.write(b'2')
    time.sleep(1)
    ser.write(b'3')
ser.close()
