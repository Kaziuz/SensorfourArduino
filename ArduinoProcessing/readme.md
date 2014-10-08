===== handshaking - pregunta y respuesta en Serial arduino y processing =====

Crear un sistema con las siguientes caracteristicas:

![Circuito](http://arduino.cc/en/uploads/Tutorial/SerialCallResponse-circuit3.png)

Puede ser cualuier circuito, lo importante es usar dos entradas analogicas y una digital para propositos de esta explicación.

Luego usar este codigo en tu Arduino:

´´´

//  pines analogos establecidos
int firstSensor = 0;    // 1 sensor analogo
int secondSensor = 0;   // 2 sesnor analogo

//  Pines digitales establecidos
int thirdSensor = 0;    // 1 sensor digital
int inByte = 0;         // variable que escucha un byte serial

void setup()
{
  // Empezamos con el serial fijandolo a una velocidad de 9600  bps(baudios por segundos):
  Serial.begin(9600);
  while (!Serial) {
    ; // Necesitamos un puerto serial establecido. Modificar solamente para placas Leonardo
  }

  pinMode(2, INPUT);   // El sensor digital es establecido como Input por en la placa
  establishContact();  // Función que envia un byte (caracter) para establecer contacto hasta que el receptor responda(processing)
}

void loop()
{
  // Si tomamos el byte valido, leemos los puertos analogos entrantes:
  if (Serial.available() > 0) {
    // Tomamos el byte escuchado:
    inByte = Serial.read();

    // Procesamiento pines analogos
    // Leemos esa primera entrada analogica,y la dividimos por 4 para obtener un valor de 0-255:
    firstSensor = analogRead(A0)/4;
    // damos un delay 10ms para que el conversor ADC tenga una esperita de recuperarse:
    delay(10);
    // Leemos la segunda entrada analogica,y la dividimos por 4 para obtener un valor de 0-255:
    secondSensor = analogRead(1)/4;

    // para leer el suiche,mapeamos de 0 a 255L
    thirdSensor = map(digitalRead(2), 0, 1, 0, 255);  
    // mandamos los valores de los sensores:
    Serial.write(firstSensor);
    Serial.write(secondSensor);
    Serial.write(thirdSensor);               
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}
´´´

Despues de insertar o 'ingresar' el codigo en el arduino, abrimos processing e insertamos y ejecutamos el siguiente codigo:

´´´
//  Para utilizar este codigo

int firstSensor = 0;    // first analog sensor
int secondSensor = 0;   // second analog sensor
int thirdSensor = 0;    // digital sensor
int inByte = 0;         // incoming serial byte

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  pinMode(2, INPUT);   // digital sensor is on digital pin 2
  establishContact();  // send a byte to establish contact until receiver responds 
}

void loop()
{
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    // read first analog input, divide by 4 to make the range 0-255:
    firstSensor = analogRead(A0)/4;
    // delay 10ms to let the ADC recover:
    delay(10);
    // read second analog input, divide by 4 to make the range 0-255:
    secondSensor = analogRead(1)/4;
    // read  switch, map it to 0 or 255L
    thirdSensor = map(digitalRead(2), 0, 1, 0, 255);  
    // send sensor values:
    Serial.write(firstSensor);
    Serial.write(secondSensor);
    Serial.write(thirdSensor);               
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}

import processing.serial.*;

int bgcolor;                         // Color de fondo
int fgcolor;                         // color de relleno
Serial myPort;                       // El puerto serial
int[] serialInArray = new int[3];    // serial Array donde recibimos los pines
int serialCount = 0;                 // Un contador serial donde recibimos algunos arrays
int xpos, ypos;                      // posicionX y posicionY
boolean firstContact = false;        // Establecer contacto con el controlador

void setup() {
  size(256, 256);  // fijamos tamaño de pantalla
  noStroke();      // no hay un borde para la proxima figura

  // Fijamos una posición inicial para la bola (middle of the stage)
  xpos = width/2;
  ypos = height/2;

  // Imprimimos una lista de los puertos seriales establecidos, propositos de debugueo:
  println(Serial.list());

  // Ahora que ya tienes una lista de los puertos seriales establecidos en tu Mac
  // siempre tu FTDI chip-adaptor, los podras ver en la terminal con la función Serial.list()[0].
  // Maquinas con Windows, Generalmente el puerto serial es establecido como COM1.
  // busca y abre cualquier puerto en tu programa, elegiendolo cambiando el número cotenido dentro del array.
  String portName = Serial.list()[2];        //  Elejimos de la lista el puerto del Arduino
  myPort = new Serial(this, portName, 9600); //  inicializamos la variable para comunicarnos con el puerto serial
}

void draw() {
  background(bgcolor);
  fill(fgcolor);
  // Draw the shape
  ellipse(xpos, ypos, 20, 20);
}


void serialEvent(Serial myPort) {
  // Lee un byte desde el puerto serial:
  int inByte = myPort.read();
  // si este primer byte es recibido, y eso es un caracter A,
  // esto limpia el buffer del serial y ahora es recibido
  // ahora hemos establecido contacto con el microcontrolador. 
  // del lo contrario, añadimos el byte entrante al array:
  if (firstContact == false) {
    if (inByte == 'A') { 
      myPort.clear();          // se limpia el buffer del puerto serial
      firstContact = true;     // ya hemos establecido contacto con el microcontrolador
      myPort.write('A');       // preguntamos por ese caracter
    } 
  } 
  else {
    //Añadimos el ultimo byte del puerto serial al array
    serialInArray[serialCount] = inByte;
    serialCount++;

    // si tenemos 3 bytes:
    if (serialCount > 2 ) {
      xpos = serialInArray[0];    //  Leemos los datos que se envian desde el serial y los asignamos a la posX del circulo
      ypos = serialInArray[1];    //  Leemos los datos que se envian desde el serial y los asignamos a la posY del circulo
      fgcolor = serialInArray[2]; //  Cabiamos el color de la forma cuando presionamos un boton    

      // Imprimimos los valores (para propositos de debugeo solamente):
      println(xpos + "\t" + ypos + "\t" + fgcolor);

      // Enviamos una A mayuscula para que le preguntemos al serial si hay nuevas lecturas de los sensores:
      myPort.write('A');
      // Reset serialCount:
      serialCount = 0;
    }
  }
}


