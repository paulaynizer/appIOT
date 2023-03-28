//Bibliotecas necessárias
#include <Arduino.h>
#include "FirebaseESP8266.h" 
#include <ESP8266WiFi.h>
#include <DHT.h> 

//Configurações Firebase
#define FIREBASE_HOST "fir-iot-712bc-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "5yMqlvAfqUg7orKqeyP3NpWAL1OjXJV75PBx69bf"

//Configurações WIFI
#define WIFI_SSID "WIFI_SSID"
#define WIFI_PASSWORD "PASSWORD"

//Definição pinos
#define DHTPIN 2    
int led1 = D6;      
int led2 = D7;
int led3 = D8;
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

//Objetos Firebase
FirebaseData firebaseData;
FirebaseData led1Data;
FirebaseData led2Data;
FirebaseData led3Data;


FirebaseJson json;

void setup()
{

  Serial.begin(9600);
  dht.begin();
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  //Conecta WIFI e Firebase
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}


void sensorUpdate(){
  //Leitura sensor umidade
  float h = dht.readHumidity();
  //Leitura temperatura celsius
  float t = dht.readTemperature();
  //Leitura temperatura Fahrenheit
  float f = dht.readTemperature(true);


  // Verifica se leitura falhou
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C  ,"));
  Serial.print(f);
  Serial.println(F("°F  "));

  //Envio das leituras para o Firebase
  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/temperature", t))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }


  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/humidity", h))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
}
void loop() {
  //Atualiza leituras
  sensorUpdate();
  //Controles dos Leds ascendendo de acordo com os dados no Firebase
  //LED 1
  if (Firebase.getString(led1Data, "/FirebaseIOT/led/led1")){
    Serial.println(led1Data.stringData());
    if (led1Data.stringData() == "1" | led1Data.stringData() == "true") {
    digitalWrite(led1, HIGH);
    }
  else if (led1Data.stringData() == "0" | led1Data.stringData() == "false"){
    digitalWrite(led1, LOW);
    }
  }
  //LED 2
  if (Firebase.getString(led2Data, "/FirebaseIOT/led/led2")){
    Serial.println(led2Data.stringData());
    if (led2Data.stringData() == "1" | led2Data.stringData() == "true") {
    digitalWrite(led2, HIGH);
    }
  else if (led2Data.stringData() == "0" | led2Data.stringData() == "false"){
    digitalWrite(led2, LOW);
    }
  }
  //LED 3
  if (Firebase.getString(led3Data, "/FirebaseIOT/led/led3")){
    Serial.println(led3Data.stringData());
    if (led3Data.stringData() == "1" | led3Data.stringData() == "true") {
    digitalWrite(led3, HIGH);
    }
  else if (led3Data.stringData() == "0" | led3Data.stringData() == "false"){
    digitalWrite(led3, LOW);
    }
  }
  delay(100);
}


