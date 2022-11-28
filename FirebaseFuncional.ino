// PROYECTO SISTEMAS PROGRABLES
// CONEXION CON FIREBASE
//---------------------------------------------
// Mandamos a llamar las librerias necesarias
#include <WiFi.h>
#include <WiFiClient.h>
#include <FirebaseESP32.h>
#include <WiFiAP.h>

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

// Definimos las credenciales WiFi
#define WIFI_SSID "miredwifi" // nombre de la red
#define WIFI_PASSWORD "lacontrasena" // contrasena

// Definimos la API del proyecto
#define API_KEY "AIzaSyAth51Y0Nr1wSgHHRmaRnFUvjyLTu6Um18"

// Definimos la url de la base de datos, sin http.
#define DATABASE_URL "invernaderodomotizadodb-default-rtdb.firebaseio.com"
// En caso de ser requerido definimos el email y contrasena
#define USER_EMAIL "correo@gmail.com"
#define USER_PASSWORD "mypass"

// Creamos los objetos necesarios de FireBase, para el manejo de eventos
FirebaseData fbdo; // Manejo de datos
// Para la autenticacion
FirebaseAuth auth; // Se puede usar correo o la api key
FirebaseConfig config; // guardamos todas las config en este objeto
// Definimos bandera para cuando validemos si se ha hecho la conexion a la db
bool band = false;

// Manejamos los millisegundos
unsigned long dataMillis = 0;
int contador = 0;
// Anadimos otra bandera para el proceso de leer, insertar datos
bool hagoAlgo = true;

void setup() {
  // Codigo que se ejecuta solo una vez, de inicio.
  Serial.begin(115200); // Seteamos los baudios, 115200 por el esp32
  Serial.println(); // Salto de linea
  Serial.println("Configurando punto de acceso");
  // Inicializamos la red wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // De ser necesario creamos el punto de accesso
  //WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Conectando a la red wifi");
  // Validamos que mientras no haya una conexion imprima un puntito
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300); // un delay para mantener mas control
  }
  Serial.println(); // En caso de que haye conexion, salto de linea
  Serial.print("Conectado con IP : " +WiFi.localIP());
  Serial.println();  

// Imprimimos el cliente de firebase  que estamos usando
Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

// ZONA IMPORTANTE DE CONFIGURACIONES DE FIREBASE
config.api_key = API_KEY; // Le mandamos la key de la app por la variable que definimos arriba

// Le mandamos las credenciales del correo
auth.user.email = USER_EMAIL;
auth.user.password = USER_PASSWORD;

// Le mandamos a config la url de la base de datos
config.database_url = DATABASE_URL;
// Le mandamos la clave secreta
config.signer.tokens.legacy_token = "23c2ANwtGUvjj4K0K9KV14LB3Xcd9TwxAD4sLpOD";// D
//config.signer.tokens.legacy_token = "23c2ANwtGUvjj4K0K9KV14LB3Xcd9TwxAD4sLpOD";// 
// Inicializamos el proceso dadas las configuraciones y parametros de autenticacion dados
Firebase.begin(&config, &auth);
// Le decimos que se reste reconectando a la red wifi
Firebase.reconnectWiFi(true);

}

void loop() {
  // Validamos si tenemos la conexion a la base de datos
while(!band)  
  if (Firebase.ready())
  {
    Serial.println("OK, Conexion correcta a la base de datos");
    band = true; // Cuando la conexion este hecha entonces nos salimos del while
  } else {
    // Entrara en un loop infinito hasta que se detenga el proceso
    Serial.println("Algo salio mal, revise los parametros de conexion");
  }
// Si todo ha salido bien,
// Manejamos el envio y lectura a la base de datos
while(hagoAlgo){
 // Insertamos algun dato solo para probar
 // Parametros generales para : 
 // Escritura : objeto firebase, nodo, dato a insertar
 // Lectura : objeto firebase, nodo.
 Firebase.setString(fbdo, "/saludar","Segunda prueba");
 Serial.println("Dato insertado");
 // Lectura de datos del nodo que queremos leer.
 Firebase.getString(fbdo,"/saludar");
 // Cambiamos la bandera para que salga del while
 hagoAlgo = false;
 Firebase.end(fbdo); // finalizamos el proceso
} // Fin del while hagoAlgo

} // Fin del loop
