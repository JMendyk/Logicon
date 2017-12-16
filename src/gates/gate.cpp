//
// Created by rufus on 11.12.17.
//

#include "gates/gate.h"

Gate::Gate(const int ID) : ID(ID) {}

int Gate::getID() const {
    return ID;
}

bool Gate::getInputState(int index) {

}

bool Gate::getOutputState(int index) {

}

void Gate::setInputState(int index, bool state) {

}

void Gate::setOutputState(int index, bool state) {

}

std::pair<int, int> Gate::getInputConnection(int index) {

}

void Gate::setInputConnection(int index, int id, int port) {

}

void Gate::addOutputConnection(int index, int id, int port) {

}

void Gate::removeOutputConnection(int id, int port) {

}
