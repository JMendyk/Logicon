//
// Created by rufus on 11.12.17.
//

#ifndef LOGICON_CIRCUIT_H
#define LOGICON_CIRCUIT_H

#include <string>
#include <tuple>
#include <vector>
#include "../data.h"

class Circuit {
private:
    const int ID;
    Data data;
    std::vector<std::tuple<bool, int, int> > inputs;
    std::vector<
            std::pair<
                    bool,
                    std::vector<
                            std::pair<int, int>
                    >
            > > outputs;
public:
    explicit Circuit(int ID);

    int getID() const;

    virtual void update()=0;

    virtual void clickAction() {};

    bool getInputState(int index);

    bool getOutputState(int index);

    void setInputState(int index, bool state);

    void setOutputState(int index, bool state);

    std::pair<int, int> getInputConnection(int index);

    void setInputConnection(int index, int id, int port);

    void addOutputConnection(int index, int id, int port);

    void removeOutputConnection(int id, int port);
};


#endif //LOGICON_CIRCUIT_H
