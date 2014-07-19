//  Documentacion arduino sensor de fuerza.
//  Tomado de http://www.bit-101.com/blog/?p=3831

void setup() {
    pinMode(7, OUTPUT);
}
 
void loop() {
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
    delay(1000);
}
