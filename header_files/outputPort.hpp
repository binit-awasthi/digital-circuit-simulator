#pragma once

#include "port.hpp"

class InputPort;

class OutputPort : public Port
{

public:
    std::vector<InputPort *> childPorts;

    // void setChildrenState();
};