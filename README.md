# Bad Apple!! on 8x8 matrix LED

Render Bad Apple!! music video on 8x8 matrix LED.
https://www.youtube.com/watch?v=gfz-vlIPXD8

## Project structure

* `receiver` Arduino side code for receiving the streaming data
* `streamer` PC side code for streaming the music video

## Components used

* Microcontroller (Arduino UNO R3)
* 8x8 matrix LED display (1588AS)
* 2x 8-bit shift register (74HC595N)
* 8x 1k ohm resistor

## How to run

1. Connect your Arduino board.
2. Open `receiver` folder in Arduino IDE and upload the code to your Arduino board.
3. Open `streamer` folder and run `python3 .` on linux or mac, run `py .` on windows
