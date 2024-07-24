#include "../header_files/inputSignal.hpp"

std::vector<InputSignal *> InputSignal::inputSignals;

InputSignal::InputSignal(InputPort *port)
{
    port->setState(getState());
}

InputSignal::~InputSignal()
{
    delete this;
}
