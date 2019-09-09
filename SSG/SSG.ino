#include "SSG.h"

SSG ssg;

/* Same as delay(d) (or delay(d-1) if d%2 == 1
 * Make the builtin led blink on half the time of the delay
 */
void delay_blink(unsigned long d)
{
  unsigned long d_2 = d / 2;
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(d_2);
  digitalWrite(LED_BUILTIN, LOW);
  delay(d_2);
}

void setup() {
unsigned int i;
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  unsigned int i;
  
  // 1 - Test Music

  ssg.set_chan_level(0b1111, chanA | chanB | chanC);
  ssg.set_chan_mixer_mute(chanA | chanB | chanC);
  ssg.set_chan_mixer(true, false, chanA);
  
  for(i = 1; i < 6; ++i)
  {
    ssg.set_chanA_frequency(C, i);
    delay_blink(200);
    ssg.set_chanA_frequency(D, i);
    delay_blink(200);
    ssg.set_chanA_frequency(E, i);
    delay_blink(200);
    ssg.set_chanA_frequency(F, i);
    delay_blink(200);
    ssg.set_chanA_frequency(G, i);
    delay_blink(200);
    ssg.set_chanA_frequency(A, i);
    delay_blink(200);
    ssg.set_chanA_frequency(B, i);
    delay_blink(200);
  }
  ssg.set_chan_mixer(true, false, chanA | chanB | chanC);

  ssg.set_chanA_frequency(C, 3);
  ssg.set_chanB_frequency(E, 4);
  ssg.set_chanC_frequency(G, 5);
  delay_blink(1000);
  
  ssg.set_chan_frequency(C, 4, chanA | chanB | chanC);
  delay_blink(1000);
  
  ssg.set_chanA_frequency(C, 4);
  ssg.set_chanB_frequency(E, 5);
  ssg.set_chanC_frequency(G, 6);
  delay_blink(1000);


  // 2 - Noise and Mixer
  ssg.set_noise_frequency(0b01111);
  delay_blink(1000);
  
  ssg.set_chanA_mixer(false, true);
  delay_blink(1000);
  ssg.set_chanB_mixer(false, true);
  delay_blink(1000);
  ssg.set_chanC_mixer(false, true);
  delay_blink(1000);
  
  ssg.set_noise_frequency(0b11111);
  delay_blink(1000);

  ssg.set_chan_mixer(false, false, chanA | chanB | chanC);
  delay_blink(1000);
  ssg.set_chanA_mixer(true, false);
  ssg.set_chanB_mixer(false, false);
  ssg.set_chanC_mixer(false, false);
  delay_blink(1000);


  // 3 - Test Level
  
  ssg.set_chanA_level(0b1111);
  ssg.set_chanA_frequency(A, 4);
  delay_blink(1000);

  for(i = 0; i < 0b1111; ++i)
  {
    ssg.set_chanA_level(i);
    delay_blink(200);
  }
  
  
  // 4 - Test Envelope
  
  ssg.set_envelope_shape(true, false, true, false);
  ssg.set_chanA_use_envelope();

  ssg.set_envelope_frequency(32);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(64);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(128);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(256);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(512);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(1024);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(2048);
  delay_blink(1000);
  

  ssg.set_envelope_shape(false, false, false, false);
  ssg.set_chanA_use_envelope();

  ssg.set_envelope_frequency(512);
  delay_blink(1000);
  
  ssg.set_envelope_shape(false, true, false, false);
  ssg.set_chanA_use_envelope();

  ssg.set_envelope_frequency(512);
  delay_blink(1000);


  ssg.set_envelope_shape(true, false, false, false);
  ssg.set_chanA_use_envelope();

  ssg.set_envelope_frequency(32);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(64);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(128);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(256);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(512);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(1024);
  delay_blink(1000);
  
  ssg.set_envelope_frequency(2048);
  delay_blink(1000);
}
