import numpy as np
from io import BytesIO
import matplotlib.pyplot as plt
fname = "still.txt"
data = np.genfromtxt(fname, delimiter=" ", dtype=[('count', int), ('magX', float), ('magY', float), ('magZ', float), ('accX', float), ('accY', float), ('accZ', float), ('gyroX', float), ('gyroY', float), ('gyroZ', float)], skip_header=1)

count = data['count']
magX = data['magX']
magY = data['magY']
magZ = data['magZ']
accX = data['accX']
accY = data['accY']
accZ = data['accZ']
gyroX = data['gyroX']
gyroY = data['gyroY']
gyroZ = data['gyroZ']

plt.figure(1)
plt.subplot(3,2,1)
plt.plot(count, accX)
plt.title('Accelerometer')
plt.ylabel('accX')

plt.subplot(3,2,2)
plt.plot(count, accY)
plt.ylabel('accY')

plt.subplot(3,2,3)
plt.plot(count, accZ)
plt.ylabel('accZ')
plt.xlabel('Data point')

plt.figure(2)
plt.subplot(3,2,1)
plt.plot(count, gyroX)
plt.title('Gyroscope')
plt.ylabel('gyroX')

plt.subplot(3,2,2)
plt.plot(count, gyroY)
plt.ylabel('gyroY')

plt.subplot(3,2,3)
plt.plot(count, gyroZ)
plt.ylabel('gyroZ')
plt.xlabel('Data point')


plt.figure(3)
plt.subplot(3,2,1)
plt.plot(count, magX)
plt.title('Magnetometer')
plt.ylabel('magX')

plt.subplot(3,2,2)
plt.plot(count, magY)
plt.ylabel('magY')

plt.subplot(3,2,3)
plt.plot(count, magZ)
plt.ylabel('magZ')
plt.xlabel('Data point')
plt.show()
