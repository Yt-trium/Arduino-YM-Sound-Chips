#include "SSG.h"

SSG::SSG()
{
  pinMode(DA0, OUTPUT);
  pinMode(DA1, OUTPUT);
  pinMode(DA2, OUTPUT);
  pinMode(DA3, OUTPUT);
  pinMode(DA4, OUTPUT);
  pinMode(DA5, OUTPUT);
  pinMode(DA6, OUTPUT);
  pinMode(DA7, OUTPUT);
  
  pinMode(BC1, OUTPUT);
  pinMode(BC2, OUTPUT);
  pinMode(BDIR, OUTPUT);

  digitalWrite(DA0, LOW);
  digitalWrite(DA1, LOW);
  digitalWrite(DA2, LOW);
  digitalWrite(DA3, LOW);
  digitalWrite(DA4, LOW);
  digitalWrite(DA5, LOW);
  digitalWrite(DA6, LOW);
  digitalWrite(DA7, LOW);
  
  digitalWrite(BC1, LOW);
  digitalWrite(BC2, LOW);
  digitalWrite(BDIR, LOW);

  unsigned int i;
  
  for(i=0; i<16; i++) {
    write_data(i, 0);
  }

  // Default settings
  mixer_status = 0b11111000;

  write_data(7, mixer_status);

  write_data(8, 0x0f);
  write_data(9, 0x0f);
  write_data(0xA, 0x0f);
}

word SSG::note_to_YM(word note, word octave)
{
  return round(fMaster / (16*pgm_read_float(&note_frequency[note][octave])));
}

void SSG::set_mode_inactive()
{
  digitalWrite(BC1, HIGH);
  digitalWrite(BC2, LOW);
  digitalWrite(BDIR, HIGH);
}

void SSG::set_mode_write()
{
  digitalWrite(BC1, LOW);
  digitalWrite(BC2, HIGH);
  digitalWrite(BDIR, HIGH);
}

void SSG::set_mode_address()
{
  digitalWrite(BC1, HIGH);
  digitalWrite(BC2, HIGH);
  digitalWrite(BDIR, HIGH);
}

void SSG::set_address(char address)
{
  set_mode_address();
  delayMicroseconds(us_delay);

  // write address
  delayMicroseconds(us_delay); 
  digitalWrite(DA0, (address & 0b00000001));
  digitalWrite(DA1, (address & 0b00000010));
  digitalWrite(DA2, (address & 0b00000100));
  digitalWrite(DA3, (address & 0b00001000));
  digitalWrite(DA4, 0);
  digitalWrite(DA5, 0);
  digitalWrite(DA6, 0);
  digitalWrite(DA7, 0);
  delayMicroseconds(us_delay);

  set_mode_inactive();
  delayMicroseconds(100);
}

void SSG::set_data(char data)
{
  set_mode_write();
  delayMicroseconds(us_delay);
  
  // write data
  delayMicroseconds(100); 
  digitalWrite(DA0, (data & 0b00000001));
  digitalWrite(DA1, (data & 0b00000010));
  digitalWrite(DA2, (data & 0b00000100));
  digitalWrite(DA3, (data & 0b00001000));
  digitalWrite(DA4, (data & 0b00010000));
  digitalWrite(DA5, (data & 0b00100000));
  digitalWrite(DA6, (data & 0b01000000));
  digitalWrite(DA7, (data & 0b10000000));
  delayMicroseconds(us_delay);

  set_mode_inactive();
  delayMicroseconds(us_delay);
}

void SSG::write_data(char address, char data)
{
  set_address(address);
  set_data(data);
}

void SSG::set_chan_frequency(word note, word octave, char chan)
{
  word fT = note_to_YM(note, octave);
  
  if(chan & chanA)
  {
    write_data(0, (fT & 0xff));
    write_data(1, (fT >> 8));
  }
  if(chan & chanB)
  {
    write_data(2, (fT & 0xff));
    write_data(3, (fT >> 8));
  }
  if(chan & chanC)
  {
    write_data(4, (fT & 0xff));
    write_data(5, (fT >> 8));
  }
}

void SSG::set_chan_frequency_null(char chan)
{
  if(chan & chanA)
  {
    write_data(0, 0);
    write_data(1, 0);
  }
  if(chan & chanB)
  {
    write_data(2, 0);
    write_data(3, 0);
  }
  if(chan & chanC)
  {
    write_data(4, 0);
    write_data(5, 0);
  }
}

void SSG::set_chanA_frequency(int note, int octave)
{
  set_chan_frequency(note, octave, chanA);
}

void SSG::set_chanB_frequency(int note, int octave)
{
  set_chan_frequency(note, octave, chanB);
}

void SSG::set_chanC_frequency(int note, int octave)
{
  set_chan_frequency(note, octave, chanC);
}

void SSG::set_chan_level(char level, char chan = 7)
{
  if(level > 0b1111)
    level = 0x0f;
  else
    level &= ~(1 << 4);
     
  if(chan & chanA)
  {
    write_data(8, level);
  }
  if(chan & chanB)
  {
    write_data(9, level);
  }
  if(chan & chanC)
  {
    write_data(0xA, level);
  }
}

void SSG::set_chan_level_null(char chan = 7)
{
  set_chan_level(0, chan);
}

void SSG::set_chanA_level(char level)
{
  set_chan_level(level, chanA);
}

void SSG::set_chanB_level(char level)
{
  set_chan_level(level, chanB);
}

void SSG::set_chanC_level(char level)
{
  set_chan_level(level, chanC);
}

void SSG::set_noise_frequency(char NP)
{
  // Noise frequency (fN) is obtained with this formula :
  // fN = fMaster / (16*NP)
  // NP is a 5 bit value
  write_data(6, (NP & 0b00011111));
}

void SSG::set_chan_mixer(bool music, bool noise, char chan)
{
  if(chan & chanA)
  {
    if(music)
      mixer_status &= 0;
    else
      mixer_status |= 1;

    if(noise)
      mixer_status &= ~(1 << 3);
    else
      mixer_status |= 1 << 3;
  }
  if(chan & chanB)
  {
    if(music)
      mixer_status &= ~(1 << 1);
    else
      mixer_status |= 1 << 1;

    if(noise)
      mixer_status &= ~(1 << 4);
    else
      mixer_status |= 1 << 4;
  }
  if(chan & chanC)
  {
    if(music)
      mixer_status &= ~(1 << 2);
    else
      mixer_status |= 1 << 2;

    if(noise)
      mixer_status &= ~(1 << 5);
    else
      mixer_status |= 1 << 5;
  }
  
  write_data(7, mixer_status);
}

void SSG::set_chan_mixer_mute(char chan)
{
  set_chan_mixer(false, false, chan);
}

void SSG::set_chanA_mixer(bool music, bool noise)
{
  set_chan_mixer(music, noise, chanA);
}

void SSG::set_chanB_mixer(bool music, bool noise)
{
  set_chan_mixer(music, noise, chanB);
}

void SSG::set_chanC_mixer(bool music, bool noise)
{
  set_chan_mixer(music, noise, chanC);
}

void SSG::set_envelope_frequency(word EP)
{
  // Envelope repetition frequency (fE) is obtained with this formula :
  // fE = fMaster / (256*EP)
  // EP is a 16 bit value
  // The period of the actual frequency fE used for the envelope
  // generated is 1/32 of the envelope repetition period (1/fE)
  // Check the YM2149 datasheet page 7 for more informations.
  
  write_data(0xB, (EP & 0xff));
  write_data(0xC, (EP >> 8));
}

void SSG::set_envelope_shape(bool cont, bool att, bool alt, bool hold)
{
  // Check the YM2149 datasheet page 7 and 8 to view the 10 envelope possible shapes.
  word RD = 0;

  if(cont)
    RD |= 1 << 3;
  if(att)
    RD |= 1 << 2;
  if(alt)
    RD |= 1 << 1;
  if(hold)
    RD |= 1;

  write_data(0xD, RD);
}

void SSG::set_chan_use_envelope(char chan)
{
  if(chan & chanA)
  {
    write_data(8, 0x1f);
  }
  if(chan & chanB)
  {
    write_data(9, 0x1f);
  }
  if(chan & chanC)
  {
    write_data(0xA, 0x1f);
  }
}

void SSG::set_chanA_use_envelope()
{
  set_chan_use_envelope(chanA);
}

void SSG::set_chanB_use_envelope()
{
  set_chan_use_envelope(chanB);
}

void SSG::set_chanC_use_envelope()
{
  set_chan_use_envelope(chanC);
}
