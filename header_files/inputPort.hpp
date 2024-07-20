
#pragma once

#include "port.hpp"

class OutputPort;

class InputPort : public Port
{

public:
    OutputPort *parentPort = nullptr;

};