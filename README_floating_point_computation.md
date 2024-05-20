# Floating point computation

## Intro
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

To learn more and read about the performance increases, see the documentation of the C/C++ SDK page 24–28.

And yes, "math magic" is a real word! :^)