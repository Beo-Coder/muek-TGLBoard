# TGL Board

### 8x16 RGB Board

# Usage
You need PlatformIO to use this project.  
Arduino IDE might work too (not tested).

For own programming, you can use my pioMatrixOutput library.
Documentation is here [pioMatrixOutput](READMEpioMatrixOutput.md)

For own scroll text, you can use my library.
Documentation is here [scrollText](READMEscrollText.md)

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
