//
// Created by rufus on 11.12.17.
//

#ifndef LOGICON_SWITCH_H
#define LOGICON_SWITCH_H


#include "gate.h"

class Switch : Gate {
public:
    explicit Switch(int ID);

    void clickAction() override;

};


#endif //LOGICON_SWITCH_H
