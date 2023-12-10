//  HIGH - es paagado
//  LOW - es prendido

#include <SD.h>           // Para manejar la tarjeta SD
#include <AudioOutputI2SNoDAC.h>
#include <AudioFileSourceSD.h>
#include <AudioGeneratorWAV.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SD_ChipSelectPin D1  // Pin de la tarjeta SD , D2

#include "config.h"

AudioGeneratorWAV *wav;
AudioFileSourceSD *file;
AudioOutputI2SNoDAC *out;

const int LEDPin = LED_BUILTIN;        // pin para el LED
const int PIRPin = D2;         // pin de entrada (for PIR sensor)

const bool led_on = LOW;
const bool led_off = HIGH;

int pirState = LOW;           // de inicio no hay movimiento
int val = 0;                  // estado del pin

WiFiClient wifiClient;

void setup()
{
  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);
  pinMode(PIRPin, INPUT);
  digitalWrite(LEDPin, led_off);

  if (UsarAudio == 1 && !SD.begin(SD_ChipSelectPin)) {
    Serial.println("Fallo en la inicialización de la SD");
    digitalWrite(LEDPin, led_on);
    return;
  }

  wav = new AudioGeneratorWAV();
}

void loop()
{
  if (UsarAudio == 0 && UsarIFTTT == 1)
  {
    BasicoConInternet();
  }
  else
  {
    CodigoCompleto();
  }

}

void BasicoConInternet() {

  val = digitalRead(PIRPin);

  if (val == HIGH)   //si está activado
  {
    digitalWrite(LEDPin, led_on);  //LED ON
    if (pirState == LOW)  //si previamente estaba apagado
    {
      Serial.println("Sensor activado");
      pirState = HIGH;
      enviarSolicitudIFTTT();
    }
  }
  else   //si esta desactivado
  {
    digitalWrite(LEDPin, led_off); // LED OFF
    if (pirState == HIGH)  //si previamente estaba encendido
    {
      Serial.println("Sensor parado");
      pirState = LOW;
    }
  }

}


void CodigoCompleto() {
  if (wav->isRunning()) {
    if (!wav->loop())
    {
      wav->stop();
    }
  } else
  {

    val = digitalRead(PIRPin);

    if (val == HIGH)   //si está activado
    {
      digitalWrite(LEDPin, led_on);  //LED ON
      if (pirState == LOW)  //si previamente estaba apagado
      {
        Serial.println("Sensor activado");
        pirState = HIGH;
        if (UsarIFTTT == 1) {
          enviarSolicitudIFTTT();
        }
        file = new AudioFileSourceSD(AudioAEjecutar);
        out = new AudioOutputI2SNoDAC();
        wav->begin(file, out);
      }
    }
    else   //si esta desactivado
    {
      digitalWrite(LEDPin, led_off); // LED OFF
      if (pirState == HIGH)  //si previamente estaba encendido
      {
        Serial.println("Sensor parado");
        pirState = LOW;
      }
    }

  }
}

void enviarSolicitudIFTTT() {
  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("Se manda la respuesta");
    HTTPClient http;
    String url = "http://maker.ifttt.com/trigger/" + String(eventName) + "/with/key/" + iftttKey;
    http.begin(wifiClient, url); // Modificado aquí
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("Respuesta IFTTT: " + http.getString());
    } else {
      Serial.println("Error en solicitud IFTTT");
    }

    http.end();
  } else {
    Serial.println("Error de conexión WiFi");
  }
}
