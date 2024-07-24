#include "../header_files/outputSignal.hpp"

std::vector<OutputSignal *> OutputSignal::signals;

OutputSignal::OutputSignal(sf::Vector2f pos)
{
    this->setPosition(pos);
}

OutputSignal::~OutputSignal()
{
    delete this;
}

void OutputSignal::deleteConnections()
{

    for (auto conIt = Connection::connections.begin(); conIt != Connection::connections.end();)
    {
        auto con = *conIt;

        if (con->ip == this)
        {
            for (auto it = parentPort->childPorts.begin(); it != parentPort->childPorts.end();)
            {
                auto port = *it;
                if (port == this)
                {
                    it = parentPort->childPorts.erase(it);
                    break;
                }
                ++it;
            }
            conIt = Connection::connections.erase(conIt);
            //
            this->isConnected = false;
            this->setState(false);
            // this->updateColor();
            //
            break;
        }
        ++conIt;
    }
}

void OutputSignal::removeAtPos(sf::Vector2f pos)
{

    for (auto it = signals.begin(); it != signals.end();)
    {
        auto sig = *it;

        if (sig->contains(pos))
        {
            sig->deleteConnections();
            it = signals.erase(it);
            break;
        }
        ++it;
    }
}

void OutputSignal::removeAll()
{
    for (auto signal : signals)
    {
        signal->deleteConnections();
    }
    signals.clear();
}
