//Para hacer esta prueba de funcionamiento con el ESP32, 
//haremos parpadear el LED interno de la tarjeta que es el pin 2
//Al cargar es necesario estar presionando el boton derecho (boot) del ESP para que haga conexión

int LED_BUILTIN = 2;

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  
  // put your main code here, to run repeatedly:

}
