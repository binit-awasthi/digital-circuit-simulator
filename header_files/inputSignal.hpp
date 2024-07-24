#pragma once

#include "includes.hpp"
#include "outputPort.hpp"
#include "inputPort.hpp"

class InputSignal : public OutputPort
{

public:
    InputSignal(InputPort *);
    ~InputSignal();
    static std::vector<InputSignal *> inputSignals;
};