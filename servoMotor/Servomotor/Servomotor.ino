// Sweep
// por BARRAGAN <http://barraganstudio.com> 
// Este codigo fue tomado de la pagina http://arduino.cc/es/Tutorial/Sweep

#include <Servo.h> 

Servo myservo;  // crea un objeto tipo servo para controlar el servo 

int pos = 0;    // variable para almacenar la posición del servo

void setup() 
{ 
  myservo.attach(9);  // liga el servo conectado en el pin 9 al objeto servo
} 

void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // va de 0 a 180 grados
  {                                  // en pasos de 1 grado 
    myservo.write(pos);              // dice al servo que se posicione en la posición indicada por la variable 'pos'
    delay(15);                       // espera 15 ms para dar tiempo al servo a llegar a la nueva posición 
  } 
  for(pos = 180; pos>=1; pos-=1)     // va de 180 a 0 grados
  {                                
    myservo.write(pos);              // dice al servo que se posicione en la posición indicada por la variable 'pos'
    delay(15);                       // espera 15 ms para dar tiempo al servo a llegar a la nueva posición 
  } 
} 

