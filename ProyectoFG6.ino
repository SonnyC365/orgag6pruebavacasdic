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

Servo puertaServo;

int velocidadFan = 0;
bool puertaAbierta = false;

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