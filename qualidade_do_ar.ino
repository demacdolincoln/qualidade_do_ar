#include <SPI.h>
#include <SD.h>
#include <dht.h>
#include <virtuabotixRTC.h>  
#define DHT11_PIN 5
virtuabotixRTC myRTC(6, 7, 8);
dht DHT;
File myFile;
int led =4;
int sensImpureza=A0;
int valorSensor=0;
int umidade=0;
int temperatura=0;

void setup(){
  Serial.begin(9600);
  // (segundos, minutos, hora, dia da semana, dia do mes, mes, ano)
//  myRTC.setDS1302Time(0, 39, 9, 4, 25, 10, 2017);
pinMode(led,OUTPUT);
digitalWrite(led,1);
pinMode(sensImpureza,INPUT);
myFile.println("data,hora,umidade,temperatura,SensorImpureza");  
Serial.println("data,hora,umidade,temperatura,SensorImpureza");  

  if (!SD.begin(4)) {
//    Serial.println("initialization failed!");
//    return;
  }
//  Serial.println("initialization done.");

  myFile = SD.open("teste.csv", FILE_WRITE);

   if (myFile) {
//    Serial.print("Writing to teste.csv...");
//    myFile.println("testing 1, 2, 3.");
//    myFile.close();
//    Serial.println("done.");
//  } else {
//    Serial.println("error opening teste.csv");
  }

  myFile = SD.open("teste.csv");
  if (myFile) {
//    Serial.println("teste.csv:");

    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
//    Serial.println("error opening teste.csv");
  }
}

void loop(){
  valorSensor = analogRead(sensImpureza);
  umidade = DHT.humidity;
  temperatura = DHT.temperature;
  myRTC.updateTime();
//   Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
//    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
  //dia,mes,ano,hora,minuto,segundo,umidade,temperatura,SensorImpureza
 Serial.print(myRTC.dayofmonth);
 Serial.print("/");
 Serial.print(myRTC.month);
 Serial.print("/");
 Serial.print(myRTC.year);
 Serial.print(",");
 Serial.print(myRTC.hours);
 Serial.print(":");
 Serial.print(myRTC.minutes);
 Serial.print(":");
 Serial.print(myRTC.seconds);
 Serial.print(",\t\t");
// Serial.print(DHT.humidity, 1);
 Serial.print(umidade);
 Serial.print(",\t");
// Serial.print(DHT.temperature, 1);
 Serial.print(temperatura);
 Serial.print(",\t");
 Serial.println(valorSensor);
 
myFile = SD.open("teste.csv", FILE_WRITE);
   if (myFile) {
 //dia,mes,ano,hora,minuto,segundo,umidade,temperatura,sensorImpureza
 myFile.print(myRTC.dayofmonth);
 myFile.print("/");
 myFile.print(myRTC.month);
 myFile.print("/");
 myFile.print(myRTC.year);
 myFile.print(",");
 myFile.print(myRTC.hours);
 myFile.print(":");
 myFile.print(myRTC.minutes);
 myFile.print(":");
 myFile.print(myRTC.seconds);
 myFile.print(",");
 myFile.print(umidade);
 myFile.print(",");
 myFile.print(temperatura);
 myFile.print(",");
 myFile.println(valorSensor);
    myFile.close();
   }
   delay(10000);
  
}
