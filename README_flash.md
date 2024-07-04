# Flash usage
## Intro
The RP2040 does not have an internal flash.
All the flash is outside in the small black ic package on the left side over the RP2040.  
The CPUs can directly interface with this memory and execute code from it (XIP).  
The pico has some functions that let us write to this flash during runtime.  

## Usage
### Initialize
`FlashController flash;`

<br/>

### Read data
`uint8_t* data = flash.readData(<accessKey>);`

- **accessKey**: Key/ID for the data you want to access
- **data**: Start address of the data.

<br/>

### Write data
`bool status = flash.writeData(<accessKey>,<data>);`

- **accessKey**: Key/ID for the data you want to access
- **data**: The beginning of an array, where the data is stored you want to write.
- **status**: `true` if successful.

Please do not call this function unnecessary often.
Please check first if the data has changed before writing.

<br/>

### Erase all data
`flash.eraseAllData();`

This command erases all data currently stored in flash (only the data which we can also write (no code))  
Only use this when you exactly know what you are doing.  
Theoretically, you should never use this function if you use this library correctly (and it has no bugs...)

<br/>

### Add a new access key
To read or write data, the flash controller needs to know where your data is stored and how big it is.
This is achieved through predefined datasets (FlashItem).  
Each dataset has an accessKey (ID) and a size (number of bytes).  
To add/remove these, you must modify flash_controller.h/.cpp.  
**Note**: An access Key must be unique.
All the number of bytes combined should not be more than 256-1 (255), or you have to increase NUMBER_OF_PAGES by 1.  
No flash item should have more than 255 bytes of size.  
No flash item should overlap between pages (you can fill space with dummy content).

## Notes
During writing and erasing, there are no IRQs allowed, and only one core is allowed to access the flash.
The IRQs are handled by the flash controller itself.
It will disable the IRQs at the beginning of a flash command and restore them at the end.  
That only one core is running is your responsibility!  
We can only store 4095 bytes of data (one sector - internal byte)

Also see flash example.

## Technical notes
Flash can only be written to in 256 byte pages.  
Flash can only be erased in 4096 byte sectors.  
Erasing a sectors sets all bits to `1`.  
Writing only sets bits to `0`.  
So you cant write on the same address multiple times or data will get lost because you can't write an `1`.  
Because every erase-cycle wears out the flash, we only erase the sector if all the pages inside have been written.  
To further protect the flash from too many erase-cycles, we use multiple flash sectors to write our data and increment every time to the next sector.  
If no empty pages are found, we erase.  
This controller currently uses five sectors of flash.
This is a size of 4096*5 (20.480) bytes.  
This gives us 80 (20.480/256) write cycles before we need to erase.  
The flash that is solders to the board has, according to spec, a minimum of 100k erase-cycles per sector.  
This gives us 8.000.000 write cycles.  
Still, you should check if your data has changed and need rewriting before writing it again.

To every page we write, we steal one byte for internal use.  
This is the first byte to each page.  
When writing, we set this byte to a specific pattern.
With this pattern, we can easily detect a full / empty page of data.

To even further decrease erase-cycles, we could divide each page in smaller pieces.  
But this functionality is an idea for the future. :^)   
( ._.)
