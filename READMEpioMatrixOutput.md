# PIO Matrix Output Library

### Library to interface with the 8x16 ARGB Display

# Table of Contents
1. [Features](#features)
2. [Overview](#overview)
   1. [Modes](#modes)
   2. [Terminology](#terminology)
3. [Usage](#usage)
4. [Explanations](#explanations)
   1. [Framebuffer](#framebuffer)
   2. [Frame bs Subframe](#frame-vs-subframe)
   3. [RAM Usage](#ram-usage)
   4. [Output](#output)
5. [Notes](#notes)


# Features

- Framebuffer support
- Subframes support
- No CPU interaction needed during output
- Two (real) parallel outputs
- Fast refresh rate possible (~200 Hz)


# Overview
## Modes
There are two main modes of usage:
- Manual mode
- Automatic (framebuffer) mode

In Manual mode, you are responsible for creating the frames, sending the frames to the library and telling the software when to display the frames.

In Automatic (framebuffer) mode, you are only responsible for creating and sending the frames to the software.
The software will then display the frames on a fixed clock/time.
In this mode, frames are stored, as the name framebuffer implies.

## Terminology
**Frame:**
A frame is one image on the display.

**Subframes:**
One frame can be divided in subframes.
Subframes are used to create a larger range of colors and gradations.

To learn more about frames and subframes, please read [frame vs subframe](#frame-vs-subframe)

# Usage
## General use
### Initialize
`MatrixOutput ledMatrix(<pio>, <sm>, <dmaChannel>, <pin1>, <pin2>);`
- **ledMatrix**: name of the object
- **pio**: Identifier for the PIO instance (e.g. `pio0` (see examples))
- **sm**: Index of the state machine inside the PIO (e.g. `0`)
- **dmaChannel**: Index of the dma channel to use (e.g. `0`)
- **pin1**: GPIO pin of the first matrix half (e.g. `10`)
- **pin2**: GPIO pin of the second matrix half (e.g. `11`)

<br/>

### Enable Subframes
`ledMatrix.enableSubframes(<enable>);`

- **enable**: `true` or `false`. By default `true`

This command enables/disables subframes.

<br/>

### Clear Display
`ledMatrix.clearDisplay();`

Clears the display, disables subframes and the framebuffer.

<br/>


## Manual mode
### Setting display data
`ledMatrix.setDisplayData(<data>);`

- **data**: Address of an 8 by 16 Color array (see examples)

This command only sets the next frame to be sent. It does not send the data.

<br/>

### Displaying the data
`ledMatrix.sendData();`

Send the data to the display.

<br/>


## Automatic mode
### Enable Framebuffer
`ledMatrix.enableFramebuffer(<enable>);`

- **enable**: `true` or `false`. By default `true`

This command enables/disables the framebuffer.

<br/>

### Set Framebuffer interval
`ledMatrix.setFrameBufferInterval(<interval>);`

- **interval**: time in ms until the next frame is displayed (e.g. `90`)

If set to `0` the framebuffer remains on, but the timer is disabled.
You need to send the data manually.  
The interval can be set any time.


<br/>


### Load frame to framebuffer
`ledMatrix.addToFrameBuffer(<data>);`

- **data**: Address of an 8 by 16 Color array (see examples)

This command only loads the next frame to be s. It does not send the data.

<br/>

### Get free frames
`uint8_t freeFrames = ledMatrix.getFreeFrames();`

Returns the number of frames that can be added to the framebuffer before it overflows.





# Explanations
## Framebuffer
As the name suggests it buffers frames.   
Normally it is set to store up to 10 frames.
These frames can be pre-rendered by the CPU and then get output on a fixed timing/clock signal.

## Frame vs Subframe
The LEDs used in the Matrix are ARGB LEDs.
That means that each LED will remember its color.
This means that for one frame we only need to send one data frame to each LED.
So 128 dataframes in total for the whole matrix.   
So the CPU can spin around in circles until the next frame has to be sent.

Instead of waiting and spinning around (even if this is fun), the CPU could use this time to output more and more frames over and over again.  
For example, in the time the CPU waits for the next frame, there could be sent three more frames.   
And this is exactly what subframes are.  
One frame is divided in different subframe (four subframes by default).
By using the subframes in a smart way, we can create more shades of a color.
It is like PWM but fancy and more complex (not really but hey).

So if we only have frames we could only display distinct values of brightness (0,1,2, ...)
For example, we would send a `1` once to have a brightness level of 1.

But with subframes, we also can display 0.5 as a brightness level.
As described, we divide one frame into, for example, four subframes.
To display 0.5 as a continuous brightness level, we would send
`1100, 1100, 1100, 1100, ...`
over and over again. 
In this way, we can create smaller steps in brightness.
With 4 subframes, we can go in steps of 0.25.

This is, of course, a simple example, but this is what the software is doing if you enable subframes.  
You cannot directly control the values of the subframes.
Subframes are calculated and stored when setting the frame either as data or when adding the frame to the framebuffer.

## RAM usage
As you can imagine, subframes in combination with the framebuffer are really RAM intensiv.
And yes, that is true.  
Normally, we can store 10 frames in the frame buffer.
Each of these frames has four subframes.
And each subframe needs to store the color information for each of the 128 LEDs.
Each LED takes three bytes of data.  
3 x 128 = 384 bytes per subframe.  
384 x 4 = 1536 bytes per frame.  
1536 x 10 = 15360 bytes.  
That is a lot of memory.  
Especially if you remember that an Arduino UNO (R3) only has 2kB of RAM.
We use more than 7 times the amount just for the framebuffer alone.  
In total, the RP2040 has 256 kBytes of RAM.
So we have plenty to spare. (Maybe more subframes?...)


## Output
The cool thing about the RP2040 is that it has PIO.  
PIO stands for programmable IO.  
To break it down. 
It has 2 PIO Blocks with 4 State Machines each.
Each of these state machines is like a really, really, really tiny CPU.
Each machine has one input and one output buffer to get data to and from the machine.
This data can be output to the GPIO pins.
Inside these machines you can programm a small programm, to output the data just as you want.
And the output is parallel on as many pins as you want.  
To learn more about PIO,
read the [documentation of the RP2040 Chapter 3](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#section_pio).

These state machines run independently of the CPU. 
The CPU only needs to set up the machine and handel the data in the input/output registers.

This alone is already really cool.
But it gets even better.

Even if the CPU only needs to handle the loading of the state machine register, this is still a lot of time wasted on simple tasks.   
There is a cool feature in many microcontrollers called DMA.   
DMA stands for direct memory access. 
The DMA can access memory and copy data from one place to another. 
And this extremely fast and without interaction of the CPU.
So we have an array of data in the RAM.
This data has been rendered by the CPU and stored in the RAM.
The DMA takes this data and loads it in small pieces into the state machine buffer which then outputs it onto the GPIO pins.
And all this without any interaction from the CPU.  
While the DMA and the PIO are output the data and loading the LEDs with data, the CPU can already render the next frame and/or spinning around in circles :)


# Notes
When using subframes and/or the framebuffer, please don't use the `delay` instruction.
It can mess up everything.



