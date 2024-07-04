# Runtime

## Intro
There are four different build environments:
- PlatformIO Normal
- PlatformIO Fast
- C/C++ SDK (Debug)
- C/C++ SDK (Release)

On an execution speed perspective, the C/C++ SDK release is by far the fastest.  
The fast PlatformIO environment comes seconds but is still significantly slower than the C/C++ SDK.  
The normal PlatformIO environment comes in third with sometimes near or worse performance to the fast PlatformIO environment.
The C/C++ SDK debug environment is last.

Here is a table of some measurements in the different environments

| Operation                                                                   | PlatformIO Normal | PlatformIO Fast | C/C++ SDK Debug | C/C++ SDK Release |
|-----------------------------------------------------------------------------|-------------------|-----------------|-----------------|-------------------|
| Creation of 1000 hamiltonian cycles                                         | 5.472.567         | 5.313.235       | 6.995.862       | 3.246.311         |
| Calculation of 1000 Game of Life frames<br/>(without loading or displaying) | 376.821           | 368.443         | 511.537         | 149.013           |
| Calculation of 1000 Firework frames<br/>(without loading or displaying)     | 920.234           | 444.682         | 431.344         | 364.977           |

All measurements are in µs.  
Note that the measurements are not 100% precise and are sometimes dependent on randomness.
But they still give a good idea of the different runtimes.

The differences can be tracked down two a few things.
The C/C++ SDK is way more optimized for the RP2040 than the Arduino (PlatformIO) framework is.
This is especially true to floating point
and divide operations
because the Arduino framework does not normally use the build in software/hardware features that the RP2040 has.  
In the PlatformIO fast environment, I added some of these features (floating point computation and hardware divider).

## Floating point computation

### Intro
The RP2040 does not have a floating-point-point(FPU), so the hardware does not support floating-point numbers.
But with a little bit of math magic, you can still calculate with floating-point numbers.
But this math magic is relatively slow and thus is not as performant as "normal" fixed-point numbers.

This math magic is "normally" done by the compiler and is done in a way so that all CPUs without an FPU can calculate this.
But luckily, Raspberry Pi developed their own piece of software which has a drastically better performance than the "normal" compiler math magic.

This piece of code is not normally used by the Arduino Framework for the RP2040.
So we need to include it ourselves.

This is why there are now two different build environments.  
`pico_normal` uses the normal algorithms from the compiler.  
`pico_fast` uses the algorithms specialized for the RP2040.  

Code wise in C/C++ there are no changes.

Note that `pico_fast` is not well tested and can crash or behave "weird".

To learn more and read about the performance increases,
see the documentation of the [C/C++ SDK section 2.7](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf#sdk-runtime-section).

And yes, "math magic" is a real word! :^)