/*
modificado de   ejemplo  evento Serial
 
 */
String inputString = "";         // una cadena para contener los datos entrantes
boolean stringComplete = false;  // si la cadena esta completa
int port = 2;
void setup() {
  while(port <= 13){
    pinMode(port, OUTPUT);
    port++;
  }  
  Serial.begin(9600);
  // reserva 200 bytes para la cadena de entrada:
  inputString.reserve(200);
}

void loop() {

  if (stringComplete) {
    if(inputString[0] == 'L' && inputString[1] == 'E' && inputString[2] == 'D'){
      int port = (inputString[3] -48)*10 +(inputString[4] -48);
      if(port > 13 || port < 2)inputString = "";
      bool event_value = false;
      if(inputString[5] == 'O'){
      if(inputString[6] == 'N'){
        digitalWrite(port, HIGH);
      }
      if(inputString[6] =='F' && inputString[7] == 'F'){
        digitalWrite(port, LOW);
      }
      }
    }
    if(inputString[0] == 'D' &&inputString[1] == 'A' && inputString[2] == 'T'){
      if((inputString[3] -48) >0 &&(inputString[3] -48) <6)
      {
        Serial.println((5.0 * analogRead(inputString[3] -48) * 100.0) / 1024);      
      }
    }

    // limpia la cadena
    inputString = "";
    stringComplete = false;
  }
}

/*
SerialEvent ocurre cuando una nueva información viene en el RX(receptor) de serial. Esta rutina se ejecuta entre cada loop() , por lo que el retraso dentro del loop puede retrasar la respuesta. Múltiples bytes de datos pueden estar disponibles.
  */
void serialEvent() {
  while (Serial.available()) {
    // obtiene un nuevo byte:
    char inChar = (char)Serial.read();
    // agrega esto hacia inputString:
    // si el caracter entrante es una nueva linea, se configura una bandera
    // asi que el bucle principal puede hacer algo acerca de esto:
    if (inChar == '%') {
      stringComplete = true;
    }else{
      inputString += inChar;
   }
  }
}
