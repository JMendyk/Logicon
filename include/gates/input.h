//
// Created by rufus on 11.12.17.
//

#ifndef LOGICON_INPUT_H
#define LOGICON_INPUT_H


#include "gate.h"

class Input : Gate {
public:
    explicit Input(int ID);

    void clickAction() override;
};


#endif //LOGICON_INPUT_H
