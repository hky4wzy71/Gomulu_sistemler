import serial
import math
import plotly.graph_objects as go
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

Ax=[]
Ay=[]
Az=[]

def kordinat(x,y,z):
    
    step_derece  = int(x)*5
    servo_derece = int(y)
    uzaklik      = float(z)
    
    
    dikey = uzaklik * math.cos(math.radians(servo_derece))
    yatay = uzaklik * math.sin(math.radians(servo_derece)) * math.sin(math.radians(step_derece))
    derinlik = uzaklik * math.sin(math.radians(servo_derece)) * math.cos(math.radians(step_derece))
    
    Ax.append(yatay)
    Ay.append(dikey)
    Az.append(derinlik)


    
    print("step_derece",step_derece,"Hesaplanan kordinat = ",yatay)
    print("servo_derece",servo_derece,"Hesaplanan kordinat = ",dikey)
    print("uzaklik",uzaklik,"Hesaplanan kordinat = ",derinlik),
    print("========================================================")


ser = serial.Serial('COM3')

i = 0
while i<=1296:
        arduinoData = ser.readline()
        arduinoData = arduinoData.decode('utf-8')
        arduinoData = arduinoData.split()
        kordinat(arduinoData[0],arduinoData[1],arduinoData[2])
        i+=1



marker_data = go.Scatter3d(
    x=Ax, 
    y=Ay, 
    z=Az, 
    marker=go.scatter3d.Marker(size=6), 
    opacity=0.8, 
    mode='markers'
)
fig=go.Figure(data=marker_data)
fig.show()














