//
// Created by leo on 11.05.24.
//

#ifndef MUEK_TGL_BOARD2_STATIC_TEXT_H
#define MUEK_TGL_BOARD2_STATIC_TEXT_H

#include <Arduino.h>
#include "letters.h"
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "color.h"
#include "display_program.h"
#include "text_controller.h"
#include "scroll_text.h"

#define NUMBER_FREE_PIXELS_ADDED_STATIC_TEXT 1 // Only added if the text is too large to fit on display
#define STATIC_TEXT_WAIT_TIME_START 3
#define STATIC_TEXT_WAIT_TIME_END 3

class StaticText : public ScrollText{

    bool needScrolling;
    uint8_t staticTextTime;
    uint8_t state;

    void refreshText();
    void initText();

public:

    explicit StaticText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void setText(String *text) override;

    void createAndLoadFrame() override;

    void refresh() override;
    void restart() override;


};


#endif //MUEK_TGL_BOARD2_STATIC_TEXT_H
