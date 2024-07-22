#include "../header_files/inputPort.hpp"
#include "../header_files/outputPort.hpp"

InputPort::~InputPort()
{

    for (auto portIt = parentPort->childPorts.begin(); portIt != parentPort->childPorts.end();)
    {

        // auto &port = *portIt;
        if ((*portIt) == this)
        {
            portIt = parentPort->childPorts.erase(portIt);
            std::cout << "child port removed from parent output port" << std::endl;
            break;
        }
        else
        {
            ++portIt;
        }
    }

    isConnected = false;
    setState(false);
    parentPort = nullptr;
    std::cout << "deleted: input port" << std::endl;
}


