#include "../header_files/inputPort.hpp"
#include "../header_files/outputPort.hpp"

InputPort::~InputPort()
{
    this->parentPort = nullptr;
    std::cout << "deleted: input port" << std::endl;
}