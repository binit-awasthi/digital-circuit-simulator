#pragma once

#include "port.hpp"

class InputPort;

class OutputPort : public Port
{

    bool state;

public:
    std::vector<InputPort *> childPorts;

    void setChildrenState();
};