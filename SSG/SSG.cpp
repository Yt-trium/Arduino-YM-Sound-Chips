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
  write_data(7, 0b11111000);
  
  write_data(8, 0x0f);
  write_data(9, 0x0f);
  write_data(10, 0x0f);
}

word SSG::note_to_YM(word note, word octave)
{
  return (fMaster / (16*pgm_read_float(&note_frequency[note][octave])));
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
  
  if(chan & 1)
  {
    write_data(0, (fT & 0xff));
    write_data(1, (fT >> 8));
  }
  if(chan & 2)
  {
    write_data(2, (fT & 0xff));
    write_data(3, (fT >> 8));
  }
  if(chan & 4)
  {
    write_data(4, (fT & 0xff));
    write_data(5, (fT >> 8));
  }
}

void SSG::set_chan_frequency_null(char chan = 1)
{
  word fT = 0;
  
  if(chan & 1)
  {
    write_data(0, (fT & 0xff));
    write_data(1, (fT >> 8));
  }
  if(chan & 2)
  {
    write_data(2, (fT & 0xff));
    write_data(3, (fT >> 8));
  }
  if(chan & 4)
  {
    write_data(4, (fT & 0xff));
    write_data(5, (fT >> 8));
  }
}

void SSG::set_chanA_frequency(int note, int octave)
{
  set_chan_frequency(note, octave, 1);
}

void SSG::set_chanB_frequency(int note, int octave)
{
  set_chan_frequency(note, octave, 2);
}

void SSG::set_chanC_frequency(int note, int octave)
{
  set_chan_frequency(note, octave, 4);
}
