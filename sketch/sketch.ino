#define BLYNK_PRINT Serial

#include <DHT.h>
#include <ESP8266WiFi.h> // file untuk wifi 
#include <BlynkSimpleEsp8266.h> // file untuk blynk

char auth[] = "Nxu2KnuyajwInWDNarIzoDrAPwbrvdFk";
char ssid[] = "A50s";
char pass[] = "kirana321";

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
  float h  = dht.readHumidity();
  float t  = dht.readTemperature();

  if (isnan(h) || isnan(t)) { // mengecek kondisi apabila suhu dan kelembapan tidak ada
    Serial.println("Failed to read temp and humidity");
    return;
  }

  Blynk.virtualWrite(V1, t); //setting virtual suhu di Blynk
  Blynk.virtualWrite(V2, h); //serring virtual kelembapan di Blynk
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin(); //Sensor mulai membaca suhu dan kelembapan 
  timer.setInterval(1000L, sendSensor); // waktu untuk mengirim data setiap 1 detik sekali

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();

}
