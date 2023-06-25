#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void leitura_dht11(){
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Falha ao ler o sensor DHT11!"));
    return;
  }
  Serial.print(F("Temperatura: "));
  Serial.print(temperature);
  Serial.print(F("°C\t"));

  Serial.print(F("Umidade: "));
  Serial.print(humidity);
  Serial.println(F("%"));
}

void loop() {
  delay(2000);
  leitura_dht11();
}
