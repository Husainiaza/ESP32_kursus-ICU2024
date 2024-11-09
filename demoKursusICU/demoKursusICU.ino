//--------------------------------------------------------------------------
//----Seksyen 1 - HEADER  ------------- ----

//--------------------------------------------------------------------------
//-----a Library  include and define  yang diperlukan ----
//--------------------------------------------------------------------------

#include <Wire.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <MQTT.h>
#include "DHT.h"



//--------------------------------------------------------------------------
//-----b. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

//---Actuator and Relay  pin connection---
#define relay01 27 
#define relay02 26
#define buzzer 25
#define SensorSuhu  4 // pin sambungan ke DS18B20 (ONEWIRE)
#define sensorLDR 34
//---Analog Sensor  pin connection---

//---Tentukan nama yg diumpukkan kepada satu nilai awal yg ditetapkan --
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define DHTPIN 5     
#define DHTTYPE DHT21

DHT dht(DHTPIN, DHTTYPE);
//-----d.  - ISTIHAR  constant dan pembolehubah------------------------------

//const char ssid[] = "Haza@unifi";
//const char pass[] = "0135335045";

const char ssid[] = "IoT";
const char pass[] = "iot@kksj2023";

//------ ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---

unsigned long lastMillis = 0;

float dataSuhuC; // suhu dalam Celsius
int dataLDR;

char statusSuhu[20];

//-----e. - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------

WiFiClient net;
MQTTClient client;

// Istihar Module OLED Display - SSD1306 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Istihar Module Sersor Suhu Dallas 18B20
OneWire oneWire(SensorSuhu);
DallasTemperature DS18B20(&oneWire);

//------------------------------Seksyen 1 - TAMAT --------------------- ----

//-----Seksyen 2 - Fungsi Setup --------------------------------------------
//--------------------------------------------------------------------------
void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);

  Serial.begin(115200); // initialize serial

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  WiFi.begin(ssid, pass);

  client.begin("broker.hivemq.com", net);
  client.onMessage(messageReceived);

  connect();

  DS18B20.begin();    // initialize the DS18B20 sensor
  dht.begin();
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("---  iSocket LA  ---");
  display.setCursor(0,10);
  display.println("K. Komuniti Sbg Jaya");
  display.setCursor(10,20);
  display.println("--------------------");
  display.display();
  delay(5000);

}
//------------------------------Seksyen 2 - TAMAT --------------------- ----


//-----Seksyen 3 - Fungsi Utama (LOOP) --------------------------------------------
//--------------------------------------------------------------------------
void loop() {

 client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    client.publish("/hello", "world");

//------sensor suhu -------------------------------------------------------
  
 float humid = dht.readHumidity();
  float temp = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.println(humid);
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("°C ");

 client.publish("kursusICU/temp", String(temp));  
 client.publish("kursusICU/humid", String(humid));  

//------sensor LDR -------------------------------------------------------
  dataLDR = analogRead(sensorLDR);
  Serial.print("Cahaya: ");
  Serial.println(dataLDR);  

  client.publish("kursusICU/ldr", String(dataLDR));  

//------Kawalan relay -------------------------------------------------------  


//------Paparan di OLED Display--------------------------------------------------  
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("---  iSocket LA  ---");
  display.setCursor(0,10);
  display.print("K. Komuniti Sbg Jaya");
  display.setCursor(10,20);
  display.print("--------------------");
  display.setCursor(0,30);
  display.print("BACAAN SUHU :");
  display.print(dataSuhuC,1);
  display.setCursor(0,40);
  display.print("BACAAN LDR  :");
  display.print(dataLDR);
  display.setCursor(0,50);
  display.print(statusSuhu);  
  display.display();  
}
}

//------------------------------Seksyen 3 - TAMAT --------------------- ----