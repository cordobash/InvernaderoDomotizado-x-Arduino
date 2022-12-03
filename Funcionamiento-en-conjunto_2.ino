#include <OneWire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <DHT.h>                
#include <DallasTemperature.h>
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  53  //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); ///Creamos el objeto para el RC522
#define sensor A0 //SE DEFINE
#define sensor A1 //SE DEFINE
OneWire ourWire(4);   
//Se establece el pin 4  como bus OneWire
DHT dht(DHTPIN, DHTTYPE);
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
const byte pinBuzzer = 3; //PIN PWM
byte salida = 10; //Probar con 25
 

void setup() {
pinMode(sensor, INPUT);
Serial.begin(9600);
dht.begin();
sensors.begin();   //Se inicia el sensor
SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Control de acceso:");
}

//USUARIOS
byte ActualUID[7]; //almacenará el código del Tag leído
byte ivan[7]= {0x05, 0x8B, 0x4C, 0x54, 0xB0, 0x02, 0x00} ; //código del usuario 1
byte pedro[7]= {0x82,0x87,0x14,0xFA,0x9E,0x47,0xC5} ; //código del usuario 2
byte raul[7]={0x05,0x8A,0xE8,0x98,0xB4,0x62,0x00};
byte oscar[7] = {0x05,0x86,0x5D,0xCD,0xD7,0x72,0x00};
bool mostrar = false;
void loop() {
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
      //Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                  Serial.print(F("Card UID:"));
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                          ActualUID[i]=mfrc522.uid.uidByte[i];          
                  } 
                  Serial.print("     ");                 
                  //comparamos los UID para determinar si es uno de nuestros usuarios  
                  if(compareArray(ActualUID,ivan)) {
                    Serial.println("Acceso concedido...");
                    Serial.print("Light Intensity:");
Serial.print(int(Light(analogRead(2)))); //pin A0
Serial.println(" Lux");
                    // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  // Leemos la temperatura en grados Fahreheit
  float f = dht.readTemperature(true);
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  // Calcular el índice de calor en Fahreheit
  float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
                    sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
                    float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

                    Serial.print("Temperatura de agua= ");//SENSOR DE TEMPERATURA DE AGUA
                    Serial.print(temp);
                    Serial.println(" C");
                    int valorHumedad = map(analogRead(sensor), 0, 1023, 100, 0);
                    Serial.print("Humedad de suelo: ");//SENSOR DE HUMEDAD DE SUELO
                    Serial.print(valorHumedad);
                    Serial.println("%"); 
                    Serial.println("Water level Sensor Value: "); //SENSOR DE NIVEL DE AGUA
                    Serial.println(analogRead(A1)); //Se lee el valor de A1 para el sensor de nivel de agua
                    if(analogRead(A1) <= 50) { //Comparacion de si el nivel del agua es igual o menor a 50 se activara el buzzer como alerta de sonido
                    analogWrite(pinBuzzer, salida);} }
                  else {
                    Serial.println("Acceso denegado...");
                  }
                  // Terminamos la lectura de la tarjeta tarjeta  actual
                  mfrc522.PICC_HaltA();
          
            }
      
  }

delay(100);                     
}

//Función para comparar dos vectores
 boolean compareArray(byte array1[],byte array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}

double Light (int RawADC0)
{
double Vout=RawADC0*0.0048828125;
int lux=500/(10*((5-Vout)/Vout));//use this equation if the LDR is in the upper part of the divider
//int lux=(2500/Vout-500)/10;
return lux;
}
