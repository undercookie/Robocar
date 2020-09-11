import math
import serial
import numpy as np

#variables:
first_variable = 0
#filled with any number over 100, so the program doesn't send the command to stop to the car:
measure_right = 111
measure_straight = 111
measure_left = 111

times_left = 0
times_right = 0
division_for_left = 5.2
division_for_right = 2

if __name__=='__main__':
    ser = serial.Serial('COM3', 115200, timeout=1)
    ser.flush()

while True:

    if ser.in_waiting > 0:

        first_variable = int(ser.readline().decode('utf_8').rstrip())

    if first_variable == 3:
        measure_right = (ser.readline().decode('utf_8').rstrip())
        measure_right = int(measure_right)
        print("Measure right: ")
        print(measure_right)
    elif first_variable == 2:
        measure_straight = int(ser.readline().decode('utf_8').rstrip())
        print("Measure straight: ")
        print(measure_straight)
    elif first_variable == 1:
        measure_left = int(ser.readline().decode('utf_8').rstrip())
        print("Measure left: ")
        print(measure_left)
    else:
        pass

    if measure_straight > 0 and measure_left > 0:
        if measure_left <= 100:
            # make car stop by sending command H:
            ser.write(str("H").encode('utf_8'))
            print("Now stopping the car")
            side_c = math.sqrt(pow(measure_left, 2) + pow(measure_right, 2) - (
                    2 * measure_left * measure_right * (math.cos(math.pi / 3))))
            angle_right = math.acos(
                (pow(side_c, 2) + pow(measure_left, 2) - pow(measure_right, 2)) / (2 * side_c * measure_left))
            times_right = math.ceil(
                (np.rad2deg(angle_right) / division_for_right) * 2)
            print("Times turning right: ")
            print(times_right)
            for x in range(times_right):
                ser.write(str("N").encode('utf_8'))
            ser.write(str("F").encode('utf_8'))
        elif measure_right <= 100:
            ser.write(str("H").encode('utf_8'))
            side_c = math.sqrt(pow(measure_left, 2) + pow(measure_right, 2) - (
                    2 * measure_left * measure_right * (math.cos(math.pi / 3))))
            angle_left = math.acos(
                (pow(side_c, 2) + pow(measure_right, 2) - pow(measure_left, 2)) / (2 * side_c * measure_right))
            times_left = math.ceil(
                (np.rad2deg(angle_left) / division_for_left ) * 2)  
            for x in range(times_left):
                ser.write(str("M").encode('utf_8'))
            ser.write(str("F").encode('utf_8'))
        elif measure_straight <= 100:
            ser.write(str("H").encode('utf_8'))
            print("Now stopping the car")
        else:
            pass

