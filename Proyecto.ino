int ESTADO = 0; // 0 MONEDAS | 1 TIPO CONTROL | 2 MANUAL | 3 DIGITAL

int SENSOR_LDR[3] = {A0, A1, A2}; // QUETZAL | VEINTICINCO | CINCUENTA
int BOTONES[7] = {30, 31, 32, 33, 34, 35}; // +X | -X | +Y | -Y | A ABAJO / ARRIBA | T TOMAR / SOLTAR

char valor = 0;
bool garra_cerrada = false;
bool garra_abajo = false;

void setup() {
  Serial.begin(9600);  
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
