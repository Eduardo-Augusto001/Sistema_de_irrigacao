const int pinSolo = A0;
const int pinChuva = A1;
const int pinRele = 8;
bool chuva;
bool solo;

void setup() {
  Serial.begin(9600);
  pinMode(pinSolo, OUTPUT);
  pinMode(pinChuva, OUTPUT);
  pinMode(pinRele, INPUT);
}

void sensor_chuva(){
  int valorChuva = analogRead(pinChuva);
  Serial.print("Sensor de Chuva = ");
  Serial.println(valorChuva);
  if(valorChuva > 500){
    Serial.println(" => Está chovendo.");
    chuva = true;
  }
  else{
    Serial.println(" => Não está chovendo.");
    chuva = false;
  }
}

void sensor_solo(){
  int valorSolo = analogRead(pinSolo);
  Serial.print("Sensor do Solo = ");
  Serial.println(pinSolo);
  if(valorSolo > 500){
    Serial.println(" => O solo está úmido.");
    solo = true;
  }
  else{
    Serial.println(" => O solo está seco.");
    solo = false;
  }
}

void control_rele(){
  delay(10000);
  Serial.println("Relé Acionado.");
  delay(10000);
  digitalWrite(pinRele, HIGH); // desligado
   delay(10000);
   digitalWrite(pinRele, LOW);
}

void loop() {
    sensor_chuva();
    sensor_solo();
    if(chuva == false && solo == false ){
      control_rele();
    }
    delay(10000);
}
  