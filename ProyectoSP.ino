// PROYECTO DE SISTEMAS PROGRAMABLES
// INVERNADERO DOMOTIZADO

// IMPORTACION DE LIBRERIAS
#include  "DHT.h"
#include <DHTesp.h>
#include <Wire.h>


// DECLARACION DE VARIABLES GLOBALES
#define DHTPIN 3 
#define DHTTYPE DHT11
#define RELE 2
#define SIMULADOR 4
#define LED 13

int push_lee = 0;
bool estadoLed=true;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}

// ENCENDEMOS EL FOCO, EL CUAL HARA DE BOMBILLA
void encender_bombilla()
 {
  digitalWrite(RELE,HIGH);
  Serial.print("CALEFACCION");
 }

// ENCENDEMOS LOS VENTILADORES, DEBIDO A QUE LA TEMPETARURA ESTA ALTA.
void encender_aire()
{
  digitalWrite(RELE,LOW);
  Serial.print("REFRIGERACION");
}



void real()
{
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();
  Serial.print("");
  Serial.println(temperatura);
  Serial.println(" - ");
  Serial.println(humedad);
  Serial.println(" % ");

  if(temperatura>25)
      encender_aire();
  else
      encender_bombilla();
  delay(500);
}
