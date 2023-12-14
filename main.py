from bluetoothConnection import BluetoothConnection

BLUETOOTH_ADDRESS = 'E0:5A:1B:C7:FF:56'
btconn = BluetoothConnection(BLUETOOTH_ADDRESS, 1, 1)
btconn.connect()
print(btconn.connection())


while(1):

    noteESP = list(btconn.getPressedFromBT())[0]

    print(noteESP)
