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

// Variables Globales a Utilizar
String comando = "";
int velocidadFan = 0;
bool puertaAbierta = false;
String nombreEscena = "Manual";
bool escenaActiva = false;

// EEPROM - Estableceer direcciones de memoria
const int DIR_FAN = 0;
const int DIR_PUERTA = 1;
const int DIR_ESCENA_ACTIVA = 2; 
const int DIR_NUM_PASOS = 10;
const int DIR_PASOS_BASE = 20;

// Variables Para el Sistema de Escenas
bool modoCarga = false;
String nombreNuevaEscena = "";
struct PasoEscena{
  byte pin;
  bool estado;
  unsigned int duracion; // en milisegundos
  byte repeticiones;
};
PasoEscena pasosEscena[50];

// Arreglo Unidimensional o lo que llamamos normalmente vector 
int totalPasos = 0;
String escenasGuardadas[10];

// Nombres de escenas
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

// Recuperacion del estado de la EEPROM
  recuperarEstado();
  actualizarLCD();
// Mensajes a mostrar
  Serial.println("*** CASA AUTOMATIZADA DIC 2025 ***");
  Serial.println("\n");
}

void loop() {

}

void ejecutarEscenaNonBlocking(){

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

void procesarLineaEscena(String linea){ 
  linea.trim();
// Estructurar posiciones de la linea
  if (linea.startsWith("#") || linea.length() == 0) return;
  int pos1 = linea.indexOf(':');
  int pos2 = linea.indexOf(':', pos1 + 1);
  int pos3 = linea.indexOf(':', pos2 + 1);
// Obtener datos del Ambiente
  if(pos1 > 0 && pos2 > pos1 && pos3 > pos2 && totalPasos < 50 ){
    String amb = linea.substring(0, pos1);
    String est = linea.substring(pos1 + 1, pos2);
    int dur = linea.substring(pos2 + 1, pos3).toInt();
    int rep = linea.substring(pos3 + 1).toInt();
// Mapeo de Ambiente a pin
    byte pin = getPinFromAmbiente(amb);
    if(pin > 0){
      pasosEscena[totalPasos].pin = pin;
      pasosEscena[totalPasos].estado = (est == "ON");
      pasosEscena[totalPasos].duracion = dur;
      pasosEscena[totalPasos].repeticiones = rep;
      totalPasos++;
      Serial.print(" -> Linea Agregada");
    }
  }
}

byte getPinFromAmbiente(String amb){
  if(amb == "SALA") return PIN_SALA;
  if(amb == "COMEDOR") return PIN_COMEDOR;
  if(amb == "COCINA") return PIN_COCINA;
  if(amb == "BANO") return PIN_BANO;
  if(amb == "HABITACION" || amb == "HAB") return PIN_HAB;
  return 0;
}

void guardarEscenaEnEEPROM(){
  //Guardar el nombre de cada escena
  escenasGuardadas[numEscenas] = nombreNuevaEscena;
  numEscenas++;
// Guardar pasos (4 bytes por paso)
  EEPROM.update(DIR_NUM_PASOS, totalPasos);
  for(int i = 0; i < totalPasos; i++){
    int addr = DIR_PASOS_BASE + (i * 4);
    EEPROM.update(addr, pasosEscena[i].pin);
    EEPROM.update(addr + 1, pasosEscena[i].estado);
    EEPROM.update(addr + 2, lowByte(pasosEscena[i].duracion));
    EEPROM.update(addr + 3, highByte(pasosEscena[i].duracion));
    EEPROM.update(addr + 4, pasosEscena[i].repeticiones);
  }
}

void recuperarEstado(){
  velocidadFan = EEPROM.read(DIR_FAN);
  puertaAbierta = EEPROM.read(DIR_PUERTA);
  int escenaId = EEPROM.read(DIR_ESCENA_ACTIVA);
  setVentilador(velocidadFan);
  moverPuerta(puertaAbierta);
  Serial.println("Estado Recuperado desde la EEPROM");
}

void guardarEstadoActual(){
  EEPROM.update(DIR_FAN, velocidadFan);
  EEPROM.update(DIR_PUERTA, puertaAbierta);
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

void resetSistema(){
  allOff();
  setVentilador(0);
  moverPuerta(false);
  escenaActiva = false;
  nombreEscena = "Reset";
  Serial.println("*** Sistema Reiniciado ***");
}

void listarEscenas(){
  Serial.println("*** Escenas Guardadas ***");
  for(int i = 0; i < numEscenas; i++){
    Serial.print(" >."); Serial.println(escenasGuardadas[i]);
  }
}

void cargarEscenaPredefinida(int id){
  nombreEscena = (id == 1) ? "Fiesta" : (id==2) ? "Relax" : "Noche";
  escenaActiva = true;
  Serial.print("  - "); Serial.println(nombreEscena); 
}