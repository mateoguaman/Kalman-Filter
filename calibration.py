import numpy as np
from io import BytesIO
import matplotlib.pyplot as plt

#Data parser
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

#Calibration
if count.size > 250:
    magXmean = np.mean(magX[100:200])
    magYmean = np.mean(magY[100:200])
    magZmean = np.mean(magZ[100:200])
    accXmean = np.mean(accX[100:200])
    accYmean = np.mean(accY[100:200])
    accZmean = np.mean(accZ[100:200])
    gyroXmean = np.mean(gyroX[100:200])
    gyroYmean = np.mean(gyroY[100:200])
    gyroZmean = np.mean(gyroZ[100:200])
    magXvar = np.var(magX[100:200])
    magYvar = np.var(magY[100:200])
    magZvar = np.var(magZ[100:200])
    accXvar = np.var(accX[100:200])
    accYvar = np.var(accY[100:200])
    accZvar = np.var(accZ[100:200])
    gyroXvar = np.var(gyroX[100:200])
    gyroYvar = np.var(gyroY[100:200])
    gyroZvar = np.var(gyroZ[100:200])
    magXstd = np.std(magX[100:200])
    magYstd = np.std(magY[100:200])
    magZstd = np.std(magZ[100:200])
    accXstd = np.std(accX[100:200])
    accYstd = np.std(accY[100:200])
    accZstd = np.std(accZ[100:200])
    gyroXstd = np.std(gyroX[100:200])
    gyroYstd = np.std(gyroY[100:200])
    gyroZstd = np.std(gyroZ[100:200])

    #Pre-processed data:
    magXpre = magX - magXmean
    magYpre = magY - magYmean
    magZmpre = magZ - magZmean
    accXpre = accX - accXmean
    accYpre = accY - accYmean
    accZpre = accZ - accZmean
    gyroXpre = gyroX - gyroXmean
    gyroYpre = gyroY - gyroYmean
    gyroZpre = gyroZ - gyroZmean

    plt.figure(1)
    plt.subplot(3,2,1)
    plt.plot(count, accX)
    plt.title('Accelerometer Raw')
    plt.ylabel('accX')

    plt.subplot(3,2,2)
    plt.plot(count, accXpre)
    plt.title('Accelerometer Preprocessed')
    plt.ylabel('accXPre')

    plt.subplot(3,2,3)
    plt.plot(count, accY)
    plt.ylabel('accY')

    plt.subplot(3,2,4)
    plt.plot(count, accYpre)
    plt.ylabel('accYPre')

    plt.subplot(3,2,5)
    plt.plot(count, accZ)
    plt.ylabel('accZ')
    plt.xlabel('Data point')

    plt.subplot(3,2,6)
    plt.plot(count, accZpre)
    plt.ylabel('accZPre')
    plt.xlabel('Data point')

    plt.show()
else:
    print("Not enough data")
print(accZstd)
