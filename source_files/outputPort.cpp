#include "../header_files/outputPort.hpp"
#include "../header_files/inputPort.hpp"

void OutputPort::setChildrenState()
{
    // if (!childPorts.empty())
    // {
    for (auto port : childPorts)
    {
        if (port == nullptr)
        {
            std::cout << "null" << std::endl;
            continue;
        }

        port->setState(this->getState());
        // std::cout << "input: " << port << " output: " << this << std::endl;
    }
    // }
}
