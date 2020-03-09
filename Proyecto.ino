int ESTADO = 0; // 0 MONEDAS | 1 TIPO CONTROL | 2 MANUAL | 3 DIGITAL

int SENSOR_LDR[3] = {A0, A1, A2};
int CONT_1 = 0;
int CONT_50 = 0;
int CONT_25 = 0;
int BOLETO = 0;

void setup() {
  Serial.begin(9600);  
}

void loop() {
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

void contarMonedas() {
  int valor_1 = analogRead(SENSOR_LDR[0]);
  int valor_50 = analogRead(SENSOR_LDR[1]);
  int valor_25 = analogRead(SENSOR_LDR[2]);
  
  if (valor_1 > 500) {
    CONT_1++;
    delay(500);
  } else if (valor_50 > 500) {
    CONT_50++;
    delay(500);
  } else if (valor_25 > 500) {
    CONT_25++;
    delay(500);
  }
  Serial.println("++++++++");
  Serial.println(CONT_1);
  Serial.println(CONT_50);
  Serial.println(CONT_25);
  Serial.println("++++++++");
}

void tipoControl() {
  
}

void controlManual() {
  
}

void conrolDigital() {
  
}
