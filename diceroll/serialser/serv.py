import serial 

ser = serial.Serial('/dev/tty.usbmodem1411', 9600)
print "wating for data overs serial line..."

while True:
    print ser.readline()

