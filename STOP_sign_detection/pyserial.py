import numpy as np
from imageio import imread
from skimage import feature
import matplotlib.pyplot as plt
import cv2
import time
import serial
import sys
np.set_printoptions(threshold=sys.maxsize)
  
port = "COM3"
baud = 9600
  
ser = serial.Serial(port, baud, timeout=1)
    # open the serial port
if ser.isOpen():
     print(ser.name + ' is open...')
  
while True:
    cmd = input("Enter command or '`' to exit:")
        # for Python 3
    if cmd == '`':
        ser.close()
        exit()
    else:
        ser.write(cmd.encode('ascii'))
        # out=''
        # while ser.in_waiting:
        #     out+=ser.read().decode("utf-8") # read a byte and decode to str
        out=ser.readline().decode("utf-8")
        print('Receiving...'+out)