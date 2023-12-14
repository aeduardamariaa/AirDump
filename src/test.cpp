#include "BluetoothSerial.h"
#include <Arduino.h>
#include "DHT.h"

const uint8_t PIN_INPUT = 26;

#define DHTTYPE DHT11

DHT dht(PIN_INPUT, DHTTYPE);

BluetoothSerial SerialBT;

void enviarDadosBluetooth(float humidade, float temperatura) {
    // Converter umidade e temperatura para valores inteiros
    uint8_t humidadeInt = static_cast<uint8_t>(humidade);
    uint8_t temperaturaInt = static_cast<uint8_t>(temperatura);

    // Construir os bytes para envio
    byte dados[2];
    dados[0] = humidadeInt;
    dados[1] = temperaturaInt;

    // Enviar dados via Bluetooth
    SerialBT.write(dados, 2);
}

void setup() {
    dht.begin();
    Serial.begin(115200);
    SerialBT.begin("esp32bt");
    Serial.println("Started!");
}

void loop() {
    float humidade = dht.readHumidity();
    float temperatura = dht.readTemperature();

    if (isnan(humidade) || isnan(temperatura)) {
        Serial.println("Falha na leitura do sensor DHT");
        return;
    }

    Serial.printf("Humidade: %4.2f\nTemperatura: %7.2f\n\n", humidade, temperatura);

    // Enviar dados via Bluetooth
    enviarDadosBluetooth(humidade, temperatura);

    delay(5000);
}
