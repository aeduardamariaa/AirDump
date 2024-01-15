from bluetoothConnection import BluetoothConnection

BLUETOOTH_ADDRESS = '08:3A:F2:50:B1:92'
btconn = BluetoothConnection(BLUETOOTH_ADDRESS, 1, 1)
btconn.connect()
print(btconn.connection())

while(1):
    byte_list = list(btconn.getPressedFromBT())

    if len(list) == 3:
        x_accel = byte_list[0]
        y_accel = byte_list[1]
        z_accel = byte_list[2]

        print(f"Acelerações lidas: ({x_accel}, {y_accel}, {z_accel})")