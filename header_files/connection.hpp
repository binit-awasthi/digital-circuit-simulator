#pragma once

#include "includes.hpp"
#include "inputPort.hpp"
#include "outputPort.hpp"
#include "gate.hpp"

class Connection
{
    sf::RectangleShape connection;
    void connect();
    void drawConnection();
    // static void deleteConnections(Gate *);

public:
    static std::vector<Connection *> connections;
    InputPort *ip;
    OutputPort *op;
    Connection(InputPort *, OutputPort *);
    // ~Connection();
    void drawTo(sf::RenderWindow &window);
    void updateState();
    // static void drawConnections(sf::RenderWindow &window);
};