#import serial
import time
import serial

STRAGIHT = 'A'
STOP = 'B'
RIGHT = 'C'
LEFT = 'D'

serial_port = '/dev/ttyACM0'

def port_init():
    ser = serial.Serial(
    port = serial_port,
    baudrate = 115200,
    )
    
    return ser

def get_serial():
    ser = port_init()
    
    return ser

def data_send(ser, data):
    ser.write(data.encode())