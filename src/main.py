import ctypes
from bluetoothConnection import BluetoothConnection

BLUETOOTH_ADDRESS = '08:3A:F2:50:B1:92'
btconn = BluetoothConnection(BLUETOOTH_ADDRESS, 1, 1)
btconn.connect()
print(btconn.connection())

current_accelerations = [0.0, 0.0, 0.0]
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

        if (readings[i] > -0.15 and readings[i] < 0.15):
            readings[i] = 0

    for i in range(4):
        time_passed_millis += list(btconn.getPressedFromBT())[0]

    return (readings, time_passed_millis)

def set_current_position(accelerations: list[int], time_passed_millis: int):
    for i in range(3):
        speed = current_speeds[i]
        speed += (accelerations[i] + current_accelerations[i]) / 2 * (time_passed_millis / 1000)

        current_accelerations[i] = accelerations[i]

        position = current_position[i]
        position += (speed + current_speeds[i]) / 2 * (time_passed_millis / 1000)

        current_speeds[i] = speed
        current_position[i] = position

if __name__ == "__main__":

    while(1):
        accelerations, time_passed_millis = receive_readings()

        