import serial

serial_port = '/dev/cu.usbmodem14111';
baud_rate = 57600; #In arduino, Serial.begin(baud_rate)
write_to_file_path = "output.txt";

output_file = open("tilt.txt", "w+");
ser = serial.Serial(serial_port, baud_rate)
while True:
    line = ser.readline();
    line = line.decode("utf-8") #ser.readline returns a binary, convert to string
    print(line);
    output_file.write(line);
