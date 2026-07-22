#include <Wire.h>
#include <ArduinoJson.h>
#include "MAX30105.h"
#include "heartRate.h"

#define SDA 8
#define SCL 9
#define RATE_SIZE 4

MAX30105 sensor;

byte rates[RATE_SIZE];
byte rateIndex = 0;

long lastBeat = 0;
long irValue = 0;

long lastRead = 0;
long lastSend = 0;
long lastTemp = 0;

float beatsPerMinute = 0;
float temperature, defaultTemperature;
int beatMoy = 0;

bool beatDetected = false;
bool fingerDetected = false;

String message = "";
String error = "";

void temperatureInit()
{
    sensor.enableDIETEMPRDY();
}

void readTemperature()
{
    defaultTemperature = sensor.readTemperature();
    temperature = 1.08 * defaultTemperature + 1.5;
}

void max30102Init()
{
    Wire.begin(SDA, SCL);

    if (!sensor.begin(Wire, I2C_SPEED_FAST))
    {
        error = "Max30102 introuvable";
        while (1);
    }

    sensor.setup();

    sensor.setPulseAmplitudeRed(0x0A);
    sensor.setPulseAmplitudeIR(0x0A);
    sensor.setPulseAmplitudeGreen(0);
}

void readMax30102()
{
    irValue = sensor.getIR();

    if (irValue < 10000)
    {
        fingerDetected = false;

        error = "Aucun doigt detecté";
        message = "Veuillez placer votre index";

        beatsPerMinute = 0;
        beatMoy = 0;

        return;
    }

    beatDetected = checkForBeat(irValue);

    error = "";
    message = "";

    fingerDetected = true;

    if (beatDetected)
    {
        long delta = millis() - lastBeat;

        lastBeat = millis();
        
        beatsPerMinute = 60.0 / (delta / 1000.0);
        
        if (beatsPerMinute > 20 && beatsPerMinute < 255)
        {
            rates[rateIndex++] = (byte)beatsPerMinute;
            rateIndex %= RATE_SIZE;
            beatMoy = 0;

            for (byte i = 0; i < RATE_SIZE; i++)
            {
                beatMoy += rates[i];
            }

            beatMoy /= RATE_SIZE;
        }
        rgbLedWrite(LED_BUILTIN, 255, 0, 0);
    }
    else
    {
        rgbLedWrite(LED_BUILTIN, 0, 0, 0);
    }
}

void sendData()
{
    JsonDocument data;

    data["device"] = "BioCore";
    data["time"] = millis();
    data["beatDetected"] = beatDetected;
    data["fingerDetected"] = fingerDetected;
    data["message"] = message;
    data["error"] = error;
    data["irValue"] = irValue;
    data["bpm"] = beatsPerMinute;
    data["beatMoy"] = beatMoy;
    data["temperature"] = temperature;
    
    serializeJson(data, Serial);

    Serial.println();
}

void setup()
{
    Serial.begin(115200);

    max30102Init();
    temperatureInit();
}

void loop()
{
    readMax30102();

    if (millis() - lastTemp > 10000)
    {
        lastTemp = millis();
        readTemperature();
    }
    sendData();
}