import matplotlib.pyplot as plt
import numpy as np
import serial
from time import sleep

Fs = 128.0;  # sampling rate
Ts = 1280.0/Fs; # sampling interval
t = np.arange(0,1280,Ts) # time vector; create Fs samples between 0 and 1.0 sec.
x = np.arange(0,1280,Ts) # signal vector; create Fs samples
y = np.arange(0,1280,Ts)
z = np.arange(0,1280,Ts)

serdev = 'COM3'
s = serial.Serial(serdev)

print("Enter 'a' to start:")
if ('a' == input("> ")):
    print("start")
    s.write(b'1')
    sleep(0.001)
    for i in range(0, int(Fs)):
        line = s.readline()
        line = line.strip(b'\r\n')
        line = line.decode("utf-8")
        data = line.split('/')
        x[i] = float(data[0])
        y[i] = float(data[1])
        z[i] = float(data[2])
    fig, ax = plt.subplots(3, 1)
    ax[0].plot(t,x)
    ax[0].set_xlabel('Time(ms)')
    ax[1].plot(t,y)
    ax[1].set_xlabel('Time(ms)')
    ax[2].plot(t,z)
    ax[2].set_xlabel('Time(ms)')
    plt.show()
s.close()
