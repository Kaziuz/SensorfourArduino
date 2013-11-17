/* Skecth Arduino Sensor Sharp Infrarojo
   Este codigo fue tomado de la pagina
   http://luckylarry.co.uk/arduino-projects/arduino-using-a-sharp-ir-sensor-for-distance-calculation/
*/

//  Puerto analogo IN
int sharp = 1;                                    

void setup() 
{
  Serial.begin(9600);                             
}

void loop() 
{
  //  Esta formula sale de dividir 5v por 1024, para encontrar la distancia
  float volts = analogRead(sharp)*0.0048828125;   
  float distance = 65*pow(volts, -1.10);          
  Serial.println(distance);                      
  delay(50);                                     // arbitary wait time.
}
