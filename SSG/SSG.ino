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

// Delay in microseconds we allow the chip to react
#define us_delay 100

// Set notes frequency

// /SEL is low, the input clock is divided by 2
#define fMaster 2000000

const float note_frequency[12][11] = {
{27.50,55.00,110.00,220.00,440.00,880.00,1760.00,3520.00,7040.00,14080.00,28160.00},
{29.14,58.27,116.54,233.08,466.16,932.33,1864.66,3729.31,7458.62,14917.24,29834.48},
{30.87,61.74,123.47,246.94,493.88,987.77,1975.53,3951.07,7902.13,15804.26,31608.52},
{16.35,32.70,65.41,130.81,261.63,523.25,1046.50,2093.00,4186.01,8372.02,16744.04},
{17.33,34.65,69.30,138.59,277.18,554.37,1108.73,2217.46,4434.92,8869.84,17739.68},
{18.36,36.71,73.42,146.83,293.66,587.33,1174.66,2349.32,4698.64,9397.28,18794.56},
{19.45,38.89,77.78,155.56,311.13,622.25,1244.51,2489.02,4978.03,9956.06,19912.12},
{20.60,41.20,82.41,164.81,329.63,659.26,1318.51,2637.02,5274.04,10548.08,21096.16},
{21.83,43.65,87.31,174.61,349.23,698.46,1396.91,2793.83,5587.65,11175.30,22350.60},
{23.13,46.25,92.50,185.00,369.99,739.99,1479.98,2959.96,5919.91,11839.82,23679.64},
{24.50,49.00,98.00,196.00,392.00,783.99,1567.98,3135.96,6271.93,12543.86,25087.72},
{25.96,51.91,103.83,207.65,415.30,830.61,1661.22,3322.44,6644.88,13289.76,26579.52},
};

#define Ab 11
#define A  0
#define Ad 1

#define Bb 1
#define B  2
#define Bd 3

#define Cb 2
#define C  3
#define Cd 4

#define Db 4
#define D  5
#define Dd 6

#define Eb 6
#define E  7
#define Ed 8

#define Fb 7
#define F  8
#define Fd 9

#define Gb 9
#define G  10
#define Gd 11

unsigned int i;
unsigned int data[12] = {C, E, G, C, E, G, C, E, G, C, E, G};

int note_to_YM(int note, int level)
{
  return (fMaster / (16*note_frequency[note][level])) ;
}

// We only use 3 possible state of BC1, BC2, BDIR combination.
//
//          | BC1 | BC2 | BDIR |
// Inactive |  1  |  0  |   1  |
// Write    |  0  |  1  |   1  |
// Address  |  1  |  1  |   1  |
//
// We could remove the digitalWrite(BDIR, HIGH), but we still keep it if we want to use the read functions.

void set_mode_inactive()
{
  digitalWrite(BC1, HIGH);
  digitalWrite(BC2, LOW);
  digitalWrite(BDIR, HIGH);
}
void set_mode_write()
{
  digitalWrite(BC1, LOW);
  digitalWrite(BC2, HIGH);
  digitalWrite(BDIR, HIGH);
}
void set_mode_address()
{
  digitalWrite(BC1, HIGH);
  digitalWrite(BC2, HIGH);
  digitalWrite(BDIR, HIGH);
}

void set_address(char address)
{
  // set address mode
  set_mode_address();
  delayMicroseconds(us_delay);

  // wirte address
  delayMicroseconds(us_delay); 
  digitalWrite(DA0, (address & 0b00000001));
  digitalWrite(DA1, (address & 0b00000010));
  digitalWrite(DA2, (address & 0b00000100));
  digitalWrite(DA3, (address & 0b00001000));
  digitalWrite(DA4, 0);
  digitalWrite(DA5, 0);
  digitalWrite(DA6, 0);
  digitalWrite(DA7, 0);
  /*
  digitalWrite(DA4, (address & 0b00010000));
  digitalWrite(DA5, (address & 0b00100000));
  digitalWrite(DA6, (address & 0b01000000));
  digitalWrite(DA7, (address & 0b10000000));
  */
  delayMicroseconds(us_delay);

  // set inactive mode
  set_mode_inactive();
  delayMicroseconds(100);
}

void set_data(char data)
{
  // set write mode
  set_mode_write();
  delayMicroseconds(us_delay);
  
  // wirte data
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

  // set inactive mode
  set_mode_inactive();
  delayMicroseconds(us_delay);
}

void write_data(char address, char data)
{
  set_address(address);
  set_data(data);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
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

  
  for(i=0; i<16; i++) {
    write_data(i, 0);
  }
  write_data(7, 0b11111000);
  
  write_data(8, 0x0f);
  write_data(9, 0x0f);
  write_data(10, 0x0f);
}


void loop() {
  
  for (i=0; i<8; i++) {
    write_data(0, note_to_YM(0, i) & 0xff);
    write_data(1, note_to_YM(0, i) >> 8);
    
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
  }
  
    write_data(0, (note_to_YM(0, 4) & 0xff));
    write_data(1, (note_to_YM(0, 4) >> 8));
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    write_data(0, (note_to_YM(0, 5) & 0xff));
    write_data(1, (note_to_YM(0, 5) >> 8));
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);

    
    
  for (i=0; i<12; i++) {

  Serial.println(note_to_YM(data[i], 4), BIN);
  Serial.println((note_to_YM(data[i], 4) & 0xff), BIN);
  Serial.println((note_to_YM(data[i], 4) >> 8), BIN);
  
  Serial.println("-");
    
    write_data(0, (note_to_YM(data[i], 3) & 0xff));
    write_data(1, (note_to_YM(data[i], 3) >> 8));
    
    /*
    write_data(2, data[i] >> 1 & 0xff);
    write_data(3, data[i] >> 9);
    write_data(4, data[i] >> 2 & 0xff);
    write_data(5, data[i] >> 10);
    */
    
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  for (i=0; i<12; i++) {
    write_data(0, note_to_YM(data[i], 5) & 0xff);
    write_data(1, note_to_YM(data[i], 5) >> 8);
    
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}
