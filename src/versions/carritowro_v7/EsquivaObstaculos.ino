//Inclusión de librerias
#include <Servo.h>
#include <L298N.h>
#include <SR04.h>
#include <math.h>
//Declaración de servos y ultrasonidos con las librerias
SR04 sr04adel = SR04(echo, triger);
SR04 sr04izq = SR04(echo2, triger2);
SR04 sr04der = SR04(echo3, triger3);
L298N motor(EN, IN4, IN3);
Servo servo;
//Declaración de variables
#define IN4 9
#define IN3 8
#define echo 47
#define triger 46
#define echo2 48
#define triger2 49
#define echo3 51
#define triger3 50
#define EN 11
String entradaSerial = "";
int rojo1,rojo2,verde1,verde2;
int cruzconorojo,cruzconorojo2,cruzconoverde,cruzconoverde2;
int crucecono = 0;
int intervalocono = 200;
int esquina=0;
int esq=0;
int motors=1;
int lineas=0;
int pared=0;
int paredizq=0;
int paredder=0;
int esquinader=0;
int izq=0;
int der=0;
int si=0;
int intervalo=1800;
int atrasc=0;
const int intervaloder=1900;
const int intervalopared=250;
unsigned long antespared=0;
unsigned long antesparedder=0;
unsigned long tiempoantesdelcont=0;
unsigned long valorantesconor = 0;
unsigned long valorantesconov = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(33);
  //Configuración de los pines de ultrasonido y del driver L298N
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(triger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(triger2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(triger3, OUTPUT);
  pinMode(echo3, INPUT);
  //Definición de la velocidad del motor del carro
  motor.setSpeed(180);
  //Función para detener el motor del carro
  motor.stop();
  //Servo en posición inicial
  servo.write(90);
}

void loop() {
  //Inicio del ciclo 
//Indicador de esquinas (para saber cuantas vueltas a dado el carro)
 if(lineas<12){
  unsigned long cont = millis();
  float distanciaade = sr04adel.Distance();
  float distanciaizq = sr04izq.Distance();
  float distanciader = sr04der.Distance();
  if(motors==1){
    carrorect();
  }
  //Condición de cruzar esquinas (en sentido antihorario)
  if((distanciaizq>100&&distanciaizq<300&&der==0&&si==0)||esquina==1){
    if((cont-tiempoantesdelcont>intervalo)||esq==0){
      tiempoantesdelcont=cont;
      if(esq==0){
        esquina=1;
        si=1;
        esq=1;
        motor.stop();
        motor.backward();
        intervalo=400;
        motors=0;
        izq=1;
      } 
      if(esq==1){
        motor.stop();
        carroesqizq();
        esq=2;
        intervalo=1800;
      } 
      else if(esq==2&&(rojo1!=0||rojo2!=0||verde1!=0||verde2!=0)){
        servo.write(90);
        motor.stop();
        esq=3;
        atrasc=1;
        motor.backward();
        intervalo=800;
      }
      else if(esq==3&&atrasc==1){
        esq=4;
        motor.stop();
        motor.forward();
        intervalo=400;

      }
      else if(esq==4&&atrasc==1&&verde1!=0){
        servo.write(50);
        delay(200);
        servo.write(90);
        delay(1200);
        servo.write(130);
        delay(200);
        servo.write(90);
        esq=0;
        esquina=0;
        motors=0;
        lineas++;
        tiempoantesdelcont=0;
        intervalo=400;
        atrasc=0;
      }
      else if(esq==4&&atrasc==1&&rojo1!=0){
        servo.write(110);
        delay(200);
        servo.write(90);
        delay(1200);
        servo.write(70);
        delay(200);
        servo.write(90);
        esq=0;
        esquina=0;
        motors=0;
        lineas++;
        tiempoantesdelcont=0;
        intervalo=400;
        atrasc=0;
      }
      else if(esq==4&&atrasc==1&&rojo2!=0){
        servo.write(130);
        delay(200);
        servo.write(90);
        delay(1200);
        servo.write(50);
        delay(200);
        servo.write(90);
        esq=0;
        esquina=0;
        motors=0;
        lineas++;
        tiempoantesdelcont=0;
        intervalo=400;
        atrasc=0;
      }
      else if(esq==4&&atrasc==1&&verde2!=0){
        servo.write(65);
        delay(200);
        servo.write(90);
        delay(1200);
        servo.write(105);
        delay(200);
        servo.write(90);
        esq=0;
        esquina=0;
        motors=0;
        lineas++;
        tiempoantesdelcont=0;
        intervalo=400;
        atrasc=0;
      }
      else if(esq==2&&(rojo1==0&&rojo2==0&&verde1==0&&verde2==0)){
        esq=3;
        carrorect();
        intervalo=500;
      }
        else if(esq==3&&(cruzconorojo==0&&cruzconorojo2==0&&cruzconoverde==0&&cruzconoverde2==0)){
        esq=0;
        carrorect();
        lineas++;
        esquina=0;
        tiempoantesdelcont=0;
        motors=0;
        intervalo=1800;
      }
    }
  }
    //Condición de cruzar esquinas (en sentido horario)
    if((distanciader>100&&distanciader<300&&izq==0&&si==0)||esquinader==1){
    if((cont-tiempoantesdelcont>intervaloder)||esq==0){
      tiempoantesdelcont=cont;
      if(esq==0){
        esquinader=1;
        si=1;
        esq=1;
        carroesqder();
        motors=0;
        der=1;
      }
      else{
        esq=0;
        carrorect();
        esquinader=0;
        motors=1;
        lineas++;
        tiempoantesdelcont=0;
      }
    }
  }
//Condiciones para centrar el carro
  if((distanciaizq<40&&esquina==0&&esquinader==0&&paredder==0&&cruzconorojo==0&&cruzconorojo2==0&&cruzconoverde==0&&cruzconoverde2==0)||paredizq==1){
    si=0;
    if(cont-antespared>intervalopared){
      antespared=cont;
      if(pared==0&&esquina==0&&esquinader==0&&cruzconorojo==0&&cruzconorojo2==0&&cruzconoverde==0&&cruzconoverde2==0){
        pared=1;
        carroizq();
        paredizq=1;
      }
      
      else if(pared==1&&esquina==0&&esquinader==0&&cruzconorojo==0&&cruzconorojo2==0&&cruzconoverde==0&&cruzconoverde2==0){
        pared=0;
        carrorect();
        paredizq=0;
        antespared=0;
      }
    }
  }
  if((distanciader<40&&esquina==0&&esquinader==0&&paredizq==0&&cruzconorojo==0&&cruzconorojo2==0&&cruzconoverde==0&&cruzconoverde2==0)||paredder==1){
    if(cont-antesparedder>intervalopared){
      antesparedder=cont;
      if(pared==0&&esquina==0&&esquinader==0&&cruzconorojo==0&&cruzconorojo2==0&&cruzconoverde==0&&cruzconoverde2==0){
        pared=1;
        //si=0;
        carroder();
        paredder=1;
      }
      else if(pared==1&&esquina==0&&esquinader==0&&cruzconorojo==0&&cruzconorojo2==0&&cruzconoverde==0&&cruzconoverde2==0){
        pared=0;
        carrorect();
        paredder=0;
        antesparedder=0;
      }
    }
  }
  //Condiciones para detección de obstaculos
    if ((rojo1 != 0&&esquina==0&&esquinader==0) || cruzconorojo == 1) {
    if ((cont - valorantesconor > intervalocono)||crucecono==0) {
      valorantesconor = cont;
      if (crucecono == 0) {
        crucecono = 1;
        servo.write(105);
        cruzconorojo = 1;
        motors=0;
      }  else if (crucecono == 1) {
        crucecono = 0;
        servo.write(90);
        carrorect();
        rojo1 = 0;
        cruzconorojo = 0;
        motors=1;
      }
    }
  }
  if ((rojo2 != 0&&esquina==0&&esquinader==0) || cruzconorojo2 == 1) {
    if ((cont - valorantesconor > intervalocono)||crucecono==0) {
      valorantesconor = cont;
      if (crucecono == 0) {
        crucecono = 1;
        servo.write(105);
        cruzconorojo2 = 1;
        motors=0;
      } else if (crucecono == 1) {
        servo.write(75);
        crucecono = 2;
      } else if (crucecono == 2) {
        crucecono = 0;
        servo.write(90);
        carrorect();
        rojo2 = 0;
        cruzconorojo2 = 0;
        motors=1;
      }
    }
  }

  if ((verde1!=0&&esquina==0&&esquinader==0)||cruzconoverde==1) {

    if ((cont - valorantesconov > intervalocono)||crucecono==0) {
      valorantesconov = cont;
      if (crucecono == 0&&esquina==0) {
        crucecono++;
        cruzconoverde = 1;
        servo.write(50);
        motors=0;
      } else if (crucecono == 1&&esquina==0) {
        crucecono++;
        servo.write(105);
      } else if (crucecono == 2&&esquina==0) {
        crucecono = 0;
        servo.write(90);
        carrorect();
        cruzconoverde = 0;
        verde1 = 0;
        motors=1;
      }
    }
  }

  if ((verde2!=0&&esquina==0&&esquinader==0)|| cruzconoverde2 == 1) {

    if ((cont - valorantesconov > intervalocono)||crucecono==0) {
      valorantesconov = cont;
      if (crucecono == 0&&esquina==0) {
        crucecono = 1;
        servo.write(70);
        cruzconoverde2 = 1;
        motors=0;
      }else if (crucecono == 1&&esquina==0) {
        crucecono = 0;
        servo.write(90);
        carrorect();
        cruzconoverde2 = 0;
        verde2 = 0;
        motors=1;
      }
    }
  }
}
 else{
  stopcar();
 }
}
//Funciones fundamentales del carro
void carroalante() {
  motor.stop();
  motor.forward();
}
void carroatras() {
  motor.stop();
  motor.backward();
}
void carromedder() {
  motor.stop();
  servo.write(105);
  motor.forward();
}
void carromedizq() {
  motor.stop();
  servo.write(85);
  motor.forward();
}
void carroder() {
  motor.stop();
  servo.write(70);
  motor.forward();
}
void carroizq() {
  motor.stop();
  servo.write(110);
  motor.forward();
}
void carroesqder() {
  motor.stop();
  servo.write(110);
  motor.forward();
}
void carroesqizq() {
  motor.stop();
  servo.write(65);
  motor.forward();
}
void carrorect() {
  motor.stop();
  servo.write(90);
  motor.forward();
}
void stopcar() {
  motor.forward();
  servo.write(90);
  delay(1000);
  motor.stop();
  delay(1000000);
}
//Función de recepción de la información del Raspberry pi
void serialEvent() {
  while (Serial.available()) {
    // Obtener bytes de entrada
    char inChar = (char)Serial.read();
    // Agregar al String de entrada
    entradaSerial += inChar;
    // Para saber si el string está completo, se detendrá al recibir
    // el caracter de retorno de línea ENTER \n
    if (inChar == '\n') {
      if (entradaSerial == "rojo1\n") {
        rojo1 = 1;
        inChar = "";
        entradaSerial = "";
      } else if (entradaSerial == "verde1\n") {
        verde1 = 1;
        inChar = "";
        entradaSerial = "";
      }
      if (entradaSerial == "rojo2\n") {
        rojo2 = 1;
        inChar = "";
        entradaSerial = "";
      } else if (entradaSerial == "verde2\n") {
        verde2 = 1;
        inChar = "";
        entradaSerial = "";
      }
    }
  }
}