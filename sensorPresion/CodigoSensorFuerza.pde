//  Documentacion arduino sensor de fuerza.
//  From the article: http://bildr.org/2012/11/force-sensitive-resistor-arduino
  
int FSR_Pin = A0; //analog pin 0

void setup(){
  Serial.begin(9600);
}

void loop(){
  int FSRReading = analogRead(FSR_Pin); 

  Serial.println(FSRReading);
  delay(250); //just here to slow down the output for easier reading
}
