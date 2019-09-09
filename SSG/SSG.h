#ifndef SSG_H
#define SSG_H

#include "Arduino.h"

// Include notes frequencies
#include "music.h"

// Define IO pinout
#define DA0 5
#define DA1 6
#define DA2 7
#define DA3 8
#define DA4 9
#define DA5 10
#define DA6 11
#define DA7 12
#define BC1 4
#define BC2 3
#define BDIR 2

// Delay in microseconds we allow the chip to react after mode changes or register access
#define us_delay 100

// We use a 4Mhz crystal oscillator and set /SEL to low, the input clock is divided by 2 and equal 2Mhz
#define fMaster 2000000

// channels for SSG::set_chan_frequency
#define chanA 1
#define chanB 2
#define chanC 4

class SSG
{
  public:
    SSG();

    // Music
    void set_chan_frequency(word note, word octave, char chan = 7);
    void set_chan_frequency_null(char chan = 7);
    void set_chanA_frequency(int note, int octave);
    void set_chanB_frequency(int note, int octave);
    void set_chanC_frequency(int note, int octave);

    // Level control

    // Noise
    void set_noise_frequency(char NP);

    // Mixer
    void set_chan_mixer(bool music, bool noise, char chan = 7);
    void set_chan_mixer_mute(char chan = 7);
    void set_chanA_mixer(bool music, bool noise);
    void set_chanB_mixer(bool music, bool noise);
    void set_chanC_mixer(bool music, bool noise);
    
    // Envelope
    
  private:
    // convert note and octave into a word
    word note_to_YM(word note, word octave);

    // Modes
    /* We only use 3 possible state of BC1, BC2, BDIR combination.
     *
     *          | BC1 | BC2 | BDIR |
     * Inactive |  1  |  0  |   1  |
     * Write    |  0  |  1  |   1  |
     * Address  |  1  |  1  |   1  |
     *
     * We could remove the digitalWrite(BDIR, HIGH),
     * but we still keep it if we want to use the read functions.
      */
    void set_mode_inactive();
    void set_mode_write();
    void set_mode_address();

    // Write
    void set_address(char address);
    void set_data(char data);
    void write_data(char address, char data);

    // Mixer current status
    char mixer_status;
};

#endif
