/* Skecth Arduino Sensor Sharp Infrarojo
   Este codigo fue tomado de la pagina
   http://luckylarry.co.uk/arduino-projects/arduino-using-a-sharp-ir-sensor-for-distance-calculation/
*/

//  Puerto analogo IN
#include <Servo.h>
int sharp = 1;     
Servo myservo;  // crea un objeto tipo servo para controlar el servo 

int pos = 0;    // variable para almacenar la posición del servo

void setup() 
{
  Serial.begin(9600);  
  myservo.attach(9);  // liga el servo conectado en el pin 9 al objeto servo
  
}

void loop() 
{
  //  Esta formula sale de dividir 5v por 1024, para encontrar la distancia
  float volts = analogRead(sharp)*0.0048828125;   
  float distance = 65*pow(volts, -1.10);          
  Serial.println(distance);                      
  delay(10);                                     // arbitary wait time.
  
  if (distance >= 100)
  {
    myservo.write(91);
    delay(15);
  }
  else if (distance <= 99)
  {
     for(pos = 0; pos < 180; pos += 1)  // va de 0 a 180 grados
    {                                  // en pasos de 1 grado 
    myservo.write(pos);              // dice al servo que se posicione en la posición indicada por la variable 'pos'
    delay(15);                       // espera 15 ms para dar tiempo al servo a llegar a la nueva posición 
    } 
  }
  
}
