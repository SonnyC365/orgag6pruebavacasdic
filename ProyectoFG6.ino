#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <EEPROM.h>

// Pines de Salida
const int PIN_SALA = 3;
const int PIN_COMEDOR = 5;
const int PIN_COCINA = 6;
const int PIN_BANO = 9;
const int PIN_HAB = 10;
const int PIN_FAN = 11;  // Pin de PWM (potenciometro)
const int pinIN1=12;
const int pinIN2=13;
const int PIN_SERVO = 4;

// Objetos
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo puertaServo;

int velocidadFan = 0;
bool puertaAbierta = false;
String nombreEscena = "Manual";
bool escenaActiva = false;

String escenasGuardadas[10];
int numEscenas = 0;

void setup() {
  // Inicializar el puerto serial
  Serial.begin(9600);
// Configurar los pines creados anteriormente de Salida
  pinMode(PIN_SALA, OUTPUT);  
  pinMode(PIN_COMEDOR, OUTPUT);  
  pinMode(PIN_COCINA, OUTPUT);  
  pinMode(PIN_BANO, OUTPUT);  
  pinMode(PIN_HAB, OUTPUT);
  pinMode(PIN_FAN, OUTPUT);  

  // Inicializar el periferico de Servo y LCD
  puertaServo.attach(PIN_SERVO);
  lcd.init();
  lcd.backlight();

  actualizarLCD();
// Mensajes a mostrar
  Serial.println("*** CASA AUTOMATIZADA DIC 2025 ***");
  Serial.println("\n");
}

void loop() {

}

void setVentilador (int pwm){
  digitalWrite(pinIN1,HIGH);
  digitalWrite(pinIN2,LOW);
  analogWrite(PIN_FAN, pwm);
  velocidadFan = pwm;
  Serial.print("FAN: "); Serial.println(pwm);
}

void moverPuerta(bool abrir){
  puertaAbierta = abrir;
  puertaServo.write(abrir ? 90:0);
  Serial.print("PUERTA: "); Serial.println(abrir ? "ABIERTA" : "CERRADA");
}

void togglePuerta(){ moverPuerta(!puertaAbierta);
}

void allOn(){
  digitalWrite(PIN_SALA, HIGH);
  digitalWrite(PIN_COMEDOR, HIGH);
  digitalWrite(PIN_COCINA, HIGH);
  digitalWrite(PIN_BANO, HIGH);
  digitalWrite(PIN_HAB, HIGH);
}

void allOff(){
  digitalWrite(PIN_SALA, LOW);
  digitalWrite(PIN_COMEDOR, LOW);
  digitalWrite(PIN_COCINA, LOW);
  digitalWrite(PIN_BANO, LOW);
  digitalWrite(PIN_HAB, LOW);
}

void actualizarLCD(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Escena: ");
  lcd.print(nombreEscena);

  lcd.setCursor(0,1);
  if (velocidadFan == 0) lcd.print("FAN:OFF");
  else if (velocidadFan < 100) lcd.print("FAN:LOW");
  else lcd.print("FAN:HI");

  lcd.print(puertaAbierta ? "P:ABR" : "P:CER");
}

void imprimirEstado(){
  Serial.println("*** ESTADO ACTUAL DEL SISTEMA ***");
  Serial.print("SALA : "); Serial.println(digitalRead(PIN_SALA) ? "ON" : "OFF");
  Serial.print("COMEDOR : ");
  Serial.println(digitalRead(PIN_COMEDOR) ? "ON" : "OFF");
  Serial.print("COCINA : "); Serial.println(digitalRead(PIN_COCINA) ? "ON" : "OFF");
  Serial.print("BANO : ");
  Serial.println(digitalRead(PIN_BANO) ? "ON" : "OFF");
  Serial.print("HAB : "); Serial.println(digitalRead(PIN_HAB) ? "ON" : "OFF");
  Serial.print("FAN : "); Serial.println(velocidadFan);
  Serial.print("PUERTA : ");
  Serial.println(puertaAbierta ? "ON" : "OFF");
  Serial.print("ESCENA : "); Serial.println(nombreEscena);
}

void listarEscenas(){
  Serial.println("*** Escenas Guardadas ***");
  for(int i = 0; i < numEscenas; i++){
    Serial.print(" >."); Serial.println(escenasGuardadas[i]);
  }
}