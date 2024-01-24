import ctypes
import time
import threading
from bluetoothConnection import BluetoothConnection

from play_sound import Data
from play_sound import DrumKit

BLUETOOTH_ADDRESS = '64:B7:08:CA:69:A2'
btconn = BluetoothConnection(BLUETOOTH_ADDRESS, 1, 1)
btconn.connect()
print(btconn.connection())

new_drum = DrumKit()
z_pos = 0

def receive_readings(conn) -> tuple:
    readings = [0.0, 0.0, 0.0]
    time_passed_millis = int()

    for i in range(3):
        aux = 0
        for j in range(4):
            aux <<= 8
            aux |= list(conn.getPressedFromBT())[0]

        # C-pointer fuckery to deal with floating-point bitwise operations
        # (because of the way data comes from our bluetooth connection)
        int_pointer = ctypes.pointer(ctypes.c_int(aux))
        float_pointer = ctypes.cast(int_pointer,
                                    ctypes.POINTER(ctypes.c_float))
        readings[i] = float_pointer.contents.value

        if readings[i] > -0.15 and readings[i] < 0.15:
            readings[i] = 0

    for i in range(4):
        time_passed_millis += list(conn.getPressedFromBT())[0]

    return (readings, time_passed_millis)

def calculate_z_pos(accelerations: list[float], time: int):
    global z_pos

    if z_pos == (accelerations[2] * (time / 1000)):
        z_pos = 0
    else:
        z_pos = accelerations[2] * (time / 1000)

if __name__ == "__main__":
    initial_time = time.time()
    sound_just_played = False

    while(1):
        accelerations, time_passed_millis = receive_readings(btconn)
        calculate_z_pos(accelerations, time_passed_millis)

        new_drum.change_position([0, 0, z_pos])

        if sound_just_played and (time.time() - initial_time >= 0.5):
            sound_just_played = False

        if not sound_just_played:
            play = threading.Thread(target=new_drum.detect_and_play)
            play.start()

            if z_pos <= -0.01:
                initial_time = time.time()
                sound_just_played = True

            print(accelerations)