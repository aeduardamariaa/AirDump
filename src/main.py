import ctypes
import time
from bluetoothConnection import BluetoothConnection

BLUETOOTH_ADDRESS = '08:3A:F2:50:B1:92'
btconn = BluetoothConnection(BLUETOOTH_ADDRESS, 1, 1)
btconn.connect()
print(btconn.connection())

current_speeds = [0.0, 0.0, 0.0]
current_position = [0.0, 0.0, 0.0]
count = 0

def receive_readings() -> tuple:
    readings = [0.0, 0.0, 0.0]
    time_passed_millis = int()

    for i in range(3):
        aux = 0
        for j in range(4):
            aux <<= 8
            aux |= list(btconn.getPressedFromBT())[0]

        # C-pointer fuckery to deal with floating-point bitwise operations
        # (because of the way data comes from our bluetooth connection)
        int_pointer = ctypes.pointer(ctypes.c_int(aux))
        float_pointer = ctypes.cast(int_pointer,
                                    ctypes.POINTER(ctypes.c_float))
        readings[i] = float_pointer.contents.value

    for i in range(4):
        time_passed_millis += list(btconn.getPressedFromBT())[0]

    return (readings, time_passed_millis)

def set_current_speeds(accelerations: list[int], time_passed_millis: int):
    for i in range(3):
        current_speeds[i] += accelerations[i] * (time_passed_millis / 1000)

def set_current_position(time_passed_millis: int):
    for i in range(3):
        movement = current_speeds[i] * (time_passed_millis / 1000)

        if movement > -0.01 and movement < 0.01:
            return

        current_position[i] += movement

if __name__ == "__main__":
    starting_time = time.time()

    while(1):
        accelerations, time_passed_millis = receive_readings()

        set_current_speeds(accelerations, time_passed_millis)
        set_current_position(time_passed_millis)

        print(current_position)
        count += 1

        if (time.time() - starting_time >= 10):
            print(count)
            starting_time = time.time()

            break

    print(current_position)