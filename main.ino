#include <Arduino.h>
#include <HCSR04.h>

#define motor 9
#define ledVermelho 3
#define ledVerde 4
// Define os pinos do sensor ultrassônico
#define triggerPin 5
#define echoPin 7
#define sensVazaoPin 2

double fluxo;
bool full = false;

HCSR04 hc(triggerPin, echoPin);

void incPULSE() {
    fluxo += 1.0 / 5880.00;

    if (fluxo > 0.5) {
        fluxo = 0;
        full = true;
    } else {
        full = false;
    }
}

void setup() {
    Serial.begin(9600);  // Inicializa a comunicação serial
    pinMode(motor, OUTPUT);
    pinMode(sensVazaoPin, INPUT);
    pinMode(ledVermelho, OUTPUT);
    pinMode(ledVerde, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(sensVazaoPin), incPULSE, RISING);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);
}

void loop() {
    delay(5);
    while ((hc.dist() < 10) && (!full)) {
        digitalWrite(motor, HIGH);
    }
    while (hc.dist() < 10) {
        digitalWrite(ledVermelho, HIGH);
        digitalWrite(ledVerde, LOW);
    }
    digitalWrite(ledVermelho,LOW);
    digitalWrite(ledVerde,HIGH);
    digitalWrite(motor, LOW);
}