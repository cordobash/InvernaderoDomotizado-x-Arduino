#define sensor A0 //SE DEFINE
#define sensor A1 //SE DEFINE

const byte pinBuzzer = 3; //PIN PWM
byte salida = 10; //Probar con 25 
void setup(){
    pinMode(sensor, INPUT);
    Serial.begin(9600);
  }
 void loop(){
 //Se hace la lectura analoga del pin A0 (sensor) y se pasa por la funcion map() para ajustar los valores leidos a los porcentajes que queremos utilizar   
int valorHumedad = map(analogRead(sensor), 0, 1023, 100, 0);
Serial.print("Humedad: ");
Serial.print(valorHumedad);
Serial.println("%"); 
Serial.println("Water level Sensor Value: ");
Serial.println(analogRead(A1)); //Se lee el valor de A1 para el sensor de nivel de agua
if(analogRead(A1) <= 50) { //Comparacion de si el nivel del agua es igual o menor a 50 se activara el buzzer como alerta de sonido
    analogWrite(pinBuzzer, salida);
}
delay(1000);
  }
