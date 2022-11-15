#include <OneWire.h>                
#include <DallasTemperature.h>
#define sensor A0 //SE DEFINE
#define sensor A1 //SE DEFINE
OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
const byte pinBuzzer = 3; //PIN PWM
byte salida = 10; //Probar con 25
 

void setup() {
pinMode(sensor, INPUT);
Serial.begin(9600);
sensors.begin();   //Se inicia el sensor
}
 
void loop() {
sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

Serial.print("Temperatura= ");//SENSOR DE TEMPERATURA DE AGUA
Serial.print(temp);
Serial.println(" C");
int valorHumedad = map(analogRead(sensor), 0, 1023, 100, 0);
Serial.print("Humedad: ");//SENSOR DE HUMEDAD DE SUELO
Serial.print(valorHumedad);
Serial.println("%"); 
Serial.println("Water level Sensor Value: "); //SENSOR DE NIVEL DE AGUA
Serial.println(analogRead(A1)); //Se lee el valor de A1 para el sensor de nivel de agua
if(analogRead(A1) <= 50) { //Comparacion de si el nivel del agua es igual o menor a 50 se activara el buzzer como alerta de sonido
    analogWrite(pinBuzzer, salida);
}
delay(100);                     
}
