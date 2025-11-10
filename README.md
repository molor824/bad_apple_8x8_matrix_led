# Bad Apple!! on 8x8 matrix LED

Render Bad Apple!! music video on 8x8 matrix LED.
https://www.youtube.com/watch?v=gfz-vlIPXD8

Note: The code does not strictly require Bad Apple music video. You can try with any video you like, as it will be converted to grayscale and then rendered on the 8x8 matrix LED.

## Project structure

* `receiver` Arduino side code for receiving the streaming data
* `streamer` PC side code for streaming the music video

## Components used

* Microcontroller (Arduino UNO R3)
* 8x8 matrix LED display (1588AS)
* 2x 8-bit shift register (74HC595N)
* 8x 1k ohm resistor

## Prerequisites

### Streamer

You need Python 3.

## How to run

1. Connect your Arduino board.
2. Locate what port is your Arduino connected to.
3. Open `receiver` folder in Arduino IDE and upload the code to your Arduino board.
4. Open `streamer` folder and update music video path and serial port if necessary.
5. Install packages from `requirements.txt` and run the code.
6. Enjoy!
