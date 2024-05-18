// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE

#include <hardware/pio.h>

#endif

// ---- //
// argb //
// ---- //

#define argb_wrap_target 0
#define argb_wrap 4

static const uint16_t argb_program_instructions[] = {
        //     .wrap_target
        0xe203, //  0: set    pins, 3                [2]
        0x6202, //  1: out    pins, 2                [2]
        0xe000, //  2: set    pins, 0
        0x01e0, //  3: jmp    !osre, 0               [1]
        0x0003, //  4: jmp    3
        //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program argb_program = {
        .instructions = argb_program_instructions,
        .length = 5,
        .origin = -1,
};

static inline pio_sm_config argb_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + argb_wrap_target, offset + argb_wrap);
    return c;
}

static inline void argb_program_init(PIO pio, uint sm, uint offset, uint pin1, uint pin2, uint autoshift_size) {
    pio_sm_config c = argb_program_get_default_config(offset);

    // init pins
    pio_gpio_init(pio, pin1);
    pio_gpio_init(pio, pin2);

    // configure out pins
    sm_config_set_out_pins(&c, pin1, 2);
    //sm_config_set_out_pins(&c, pin2, 1);





    sm_config_set_set_pins(&c, pin1, 2);
    //sm_config_set_set_pins(&c, pin2, 1);

    // set pins as out
    pio_sm_set_consecutive_pindirs(pio, sm, pin1, 2, true);





    // set auto shift and FIFO join
    sm_config_set_out_shift(&c, false, true, autoshift_size);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    // clear FIFOs
    pio_sm_clear_fifos(pio, sm);

    // set clock divider
    float div = SystemCoreClock / (800000 * 9);
    sm_config_set_clkdiv(&c, div);

    // init program
    pio_sm_init(pio, sm, offset, &c);

    // stop program
    pio_sm_set_enabled(pio, sm, false);
}

#endif
