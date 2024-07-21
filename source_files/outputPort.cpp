#include "../header_files/outputPort.hpp"
#include "../header_files/inputPort.hpp"

void OutputPort::setChildrenState()
{
    for (auto port : childPorts)
    {
        // if (port == nullptr)
        // {
        //     std::cout << "null" << std::endl;
        //     continue;
        // }

        if (!port->isConnected)
            port->setState(this->getState());
    }
}

OutputPort::~OutputPort()
{
    for (auto port : childPorts)
    // for (auto port : childPorts)
    {
        port->setState(false);
        port->isConnected = false;
    }

    // for (auto &port : childPorts)
    // {
    //     port->parentPort = nullptr;
    // }
}