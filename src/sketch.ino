#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int gPinTemperaturaExterna = 0;
const int gPinLuminosidade = 1;
const int gPinTemperaturaAgua = 2;

const int gTempoCiclo = 500;

double gTemperaturaExterna;
double gTemperaturaAgua;
double gLuminosidade;

OneWire gOWSensorTemperaturaAgua(gPinTemperaturaAgua);

DallasTemperature gDallasSensors(&gOWSensorTemperaturaAgua);

void medirTemperaturaExterna() {
  double leitura = analogRead(gPinTemperaturaExterna);
  gTemperaturaExterna = ((leitura / 1024.0) * 5000) / 10;
}

void medirTemperaturaAgua() {
  gDallasSensors.requestTemperatures();
  gTemperaturaAgua = gDallasSensors.getTempCByIndex(0);
}

void medirLuminosidade() {
  gLuminosidade = analogRead(gPinLuminosidade);
}

void enviarSinal() {
  Serial.print("TE:"); 
  Serial.print(gTemperaturaExterna); 
  Serial.print(";");

  Serial.print("TA:"); 
  Serial.print(gTemperaturaAgua); 
  Serial.print(";");
  
  Serial.print("LU:"); 
  Serial.print(gLuminosidade); 
  Serial.print(";");
  
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  gDallasSensors.begin();
}

void loop() {
  medirTemperaturaExterna();
  medirTemperaturaAgua();
  medirLuminosidade();

  enviarSinal();

  delay(gTempoCiclo);
}
