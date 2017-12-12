//
// Created by rufus on 11.12.17.
//

#ifndef LOGICON_INPUT_H
#define LOGICON_INPUT_H


#include "circuit.h"

class Input : Circuit {
public:
    explicit Input(int ID);

    void clickAction() override;
};


#endif //LOGICON_INPUT_H
