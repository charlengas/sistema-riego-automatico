/***************************************************/
/* Proyecto Modulo 1: sistema_riego_automatico.ino */
/* Autores: Charlie(05) y Juanma(06)               */
/* Fecha: 09-05-2025                               */
/***************************************************/

#include <DHT.h>  // Incluimos libreria para Sensor de Temperatura y Humedad del Aire DHT11

#define DHTpin 4       // Definimos el pin digital por el que pasaran los datos recopilados del Sensor DHT11
#define DHTtype DHT11  // Definimos el modelo del Sensor DHT11 para que la libreria "DHT.h" distinga/selecione los parametros relacionados al modelo correspondiente

DHT dht(DHTpin, DHTtype);  // Confirmamos a la libreria la estructura para el uso del Sensor DHT11 y facilitamos la escritura en el programa con el uso de minusculas para las peticiones

int humedadT = 0;  // Declaramos variable de tipo Entero con valor '0' para que el Sensor de Humedad en Tierra YL-69, inicialice la lectura de datos progresivamente
int relePIN = 31;  // Declaramos variable de tipo Entero correspondiente al pin que ocupa la conexion de datos que realizan la comunicacion con el Rele
int ledPIN = 13;   // Declaramos variable de tipo Entero correspondiente al pin que ocupa la conexion de datos que realizan la comunicacion con el LED indicador de estado


void setup() {
  Serial.begin(9600);                     // Activamos la escucha del Monitor Serie con 9600 baudios = 9600 bits/segundo (Velocidad de Transmision de los Datos entre Arduino-Mega y Serial Monitor de Arduino IDE)
  dht.begin();                            // Activamos la escucha del Sensor DHT11
  Serial.println("Sensor DHT11 listo!");  // Si los pasos anteriores se han realizado correctamente, se imprime una linea en el Monitor Serie que avisa que el Sensor DHT11 esta listo y funcionando
  pinMode(DHTpin, OUTPUT);                // Declaramos el modo de uso para el pin digital 4 vinculado al Sensor DHT11
  pinMode(relePIN, OUTPUT);               // Declaramos el modo de uso para el pin digital 31 vinculado al Sensor DHT11
  pinMode(ledPIN, OUTPUT);                // Declaramos el modo de uso para el pin digital 13 (LED_BUILTIN) vinculado al Sensor DHT11
}

void loop() {
  humedadT = analogRead(A0);  // Definimos y Activamos el pin analogico para la lectura de datos del Sensor en Tierra YL-69
  Serial.println(humedadT);   // Se imprime una linea en el Monitor Serie el valor captado en el pin analogico A0 correspondiente al Sensor en Tierra YL-69 (con salto de linea)

  float tC = dht.readTemperature();  // Declaramos y Activamos la funcion que vamos a utilizar para leer la Temperatura del Aire en numeros decimales ya pre-configurada en ºC de la libreria "DHT.h"
  float HA = dht.readHumidity();     // Declaramos y Activamos la funcion que vamos a utilizar para leer la Humedad del Aire en numeros decimales ya pre-configurada en tipo porcentaje % de la libreria "DHT.h"

  if (isnan(tC) || isnan(HA)) {                  // Con una funcion if(), revisamos que el Sensor DHT11 no tenga falta o error en los datos de Temperatura y Humedad del Aire recopilados
    Serial.println("Error al leer el sensor!");  // Se imprime una linea en el Monitor Serie avisando de Error en el caso de que la funcion if() se cumpla (la lectura de algun parametro del DHT11 este fallando)
    delay(2000);                                 // Esperamos 2s para darnos un margen
    return;                                      // Volvemos a comprobar en bucle la lectura de datos del Sensor DHT11 hasta que sea correcta y obtengamos ambos parametro (Temperatura y Humedad del Aire)
  }
  Serial.print("Temperatura: ");  // En caso de no haber errores en la lectura de datos, se imprime por el Monitor Serie el texto entre comillas
  Serial.print(tC);               // Se imprime en la misma linea del Monitor Serie el valor captado por el Sensor DHT11 correspondiente a la Temperatura del Aire en ºC
  Serial.println(" ºC");          // Se imprime por el Monitor Serie el texto entre comillas y se da un salto de linea
  Serial.print("Humedad: ");      // Se imprime por el Monitor Serie el texto entre comillas
  Serial.print(HA);               // Se imprime en la misma linea del Monitor Serie el valor captado por el Sensor DHT11 correspondiente a la Humedad del Aire en %
  Serial.println(" %");           // Se imprime por el Monitor Serie el texto entre comillas y se da un salto de linea

  if (humedadT <= 100) {          // Con una funcion if(), revisamos que los datos de Humedad en Tierra del Sensor YL-69 esten por debajo de lo que definimos como un ambiente seco
    digitalWrite(relePIN, LOW);   // Si los niveles de seco son bajos, entendemos que la humedad es correcta y dejamos el Rele (Bomba de Agua) desactivados
    digitalWrite(ledPIN, LOW);    // Si el Rele (Bomba de agua) se encuentran desactivados, la funcion principal del Sistema de Riego Automatico debe desactivar el aviso de estado (el sistema no estaria en marcha)
  } else {                        // En el caso de que los valores de la Humedad en Tierra del Sensor YL-69 sean superiores al rango adecuado ejecuta este otro caso siguiente:
    digitalWrite(relePIN, HIGH);  // Encender/activar funcionamiento del Rele(Bomba de Agua)
    digitalWrite(ledPIN, HIGH);   // Encender/activar el LED indicador del estado activo del Sistema de Riego Automatico
  }
  delay(500);  // Esperamos medio segundo para darnos un margen
}











// Planteamiento de Mejoras: Funcion propia relacionada al sensor DHT11 para reducir codigo en loop (Funcion Main/Principal del programa)
/*void HT() {
  float tC = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(tC) || isnan(h)) {
    Serial.println("Error al leer el sensor!");
    delay(2000);
    return;
  }
  Serial.print("Temperatura: ");
  Serial.print(tC);
  Serial.println(" ºC");
  Serial.print("Humedad: ");
  Serial.print(h);
  digitalWrite(ledPIN,HIGH);
  delay(500);
  digitalWrite(ledPIN,LOW);
  delay(500);
}
*/