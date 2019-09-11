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
| YM2413     | OPLL        |                     | Awaiting delivery      |
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
| YM2151     | OPM         | YM3012              | :white_check_mark:     |
| YM2164     | OPP         | YM3012 :grey_question: | :x::heavy_dollar_sign: |
| YM2154     | RYP4        | :grey_question:     | :x:                    |
| YM2414     | OPZ         | :grey_question:     | :x:                    |



### Accessory chips list

| Chip       | Other name  | Usage      |  Do I have it ?    |
| :--------: | :---------: | :--------: | :----------------: |
| YM3014     | Y3014B      | DAC        | :white_check_mark: |
| YAC512     |             | DAC        | :x:                |
| YM3016     | YM3016-D    | DAC        | Awaiting delivery  |
| YM3012     |             | DAC        | :white_check_mark: |


## Play Songs

To play and store a song, we have to convert a music score into C arrays which can be interpreted by the program.
A Python script to transform a channel from a midi file into an array will be available soon.

### SSG

At first, a song is loaded, then we need to call an update function (song_next_iteration()) to update the SSG register.  
For now, we want an SSG song to command the following elements.

* 3 square wave channel (note and duration)
* 1 noise (frequency and duration)

For each channel, we use two arrays, one for note and one for duration.  
The note array is read when the previous note has finished and we update the channel frequency with it's information. If value is 0, the channel is muted  
The duration array is read when the previous note has finished and we update the couter (which is decremented every time the update function is called) with the value in the duration array.
For memory reason, we use char (8 bits) to store thoses information, but if a duration is longer than 255 call, we can use a word (16 bits) using 3 cases of the array, one for a 0 flag and two for 16 bits duration.

```
{0, 0x01, 0x90} // 400 call duration.
```

The tempo is set by the delay between each call to the update function. For this reason, the duration has no absolute relation with "note value", if the update is called 4 times per BPM, a "4" duration is a 𝅘𝅥 but if the update is called 8 times per BPM, it's a 𝅘𝅥𝅮.

In our future example, we use the following table as default

| Duration    | Equivalent in note value |
| :---------: | :----------------------: |
| 1           | 𝅘𝅥𝅲 |
| 2           | 𝅘𝅥𝅱 |
| 4           | 𝅘𝅥𝅰 |
| 8           | 𝅘𝅥𝅯 |
| 16          | 𝅘𝅥𝅮 |
| 32          | 𝅘𝅥 |
| 48          | 𝅘𝅥. |
| 64          | 𝅗𝅥 |
| 96          | 𝅗𝅥. |
| 128         | 𝅝 |
| 256 (0,1,0) | 𝅝𝆊𝅝 |
