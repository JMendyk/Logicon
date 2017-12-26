//
// Created by rufus on 11.12.17.
//

#include <exceptions/wrongPortException.h>
#include <algorithm>
#include <iostream>
#include "gates/gate.h"

namespace Logicon {
    Gate::Gate(ID id, unsigned int inputsCount, unsigned int outputsCount) : id(id) {
        // initialize inputs array
        this->inputs.resize(inputsCount);
        for (auto input: inputs) {
            input.first = false;
        }
        // initialize outputs array
        this->outputs.resize(outputsCount);
        for (auto output: outputs)
            output.first = false;
    }

    ID Gate::getID() const {
        return id;
    }

    // ======
    // INPUTS
    // ======

    int Gate::getInputsCount() const {
        return this->inputs.size();
    }

    State Gate::getInputState(Port input) const {
        if (input < 0 || input >= this->inputs.size())
            throw wrongPortException(this->id, input, true);

        return this->inputs[input].first;
    }

    void Gate::setInputState(Port input, State state) {
        if (input < 0 || input >= inputs.size())
            throw wrongPortException(this->id, input, true);

        inputs[input].first = state;
    }

    bool Gate::isInputEmpty(Port input) const {
        if (input < 0 || input >= inputs.size())
            throw wrongPortException(this->id, input, true);

        return inputs[input].second.empty();
    }

    bool Gate::isInputConnectedWith(Port input, ID otherId, Port otherPort) {
        if (input < 0 || input >= inputs.size())
            throw wrongPortException(this->id, input, true);

        return std::find(inputs[input].second.begin(),
                         inputs[input].second.end(),
                         Connection(otherId, otherPort))
               != inputs[input].second.end();
    }

    const Gate::PortConnectionList_ &Gate::getInputConnections(Port input) const {
        if (input < 0 || input >= inputs.size())
            throw wrongPortException(this->id, input, true);

        return inputs[input].second;
    }

    void Gate::setInputConnection(Port input, ID otherId, Port otherPort) {
        if (input < 0 || input >= inputs.size())
            throw wrongPortException(this->id, input, true);

        // single connection only
        if (!inputs[input].second.empty()) { // if it is connected, modify the connection
            inputs[input].second.back().id = otherId;
            inputs[input].second.back().port = otherPort;
        } else // array is empty, construct new element at the end
            inputs[input].second.emplace_back(Connection(otherId, otherPort));
    }

    void Gate::clearInputConnections(Port input) {
        if (input < 0 || input >= inputs.size())
            throw wrongPortException(this->id, input, true);

        inputs[input].second.clear();
    }

    // =======
    // OUTPUTS
    // =======

    int Gate::getOutputsCount() const {
        return outputs.size();
    }

    State Gate::getOutputState(Port output) const {
        if (output < 0 || output >= outputs.size())
            throw wrongPortException(this->id, output, false);

        outputs[output].first;
    }

    void Gate::setOutputState(Port output, State state) {
        if (output < 0 || output >= outputs.size())
            throw wrongPortException(this->id, output, false);

        outputs[output].first = state;
    }

    bool Gate::isOutputEmpty(Port output) const {
        if (output < 0 || output >= outputs.size())
            throw wrongPortException(this->id, output, false);

        return outputs[output].second.empty();
    }

    bool Gate::isOutputConnectedWith(Port output, ID otherId, Port otherPort) const {
        if (output < 0 || output >= outputs.size())
            throw wrongPortException(this->id, output, false);

        return std::find(outputs[output].second.begin(),
                         outputs[output].second.end(),
                         Connection(otherId, otherPort)) != outputs[output].second.end();

    }

    const Gate::PortConnectionList_ &Gate::getOutputConnections(Port output) {
        if (output < 0 || output >= outputs.size())
            throw wrongPortException(this->id, output, false);

        return outputs[output].second;
    }

    void Gate::addOutputConnection(Port output, ID otherId, Port otherPort) {
        if (output < 0 || output >= outputs.size())
            throw wrongPortException(this->id, output, false);

        if (isOutputConnectedWith(output, otherId, otherPort)) // TODO log connect abort
            return;

        outputs[output].second.emplace_back(Connection(otherId, otherPort));
    }

    void Gate::removeOutputConnection(Port output, ID otherId, Port otherPort) {
        if (output < 0 || output >= outputs.size())
            throw wrongPortException(this->id, output, false);

        if (isOutputConnectedWith(output, otherId, otherPort)) // TODO log disconnect abort
            return;

        auto found = std::find(outputs[output].second.begin(),
                               outputs[output].second.end(),
                               Connection(otherId, otherPort));

        outputs[output].second.erase(found);
    }

    void Gate::clearOutputConnections(Port output) {
        if (output < 0 || output >= outputs.size())
            throw wrongPortException(this->id, output, false);

        outputs[output].second.clear();
    }

} // namespace Logicon