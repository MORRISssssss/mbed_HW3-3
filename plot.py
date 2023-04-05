import matplotlib.pyplot as plt
import numpy as np
import serial
from time import sleep

Fs = 128.0;  # sampling rate
Ts = 1280.0/Fs; # sampling interval
t = np.arange(0,1280,Ts) # time vector; create Fs samples between 0 and 1.0 sec.
y = np.arange(0,1280,Ts) # signal vector; create Fs samples

serdev = 'COM3'
s = serial.Serial(serdev)

s.write(b'1')
for i in range(0, int(Fs)):
    line = s.readline()
    line = line.strip(b'\t\n')
    line = line.decode("utf-8")
    print(line)
