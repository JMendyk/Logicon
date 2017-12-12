//
// Created by rufus on 11.12.17.
//

#ifndef LOGICON_AND_H
#define LOGICON_AND_H

#include "circuit.h"

class And : Circuit {
public:

    explicit And(int ID);

    void update() override;
};


#endif //LOGICON_AND_H
