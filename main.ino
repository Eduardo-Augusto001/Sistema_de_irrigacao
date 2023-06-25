#include <DHT.h>
#include "RTClib.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

RTC_DS1307 rtc;

const int pinSolo = A0;
const int pinChuva = A1;
const int pinRele = 12;
bool chuva;
bool solo;

void setup() {
  Serial.begin(9600);
  setup_RTC();
  dht.begin();
  pinMode(pinSolo, OUTPUT);
  pinMode(pinChuva, OUTPUT);
  pinMode(pinRele, OUTPUT);
}

void setup_RTC() {
  if (!rtc.begin()) {
    Serial.println("RTC nao pode ser encontrado!");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC nao esta funcionando!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void sensor_chuva() {
  int valorChuva = analogRead(pinChuva);
  Serial.print("Sensor de Chuva = ");
  Serial.println(valorChuva);
  if (valorChuva < 500) {
    Serial.println(" => Está chovendo.");
    chuva = true;
  }
  else {
    Serial.println(" => Não está chovendo.");
    chuva = false;
  }
}

void sensor_solo() {
  int valorSolo = analogRead(pinSolo);
  Serial.print("Sensor do Solo = ");
  Serial.println(valorSolo);
  if (valorSolo < 500) {
    Serial.println(" => O solo está úmido.");
    solo = true;
  }
  else {
    Serial.println(" => O solo está seco.");
    solo = false;
  }
}

void control_rele() {
  digitalWrite(pinRele, LOW);  // ligado
  Serial.println("Relé Acionado.");
  delay(5000);
  digitalWrite(pinRele, HIGH); // desligado
}

void teste_RTC(){
  if(!rtc.isrunning()){
    Serial.println("RTC não está funcionando!");
  }
}

void loop() {
  teste_RTC();
  DateTime now = rtc.now();
  int horas = now.hour();

  float humidade = dht.readHumidity();
  
  if (horas >= 18 || horas <= 6) { // Intervalo de acionamento do relé (das 8h às 18h)
    sensor_chuva();
    sensor_solo();
    
    if (chuva == false && solo == false && humidade <= 70) {
      control_rele();
    }
  }
  delay(2000);
}
