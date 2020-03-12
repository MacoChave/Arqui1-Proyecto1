/* NOTAS MUSICALES */
#define NOTE_E3  165
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_G6  1568
#define NOTE_C7  2093
#define NOTE_E7  2637
#define NOTE_G7  3136

#define melodyPin 9

int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0
};

int tempo[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
};

int underworld_melody[] = {
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4, 
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4,NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};

int underworld_tempo[] = {
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18,18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

int ESTADO = 0; // 0 MONEDAS | 1 TIPO CONTROL | 2 MANUAL | 3 DIGITAL

int SENSOR_LDR[3] = {A0, A1, A2}; // QUETZAL | VEINTICINCO | CINCUENTA
int BOTONES[7] = {30, 31, 32, 33, 34, 35}; // +X | -X | +Y | -Y | A ABAJO / ARRIBA | T TOMAR / SOLTAR

char valor = 0;
bool garra_cerrada = false;
bool garra_abajo = false;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}

void loop() {
  valor = 0;
  
  /* 
   * OBTENER CARACTER DE BLUETOOTH 
   * VERIFICAR CARACTER DE ESTADO
   */
  /*
  if (Serial.available() > 0) {
    valor = Serial.read();
    verificarEstado(valor);
  }
  */
  
  switch (ESTADO) {
    case 0:
      contarMonedas();
      break;
    case 1: 
      tipoControl();
      break;
    case 2: 
      controlManual();
      break;
    case 3: 
      controlDigital();
      break;
  }
}

void verificarEstado(char valor) {
  switch (valor) {
    case 'B': // MONEDAS OK
      sing(2);
      ESTADO = 1;
      break;
  }
}

void contarMonedas() {
  //Serial.println(valor);
  int valor_1 = analogRead(SENSOR_LDR[0]);
  int valor_50 = analogRead(SENSOR_LDR[2]);
  int valor_25 = analogRead(SENSOR_LDR[1]);
/*
  Serial.println("*****");
  Serial.print(valor_1);
  Serial.print(" - ");
  Serial.print(valor_25);
  Serial.print(" - ");
  Serial.print(valor_50);
  Serial.println("*****");
*/
  /* MAYOR LUZ : MENOR VALOR */

  if (valor_1 > 550) {
    Serial.println("Quetzal");
    delay(500);
  } else if (valor_50 > 300) {
    Serial.println("Cincuenta");
    delay(500);
  } else if (valor_25 > 350) {
    Serial.println("Veinticinco");
    delay(500);
  }

}

void tipoControl() {
  if (valor == 'M') ESTADO = 2; // MODO MANUAL ON
  else if (valor == 'D') ESTADO = 3; // MODO DIGITAL ON
}

void controlManual() {
  /* 
   * ESCUCHAR BOTONES MECANICOS 
   */
}

void controlDigital() {
  /*
   * ESCUCHAR BOTONES DIGITALES
   */
   switch (valor) {
    case 'U': // +Y
      movUp();
      break;
    case 'D': // -Y
      movDown();
      break;
    case 'R': // +X
      movRight();
      break;
    case 'L': // -X
      movLeft();
      break;
    case 'A': // ABAJO | ARRIBA
      if (garra_abajo) garraSubir();
      else garraBajar();
      garra_abajo = !garra_abajo;
      break; 
    case 'T': // TOMAR | SOLTAR
      if (garra_cerrada) garraSoltar();
      else garraTomar();
      garra_cerrada = !garra_cerrada;
      break;
   }
}

void movUp() {
}

void movDown() {
}

void movRight() {
}

void movLeft() {
}

void garraBajar() {
}

void garraSubir() {
}

void garraTomar() {
  // GARRA VACÍA: PERDIO ESTADO = 0;
}

void garraSoltar() {
  // VERIFICAR COORDENADAS FINALES: PERDIO | GANÓ:  ESTADO = 0;
}

void sing(int s){      
   // iterate over the notes of the melody:
   song = s;
   if(song == 1){ // LOSE
     int size = sizeof(underworld_melody) / sizeof(int);
     Serial.println(size);
     for (int thisNote = 30; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/underworld_tempo[thisNote];

       buzz(melodyPin, underworld_melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(melodyPin, 0,noteDuration);

    }

   } else{ // COIN
     int size = sizeof(melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/tempo[thisNote];

       buzz(melodyPin, melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(melodyPin, 0,noteDuration);
    }
  }
}

void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait againf or the calculated delay value
  }
}
