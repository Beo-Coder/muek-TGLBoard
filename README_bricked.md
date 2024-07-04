If you bricked your board,
and/or you can't upload code anymore,
use a 1k ohm resistor and put it between ground (e.g. USB-C housing)
and the left side of the small smd-resistor above the flash. (See the pictures)  
While holding the resistor, plug the board back into your pc/power and the board should appear as a normal USB-stick.  
Now you can program the board again normally.  

**Be aware that if you place the resistor wrong, you could damage the board!**

This can happen, if your code does stuff that it shouldn't do like to access an array beyond its boundaries.  
Now with watchdog support, it is also possible that the watchdog somehow does not allwo you to program the board.
If you encounter some sort of watchdog related problems, you can simply disable it.


![resistor placement](assets/images/resistorPlacement.png "resistorPlacement")
![resistor placement close](assets/images/resistorPlacementClose.png "resistorPlacementClose")