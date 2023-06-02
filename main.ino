#include <Arduino.h>
#include <HCSR04.h>

#define motor 9
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
    // conta pulso
    pinMode(sensVazaoPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(sensVazaoPin), incPULSE, RISING);
}

void loop() {
    delay(5);

    while ((hc.dist() < 10) && (!full)) {
        Serial.println(" ");
        digitalWrite(motor, HIGH);
        Serial.println("Liga");
        Serial.println(" ");
        Serial.println(full);
    }
    digitalWrite(motor, LOW);
}