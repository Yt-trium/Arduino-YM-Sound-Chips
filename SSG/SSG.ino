#include "SSG.h"

SSG ssg;

void setup() {
unsigned int i;
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  unsigned int i, j;

  ssg.set_chanA_frequency(A, 4);
  delay(1000);
  ssg.set_chanB_frequency(A, 5);
  delay(1000);
  ssg.set_chanC_frequency(A, 6);
  delay(1000);
  ssg.set_chan_frequency_null(chanA | chanB | chanC);
  delay(1000);
}
