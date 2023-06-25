#include "RTClib.h"

RTC_DS1307 rtc;
char diasDaSemana[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};

void setupRTC() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("RTC nao pode ser encontrado!");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC nao esta funcionando!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void printDateTime(const DateTime& dt) {
  Serial.print(dt.day(), DEC);
  Serial.print('/');
  Serial.print(dt.month(), DEC);
  Serial.print('/');
  Serial.print(dt.year(), DEC);
  Serial.print(" (");
  Serial.print(diasDaSemana[dt.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(dt.hour(), DEC);
  Serial.print(':');
  Serial.print(dt.minute(), DEC);
  Serial.print(':');
  Serial.print(dt.second(), DEC);
  Serial.println();
}
void setup() {
  setupRTC();
}
void loop() {
  DateTime now = rtc.now();
  printDateTime(now);
  delay(2000);
}
