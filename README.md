# TGL Board

### 8x16 RGB Board


# Note
You can either use PlatformIO (Arduino Framework) or the official C/C++ SDK from Raspberry Pi.  
If you want to use the C/C++ SDK, please use the c-SDK branch.

Code compiled with the C-SDK in release mode
is approximately 1.65 times faster than code compiled with the Arduino framework.

But code compiled with the C-SDK in debug mode
is approximately 0.79 times slower than code compiled with the Arduino framework.

Calculations are based on the creation of 1000 hamiltonian circles.

# Usage

You need PlatformIO to use this project.  
Arduino IDE might work too (not tested).

In the platform.ini file, there are now two build environments.
`pico_normal` and `pico_fast` you can read about the differences here [Floating Point Computation](README_floating_point_computation.md)

For your own programming, you can use my pioMatrixOutput library.
Documentation is here [pioMatrixOutput](READMEpioMatrixOutput.md)

For your own text, you can use my library.
Documentation is here [Textcontroller](README_textController.md)


# Hardware

Schematic, layout and gerber files can be found [here](hardware)  

## Notes
If you bricked your board,
and/or you can't upload code anymore,
use a 1k ohm resistor and put it between ground (e.g. USB-C housing)
and the left side of the small smd-resistor above the flash.  
See the picture.  
While holding the resistor, plug the board back into your pc/power and the board should appear as a normal USB-stick.  
Now you can program the board again normally.  
This can happen, if your code does stuff that it shouldn't do like to access an array beyond its boundaries.  
Be aware that if you place the resistor wrong, you could damage the board!

![resistor placement](assets/images/resistorPlacement.png "resistorPlacement")
![resistor placement close](assets/images/resistorPlacementClose.png "resistorPlacementClose")
