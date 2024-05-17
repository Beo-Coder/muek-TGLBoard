//
// Created by leo on 11.05.24.
//

#ifndef MUEK_TGL_BOARD2_TEXT_CONTROLLER_H
#define MUEK_TGL_BOARD2_TEXT_CONTROLLER_H

#include "Arduino.h"
#include "display_program.h"
#include "letters.h"
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "color.h"

#define MAX_TEXT_LENGTH 500


class TextController : public display_program {

protected:

    inline static uint8_t idTextArray[MAX_TEXT_LENGTH]{0};
    inline static uint16_t idTextArraySize{0};
    inline static uint16_t idTextArrayIndex{0};


    inline static Color *textColor{nullptr};
    inline static Color *backgroundColor{nullptr};








    virtual void createIDTextArray(String *text) = 0;

public:

    TextController(MatrixOutput *matrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    virtual void setText(String *text);
    void setColor(Color *textColor, Color *backgroundColor);

    virtual void createAndLoadFrame() = 0;





    virtual void refresh() = 0;
    virtual void restart() = 0;

    void button1ISR(bool state) override;
    void button2ISR(bool state) override;


};


#endif //MUEK_TGL_BOARD2_TEXT_CONTROLLER_H
