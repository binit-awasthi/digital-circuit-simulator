#include "../header_files/outputPort.hpp"
#include "../header_files/inputPort.hpp"

void OutputPort::setChildrenState(bool state)
{
    for (auto &port : childPorts)
    {
        port->setState(state);
    }
}