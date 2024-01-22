import ctypes
from bluetoothConnection import BluetoothConnection

from play_sound import Data
from play_sound import DrumKit

BLUETOOTH_ADDRESS = '08:3A:F2:50:A8:56'
btconn = BluetoothConnection(BLUETOOTH_ADDRESS, 1, 1)
btconn.connect()
print(btconn.connection())

movement_over_time = [list(), list(), list()]
current_state = [0, 0, 0]
movement_started = [False, False, False]
capture_started = [False, False, False]
capture_ended = [False, False, False]

new_drum = DrumKit()

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

def track_movement(accelerations: list[float], time_passed_millis: int):
    for i in range(3):
        if accelerations[i] > -0.15 and accelerations[i] < 0.15:
            accelerations[i] = 0

        if (current_state[i] == 0) and (accelerations[i] != 0):
            current_state[i] == 1
            movement_over_time[i].append(accelerations[i])
            return

        if current_state[i] == 1:
            if accelerations[i] * movement_over_time[i][0] > 0:
                movement_over_time[i].append(accelerations[i])
                return

            else:
                current_state[i] = 2

        if current_state[i] == 2:
            if accelerations[i] == 0:
                current_state[i] = 3
            else:
                return
    
        if current_state[i] == 3:
            interpret_movement(movement_over_time[i], i)
            current_state[i] = 0

def interpret_movement(accelerations: list[float], axis: int):
    if axis == 2:
        new_drum.change_position([0.0, 0.0, sum(accelerations) / len(accelerations)])
        new_drum.detect_and_play()

if __name__ == "__main__":
    while(1):
        accelerations, time_passed_millis = receive_readings()
        track_movement(accelerations, time_passed_millis)

        print(accelerations)