
//  Codigo para suichear por transistor
//  materiales :
//  transistor 2222A
//  pila 9A
//  resistencia 1k

void setup() {
    pinMode(7, OUTPUT);
}
 
void loop() {
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
    delay(1000);
}
