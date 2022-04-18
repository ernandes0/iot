#include <Arduino.h>
#include <Ultrasonic.h>
#include <CircularBuffer.h>

#define Ptrig   2 //atribuindo o pino 2 ao trigger do sensor
#define Pecho   3 //atribuindo o pino 3 ao echo do sensor
#define Pled    LED_BUILTIN //atribuindo o pino ao led builtint
CircularBuffer<int, 60> buffer;

int dist;
Ultrasonic ultrasonic(Ptrig, Pecho);

void teclado(){
  char tecla;
  tecla = Serial.read();
  if (tecla == 'L'){
    Serial.println("As ultimas medições foram:");
    int last;
    for (int i = buffer.size(); i > (buffer.size() - 10); i--) {
			last = buffer[i];
      Serial.println(last);
    }
  }
}

void setup(){
  pinMode(Pled, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  dist = ultrasonic.read();
  buffer.push(dist);

  if (dist != 0){
    digitalWrite(Pled, HIGH);
    delay(200);
    digitalWrite(Pled, LOW);
  }
  teclado();
  Serial.println("Aperte a tecla 'L' para ter acesso as ultimas medições");
  delay(10000);
}
