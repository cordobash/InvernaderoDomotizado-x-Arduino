// Creamos el servidor web usando WiFiServer
// Servidor Web
#include <WiFi.h>

//const char* ssid     = "Megacable_2.4G_0398";
//const char* password = "xtnv5HYN";

const char* ssid = "Megacable_2.4G_11CE";
const char* password = "ArFx5LGh";
WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
  client.print("<!DOCTYPE HTML>");
  client.print("<html>");
  client.print("<head>");
  client.print("<title>Invernadero Domotizado</title>");// Asignamos el nombre del titulo
  client.print("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  // Mandamos a llamar a bootstrap para darle estilo a la pagina
  client.print("<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/css/bootstrap.min.css' integrity = 'sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm' crossorigin = 'anonymous'>"); // Mandamos a llamar a bootstrap
  // En efecto, funciona Bootstrap aqui
  client.print("</head>");
  client.print("<body>");// Iniciamos la etiqueta body, en donde estara todo el html en si
  // Creacion de las tablas
  client.print("<div class='container mt-3'>") ; // Iniciamos el contenedor
  client.print("<table class='table table-dark'>"); // Le damos estilo a la tabla
  client.print("<thead>"); // Abirmos el thead
  // Atributos de la tabla
  client.print("<th>Num.Registro</th>");
  client.print("<th>Bomba de agua</th>");
  client.print("<th>Bombilla</th>");
  client.print("<th>Humedad del suelo</th>");
  client.print("<th>Nivel del agua</th>");
  client.print("<th>Puerta</th>");
  client.print("<th>Temperatura del agua</th>");
  client.print("<th>Temperatura ambiente</th>");
  client.print("</thead>"); // Cerramos el thead
  //----------------------------------------------------------------------------------
  // Hasta aqui probamos la primer parte del codigo y funciona
// Hasta aqui todo bien
client.print("<tbody id='tbody1'></tbody>"); // Iniciamos el tbody
client.print("</table>"); // Cerramos la tabla
client.print("</div>");// Cerramos el div

// Invocamos los scripts necesarios
client.print("<script src='https://code.jquery.com/jquery-3.2.1.slim.min.js' integrity='sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN' crossorigin='anonymous'></script>");
client.print("<script src='https://cdn.jsdelivr.net/npm/popper.js@1.12.9/dist/umd/popper.min.js' integrity='sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q' crossorigin='anonymous'></script>");
client.print("<script src='https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/js/bootstrap.min.js' integrity='sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl' crossorigin='anonymous'></script>");  

// El script que se encarga de las operaciones en la talba
client.print("<script type='module'>");
client.print("var regNo = 0;"); // El contandor de registros
client.print("var tbody = document.getElementById('tbody1');"); // El tbody
// Anadimos la funcion para ingresar items a la tabla
client.print("function AddItemToTable(bomba,bombilla,humedad,nivelAgua,puerta,tempAgua,tempAmbiente){");
client.print("let trow = document.createElement('tr');"); // Creamos una fila
client.print("let td1 = document.createElement('td');"); // Creamos una columna
client.print("let td2 = document.createElement('td');"); // Creamos una columna
client.print("let td3 = document.createElement('td');"); // Creamos una columna
client.print("let td4 = document.createElement('td');"); // Creamos una columna
client.print("let td5 = document.createElement('td');"); // Creamos una columna
client.print("let td6 = document.createElement('td');"); // Creamos una columna
client.print("let td7 = document.createElement('td');"); // Creamos una columna
client.print("let td8 = document.createElement('td');"); // Creamos una columna
// Hacemos los innerHTML
client.print("td1.innerHTML = ++regNo;");
client.print("td2.innerHTML = bomba;");
client.print("td3.innerHTML = bombilla;");
client.print("td4.innerHTML = humedad;");
client.print("td5.innerHTML = nivelAgua;");
client.print("td6.innerHTML = puerta;");
client.print("td7.innerHTML = tempAgua;");
client.print("td8.innerHTML = tempAmbiente;");
// bomba,bombilla, humedadad, movimiento, puerta, tempAgua, tempAmbiente
client.print("trow.appendChild(td1);");
client.print("trow.appendChild(td2);");
client.print("trow.appendChild(td3);");
client.print("trow.appendChild(td4);");
client.print("trow.appendChild(td5);");
client.print("trow.appendChild(td6);");
client.print("trow.appendChild(td7);");
client.print("trow.appendChild(td8);");
// el append al renglon
client.print("tbody.appendChild(trow);");
client.print("}"); // Cerramos la funcion

// Importamos la funcion de firebase
client.print("import {initializeApp} from 'https://www.gstatic.com/firebasejs/9.14.0/firebase-app.js';");
client.print("const firebaseConfig = {");
client.print("apiKey: 'AIzaSyAth51Y0Nr1wSgHHRmaRnFUvjyLTu6Um18',"); // La api de la aplicacion de firebase
client.print("authDomain: 'invernaderodomotizadodb.firebaseapp.com',"); // el dominio en el que esta nuestra db
client.print("projectId: 'invernaderodomotizadodb',"); // El id del proyecto
client.print("storageBucket: 'invernaderodomotizadodb.appspot.com',"); // El almacenamiento
client.print("messagingSenderId: '658102291357',"); // El id del mensajero
client.print("appId: '1:658102291357:web:28a63e712da17358dffd74'");
client.print("};"); // Cerramos la config
// Hasta aqui hicimos la segunda prueba y funciona
// Iniciamos firebase y le mandamos la base de datos como referencia
client.print("const app = initializeApp(firebaseConfig);");
client.print("import { getDatabase, ref, child, onValue, get }"); // Importamos las funciones de firebase
client.print("from 'https://www.gstatic.com/firebasejs/9.14.0/firebase-database.js';"); // Importamos la base de datos

// Trabajamos con la base de datos
client.print("const db = getDatabase();");// Obtenemos el contexto
// Hacemos una funcion para anadir los items a la tabla
client.print("function AddAllItemsToTable(Sensores){");
client.print("regNo++;"); // Incrementamos el contador
client.print("tbody.innerHTML = '';"); // Limpiamos el tbody
client.print("Sensores.forEach(element => {"); // Iteramos sobre los elementos
client.print("AddItemToTable(element.bomba,element.bombilla,element.humedadSuelo,element.nivelAgua,element.puerta,element.tempAgua,element.tempAmbiente);"); // Anadimos el item a la tabla
client.print("})"); // Cerramos el foreach
client.print("}"); // Cerramos la funcion

// Hacemos una funcion para obtener los datos de la base de datos
client.print("function GetAllDataOnce(){");
client.print("const dbRef = ref(db);"); // Obtenemos la referencia de la base de datos
client.print("get(child(dbRef, 'Sensores')).then((snapshot) => {"); // Obtenemos los datos de la base de datos
client.print("var sensores = [];"); // Creamos un arreglo para los sensores
client.print("snapshot.forEach(childSnapshot => {"); // Iteramos sobre los elementos
client.print("sensores.push(childSnapshot.val());"); // Anadimos el valor al arreglo
client.print("});"); // Cerramos el foreach
client.print("AddAllItemsToTable(sensores);"); // Anadimos los items a la tabla
client.print("})"); // Cerramos el get
client.print("}"); // Cerramos la funcion
// Hacemos que se carge la tabla
client.print("window.onload = GetAllDataOnce();");
// Funcion para los datos en tiempo real
client.print("function GetAllDataRealTime(){");// abrimos funcion para obtener datos en tiempo real
client.print("const dbRef = ref(db, 'Sensores');"); // Obtenemos la referencia de la base de datos
client.print("onValue(dbRef, (snapshot) => {"); // Obtenemos los datos de la base de datos
client.print("var sensores = [];"); // Creamos un arreglo para los sensores
client.print("snapshot.forEach(childSnapshot => {"); // Iteramos sobre los elementos)")
client.print("sensores.push(childSnapshot.val());"); // Anadimos los elementos al arreglo
client.print("});"); // Cerramos el foreach
client.print("AddAllItemsToTable(sensores);"); // Anadimos los items a la tabla
client.print("})"); // Cerramos el onValue
client.print("}"); // Cerramos la funcion
// Hacemos que se carge la tabla
client.print("window.onload = GetAllDataRealTime();");
// Cerramos el script
client.print("</script>");
// Fin del codigo en js


// Fin del codigo en js

client.print("</body>");
client.print("</html>");
// Fin del codigo en js
            // the content of the HTTP response follows the header:
//            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
//            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
