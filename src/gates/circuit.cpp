//
// Created by rufus on 11.12.17.
//

#include "circuit.h"

Circuit::Circuit(const int ID) : ID(ID) {}

int Circuit::getID() const {
    return ID;
}

bool Circuit::getInputState(int index) {

}

bool Circuit::getOutputState(int index) {

}

void Circuit::setInputState(int index, bool state) {

}

void Circuit::setOutputState(int index, bool state) {

}

std::pair<int, int> Circuit::getInputConnection(int index) {

}

void Circuit::setInputConnection(int index, int id, int port) {

}

void Circuit::addOutputConnection(int index, int id, int port) {

}

void Circuit::removeOutputConnection(int id, int port) {

}
