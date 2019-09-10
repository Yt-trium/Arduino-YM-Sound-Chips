# Arduino-YM-Sound-Chips
Using Yamaha Sound Chips as Audio Device for Arduino


## State of progress

| Sound Chip   | Work in progress | Works |
| ------------ | :--------------: | :---: |
| YM2149 (SSG) | :white_circle: | :white_check_mark: |
| YM2203 (OPN) | :white_check_mark: | :x: |
| YM2151 (OPM) | :x: | :x: |


## Stage of work in progress

| Sound Chip   | Write to chip | Music (A/B/C) | Noise | Mixer | Level control | Envelope |
| ------------ | :-----------: | :-----------: | :---: | :---: | :-----------: | :------: |
| YM2149 (SSG) | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: |

| Sound Chip   | OPN as SSG |
| ------------ | :--------: |
| YM2203 (OPN) | :x: |


## Yamaha sound chips cheat sheet

### Sound chips list

| Sound Chip | Common name | Other chip required | Do I have it ?         |
| :--------: | :---------: | :-----------------: | :--------------------: |
| YM2149F    | SSG         | :white_circle:      | :white_check_mark:     |
|            |             |                     |                        |
| YM3526     | OPL         | YM3014              | Awaiting delivery      |
| YM2413     | OPLL        | quartz oscillator   | Awaiting delivery      |
| Y8950      | MSX-AUDIO   | YM3014              | :x:                    |
| YM3812     | OPL2        | YM3014              | Awaiting delivery      |
| YMF262     | OPL3        | YAC512              | :x:                    |
| YMF289     | OPL3-L      | :grey_question:     | :x:                    |
| YMF278     | OPL4        | :grey_question:     | :x:                    |
|            |             |                     |                        |
| YM2203     | OPN         | YM3014              | :white_check_mark:     |
| YM2608     | OPNA        | YM3016              | Awaiting delivery      |
| YM2610     | OPNB        | YM3016              | Awaiting delivery      |
| YM2612     | OPN2        |                     | :x:                    |
| YM3438     | OPN2C       |                     | Awaiting delivery      |
| YMF276     | OPN2L       | DAC :grey_question: | :x:                    |
| YMF288     | OPN3        | DAC :grey_question: | :x:                    |
|            |             |                     |                        |
| YM2151     | OPM         |                     |                        |
| YM2164     | OPP         |                     |                        |
| YM2154     | RYP4        |                     |                        |
| YM2414     | OPZ         |                     |                        |
| YMF292     | SCSP        |                     |                        |
| YMF7xx     | DS-1        |                     |                        |
| YMZ280B    | PCMD8       |                     |                        |
|            |             |                     |                        |
| DSP-1      |             |                     |                        |



### Accessory chips list

| Chip       | Other name  | Usage      |  Do I have it ?    |
| :--------: | :---------: | :--------: | :----------------: |
| YM3014     | Y3014B      | DAC        | :white_check_mark: |
| YAC512     |             | DAC        | :x:                |
| YM3016     | YM3016-D    | DAC        | Awaiting delivery  |
| YM3012     |             | DAC        | :white_check_mark: |

