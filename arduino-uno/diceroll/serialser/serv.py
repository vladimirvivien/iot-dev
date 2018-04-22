import serial 
import dice_roll_pb2

ser = serial.Serial('/dev/tty.usbmodem1411', 9600)
print "wating for data overs serial line..."

roll = dice_roll_pb2.DiceRoll()
while True:
    data = ser.read(128)
    roll.ParseFromBytes(data)

