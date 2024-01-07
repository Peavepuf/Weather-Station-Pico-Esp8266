"""MIT License

Copyright (c) 2024 Peavepuf

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. """


#LIBRARIES
from machine import Pin, I2C
import time
from bmp085 import BMP180
import dht
#LIBRARIES
#--------------------------------------------
#SERIAL COMMUNICATION DEFINITION
uart = machine.UART(0, baudrate=9600, tx=machine.Pin(0))
#SERIAL DEFINITION
#--------------------------------------------
#PIN DEFINITION
dSensor = dht.DHT11(Pin(2))# DHT PIN GPIO2
led = Pin(25, Pin.OUT)
i2c1 = I2C(1, scl=Pin(7), sda=Pin(6), freq=40000)
bmp = BMP180(i2c1)#BMP180 DEFINITION
#PIN DEFINITION
#--------------------------------------------
#MAP FUNCTION. SQUEEZES THE VALUE INTO A RANGE
def MAP(x, input_min, input_max, output_min, output_max):
    return (x - input_min) * (output_max - output_min) / (input_max - input_min) + output_min
#MAP FUNCTION
#--------------------------------------------
#BMP180 MEASUREMENTS FOR PRESSURE AND ALTITUDE
def readBMP():
    pressure1 = bmp.pressure
    altitude = int(bmp.altitude)
    pressure = pressure1 / 100
    sc2 = bmp.temperature
    print("Altitude:", int(altitude), "m")
    print("Pressure:", pressure)
    return pressure, altitude
#BMP180 MEASUREMENTS
#--------------------------------------------
#TEMPERATURE AND HUMIDITY MEASUREMENT
def readDHT():
    try:
        dSensor.measure()
        temp = dSensor.temperature()
        hum = dSensor.humidity()
        print('Temperature:{} C'.format(temp))
        print('Humidity:%{} '.format(hum))
        return temp, hum
    except OSError as e:
        print('DHT11 Not Working')
#TEMPERATURE AND HUMIDITY MEASUREMENT
#--------------------------------------------
#MAIN LOOP
while True:
    readBMP()#READ ALTITUDE AND PRESSURE FUNCTION
    readDHT()#READ TEMPERATURE AND HUMIDITY FUNCTION
    data_to_send = [temp, hum, pressure, altitude]#DATA
    uart.write(str(data_to_send) + '\n')#SENDING DATA
    time.sleep(60)#60 SECONDS SLEEP
