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

  // tests all notes
  for(i = 0; i < 10; ++i)
  {
    
    ssg.set_chanA_frequency(C, i);
    delay(500);
    ssg.set_chanA_frequency(D, i);
    delay(500);
    ssg.set_chanA_frequency(E, i);
    delay(500);
    ssg.set_chanA_frequency(F, i);
    delay(500);
    ssg.set_chanA_frequency(G, i);
    delay(500);
    ssg.set_chanA_frequency(A, i);
    delay(500);
    ssg.set_chanA_frequency(B, i);
    delay(500);
    
    /*
    Serial.println(pgm_read_float(&note_frequency[C][i]));
    Serial.println(pgm_read_float(&note_frequency[D][i]));
    Serial.println(pgm_read_float(&note_frequency[E][i]));
    Serial.println(pgm_read_float(&note_frequency[F][i]));
    Serial.println(pgm_read_float(&note_frequency[G][i]));
    Serial.println(pgm_read_float(&note_frequency[A][i]));
    Serial.println(pgm_read_float(&note_frequency[B][i]));
    */
  }

  ssg.set_chanA_frequency(A, 4);
  delay(1000);
  ssg.set_chanB_frequency(A, 5);
  delay(1000);
  ssg.set_chanC_frequency(A, 6);
  delay(1000);
  ssg.set_chan_frequency_null(chanA | chanB | chanC);
  delay(1000);
}
