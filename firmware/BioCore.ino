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
byte counter = 0;

long lastBeat = 0;
long irValue = 0;
long lastRead = 0;
long lastSend = 0;

float beatsPerMinute = 0;
int beatMoy = 0;

bool beatDetected = false;
bool fingerDetected = false;

String message = "";
String error = "";

void max30102Init()
{
    Wire.begin(SDA, SCL);

    if (!sensor.begin(Wire, I2C_SPEED_FAST))
    {
        Serial.println("MAX30102 introuvable");
        while (1);
    }

    sensor.setup();

    sensor.setPulseAmplitudeRed(0x1F);
    sensor.setPulseAmplitudeIR(0x1F);

    Serial.println("MAX30102 initialise.");
}

void readMax30102()
{
    irValue = sensor.getIR();

    if (irValue < 50000)
    {
        fingerDetected = false;

        error = "Aucun doigt detecté";
        message = "Veuillez placer votre index";

        beatsPerMinute = 0;
        beatMoy = 0;

        return;
    }

    fingerDetected = true;

    error = "";
    message = "";

    beatDetected = checkForBeat(irValue);

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

            if (counter < RATE_SIZE)
            {
                counter++;
            }
            else
            {
                counter = RATE_SIZE;
            }

            for (byte i = 0; i < counter; i++)
            {
                beatMoy += rates[i];
            }

            beatMoy /= counter;
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
    data["timestamp"] = millis();

    data["fingerDetected"] = fingerDetected;
    data["message"] = message;
    data["error"] = error;
    data["irValue"] = irValue;
    data["bpm"] = beatsPerMinute;
    data["beatMoy"] = beatMoy;

    serializeJson(data, Serial);

    Serial.println();
}

void setup()
{
    Serial.begin(115200);

    max30102Init();
}

void loop()
{
    long now = millis();

    if (now - lastRead >= 10)
    {
        lastRead = now;
        readMax30102();
    }

    if (now - lastSend >= 100)
    {
        lastSend = now;
        sendData();
    }
}