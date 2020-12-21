import serial
import math
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import

import matplotlib.pyplot as plt
import numpy as np
""" Arduinodan COM3'e şu şekilde veri gönderiyorum
      Serial.print(i);
      Serial.print(" ");
      Serial.print(j);
      Serial.print(" ");
      Serial.println(uzaklik);

  readline decode split işlemlerinden sonra
  [step_adım,servo_açı,uzaklık] olarak 3 elemanlı dizi
  elde ediyorum.
"""
def kordinat(x,y,z):
    
    step_derece  = int(x*5)
    servo_derece = int(y)
    uzaklik      = int(z)

    Ay = uzaklik * math.cos(servo_derece)
    Ax = uzaklik * math.sin(servo_derece) * math.sin(step_derece)
    Az = uzaklik * math.sin(servo_derece) * math.cos(step_derece)
    return Ax,Ay,Az



fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ser = serial.Serial('COM3')

i = 0
while i<=1296:
        arduinoData = ser.readline()
        arduinoData = arduinoData.decode('utf-8')
        arduinoData = arduinoData.split()
        Ax,Ay,Az    = kordinat(arduinoData[0],arduinoData[1],arduinoData[2])
        ax.scatter(Ax,Ay,Az)
        print(Ax,Ay,Az)
        i+=1
plt.show()
