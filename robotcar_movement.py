import curses
import serial

ser = serial.Serial('/dev/ttyACM0',115200, timeout=0, write_timeout=0)
ser.flush()


class car:
        def __init__(self,name,max,min):
                self.name = name
                self.max = max
                self.min = min

#send a signal to move straight forward
        def forward(self):
                ser.write(b'F')
#send a comand to move straight backwards
        def backward(self):
                ser.write(b"B")
#send a comand to move forward and slightly to the left
        def slightleft(self):
                ser.write(b'L')
#send a comand to move forward and slightly to the right
        def slightright(self):
                ser.write(b'R')
#send a comand to stop the car
        def stopcar(self):
                ser.write(b'H')
#send a comand to turn the car sharply to the right
        def sharpright(self):
                ser.write(b'E')
#send a comand to turn the car sharply to the left
        def sharpleft(self):
                ser.write(b'Q')
#send a comand to the senser to take a measurement
        def senser(self):
                ser.write(b'X')
#send a comand  to turn to the right when the distance between the car
#and wall is above the max
        def abovemax(self):
                ser.write(b'S')
#send a comad to turn to the right when the distance between the car
#and wall is below the min
        def belowmin(self):
                ser.write(b'T')

robotcar = car("bigmac",int(600),int(500))


def football():
        key = curses.initscr()
        curses.cbreak()
        curses.noecho()
        key.keypad(1)
        key.nodelay(1)

        k = ' '
        try:
                while k != ord('o'):
                        k = key.getch()
                        key.addch(20,25,k)
                        key.refresh()

                        if k == ord('o'):
                                key.addscr.getch()
                                break
                        elif k == ord('w'):
                                robotcar.forward()
                        elif k == ord('s'):
                                robotcar.backward()
                        elif k == ord('a'):
                                robotcar.slightleft()
                        elif k == ord('d'):
                                robotcar.slightright()
                        elif k == ord('h'):
                                robotcar.stopcar()
                        elif k == ord('e'):
                                robotcar.sharpright()
                        elif k == ord('q'):
                                robotcar.sharpleft()
                        elif k == ord('v'):
                                ser.write(b'V')
        except KeyboardInterrupt:
                pass


def wallfollow():
        abovemax = robotcar.abovemax()
        ser.write(b'V')
        #robotcar.belowmin()
        while True:
                robotcar.senser()
                if ser.in_waiting > 0:
                        print("stage 1")
                        distance = int(ser.readline().decode('utf_8').rstrip())
                        if distance > robotcar.max:
                                print ("stage 2")
                                abovemax
                        elif distance < robotcar.min:
                                robotcar.belowmin()
                                print ("stage 3")
                        else:
                                print ("stage 4")
                                robotcar.forward()
print ("welcome to the Robotcar selections screen would you like to play football or follow a wa$
print ("if you'd like to play football type f and if you want to follow a wall type w ")
option = input("please pick now ")

if option == "f":
        football()
elif option == "w":
        wallfollow()

