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

  // Para manejar el ingreso comandos
  if (Serial.available() > 0){
    comando = Serial.readStringUntil('\n');
    comando.trim();
    comando.toUpperCase();
    interpretarComando(comando);
  }
 
  // Para manejar escenas activas , ejecutarlas.
  if (escenaActiva){
    //ejecutarEscenaNonBlocking();
  }

}

void ejecutarEscenaNonBlocking(){

}

void interpretarComando(String cmd){
  // Flujo de control del comando
  
  // Control de comandos de luces
  if (cmd == "L1" || cmd == "L1ON") { digitalWrite(PIN_SALA,HIGH);
  Serial.println("SALA:ON"); }
  else if (cmd == "L1OFF") { digitalWrite(PIN_SALA,LOW); Serial.println("SALA:OFF");
  }
  else if (cmd == "L2" || cmd == "L2ON") { digitalWrite(PIN_COMEDOR,HIGH); Serial.println("COMEDOR:ON");
  }
  else if (cmd == "L2OFF") { digitalWrite(PIN_COMEDOR,LOW); Serial.println("COMEDOR:OFF");
  }
  else if (cmd == "L3" || cmd == "L3ON") { digitalWrite(PIN_COCINA,HIGH); Serial.println("COCINA:ON");
  }
  else if (cmd == "L3OFF") { digitalWrite(PIN_COCINA,LOW); Serial.println("COCINA:OFF");
  }
  else if (cmd == "L4" || cmd == "L4ON") { digitalWrite(PIN_BANO,HIGH); Serial.println("BANO:ON");
  }
  else if (cmd == "L4OFF") { digitalWrite(PIN_BANO,LOW); Serial.println("BANO:OFF");
  }
  else if (cmd == "L5" || cmd == "L5ON") { digitalWrite(PIN_HAB,HIGH); Serial.println("HAB:ON");
  }
  else if (cmd == "L5OFF") { digitalWrite(PIN_HAB,LOW); Serial.println("HAB:OFF"); }
  else if (cmd == "ALLON") { allOn(); Serial.println("TODAS:ON");
  }
  else if (cmd == "ALLOFF") { allOff(); Serial.println("TODAS:OFF");
  }

  // Control de comandos de motor
  else if (cmd == "FAN0") { setVentilador(0);
  }
  else if (cmd == "FAN1") { setVentilador(20); }
  else if (cmd == "FAN2") { setVentilador(40);
  }
  else if (cmd == "FAN3") { setVentilador(60); }

  // Control de la puerta
  else if (cmd == "DOOR") { togglePuerta();
  }
  else if (cmd == "DOOROPEN") { moverPuerta(true); }
  else if (cmd == "DOORCLOSE") { moverPuerta(false);
  }

  // Control de Escenas
  else if (cmd == "FIESTA") { cargarEscenaPredefinida(1);
  }
  else if (cmd == "RELAX") { cargarEscenaPredefinida(2); }
  else if (cmd == "NIGHT") { cargarEscenaPredefinida(3);
  }

  // Control de Cargo de Escenas
  else if (cmd == "LOAD_SCENA") {
    modoCarga = true;
    totalPasos = 0;
    Serial.println("* MODO CARGA ACTIVADO *");
    Serial.println("Agrega tus lineas del .org, debe terminar con END_LOAD NOMBRE");
  }
  else if(modoCarga){
    procesarLineaEscena(cmd);
  }
  else if(cmd.startsWith("END_LOAD")){
    nombreNuevaEscena=cmd.substring(9);
    Serial.println("nombreNuevaEscena:"+nombreNuevaEscena);
    guardarEscenaEnEEPROM();
  }
  // Control del Sistema
  else if(cmd == "STOP"){
    escenaActiva = false;
    nombreEscena = "Manual";
    Serial.println("ESCENA DETENIDA");
  }
  else if(cmd == "STATUS"){ imprimirEstado(); }
  else if(cmd == "RESET"){ resetSistema();
  }
  else if(cmd == "LIST_SCENES"){ listarEscenas(); }
  else {Serial.println("--> Comando Desconocido 😢");}

  actualizarLCD();
  guardarEstadoActual();
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

//# Escena: FIESTA
//# Descripcion: Luces parpadeando rapidamente en patron alternado
//# Duracion total aproximada: 20 segundos
//
//SALA:ON:500:20  // pos1= SALA  pos2 =ON pos3= 500 pos3+1= 20
//COMEDOR:OFF:500:20
//COCINA:ON:300:30
//BAÑO:OFF:300:30
//HABITACION:ON:200:50

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


HOLLLLLASD


ASFPOKOFKSOAF
SKSA
FOKSA
FOKASF
OKAS
fKA
SFSAFAFASD