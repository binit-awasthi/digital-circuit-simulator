#include "./header_files/includes.hpp"
#include "./header_files/fontManager.hpp"
#include "./header_files/gate.hpp"

#include "./header_files/inputPort.hpp"
#include "./header_files/outputPort.hpp"
#include "./header_files/statusBar.hpp"
#include "./header_files/connection.hpp"

sf::Vector2f getMousePos(sf::RenderWindow &);
void displayChildren(OutputPort &oPort);
// void deleteGate(sf::RenderWindow &, std::vector<std::tuple<sf::RectangleShape, Port *, Port *>> &);
// void deleteConnections(sf::RenderWindow &window, std::vector<std::tuple<sf::RectangleShape, Port *, Port *>> &connections, Gate &gate);

void mainLoop(sf::RenderWindow &window)
{
    // bool duplicate = false;

    StatusBar status(FontManager::font);
    status.setPosition(sf::Vector2f(20.f, window.getSize().y - status.getGlobalBounds().height * 2.f));

    bool isConnecting = false;
    sf::Vector2f startPoint;

    sf::RectangleShape currentConnection;

    OutputPort *prevPort = nullptr;
    Gate *selectedGate = nullptr;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                Gate::removeAll();
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::C)
                {
                    for (auto &gate : Gate::gates)
                    {
                        // gate->clearState();
                        gate->deleteConnections();
                        std::cout << "deleted connection" << std::endl;
                    }
                    // deleteConnections(window, connections, gate);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::X)
                {
                    // for (auto &gate : Gate::gates)
                    //     deleteConnections(window, connections, gate);

                    // Gate::gates.clear();

                    Gate::removeAll();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    Gate::removeAtPos(getMousePos(window));
                    // deleteGate(window, connections);
                }

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    {
                        Gate::addGate(Gate::LOGIC_AND, getMousePos(window));
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
                    {
                        Gate::addGate(Gate::LOGIC_OR, getMousePos(window));
                    }

                    //

                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {

                        for (auto &gate : Gate::gates)
                        {
                            // if (gate->contains(getMousePos(window)))
                            // {
                            //     gate->duplicate();
                            //     selectedGate = Gate::gates.back();
                            //     duplicate = true;
                            //     break;
                            // }
                            if (gate->contains(getMousePos(window)))
                            {
                                // gate->duplicate();
                                std::cout << "duplicate" << std::endl;

                                // duplicate = true;
                                break;
                            }
                        }
                    }

                    //

                    sf::Vector2f mousePos = getMousePos(window);

                    // for (Gate *const &gate : Gate::gates)
                    for (Gate *const gate : Gate::gates)
                    {
                        // if (duplicate)
                        //     break;

                        if (gate->oPort.contains(mousePos))
                        {
                            isConnecting = true;
                            startPoint = gate->oPort.getPosition();

                            currentConnection.setSize(sf::Vector2f(0, 3.f));
                            currentConnection.setOrigin(0, currentConnection.getLocalBounds().height / 2);
                            currentConnection.setPosition(startPoint);
                            currentConnection.setFillColor(gate->oPort.getState() ? sf::Color::Green : sf::Color::White);
                            prevPort = &gate->oPort;
                            break;
                        }

                        else if (gate->contains(mousePos))
                        {
                            selectedGate = gate;
                            break;
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    selectedGate = nullptr;

                    if (isConnecting)
                    {
                        sf::Vector2f mousePos = getMousePos(window);
                        bool escape = false;
                        // for (auto &gate : Gate::gates)
                        for (auto gate : Gate::gates)
                        {
                            for (auto &port : gate->iPorts)
                            {
                                // if (port.parentPort != nullptr)
                                if (port.isConnected)
                                {
                                    continue;
                                }

                                if (port.contains(mousePos))
                                {

                                    /*
                                        sf::Vector2f endPoint = port.getPosition();
                                        sf::Vector2f vec = endPoint - startPoint;
                                        float magnitude = std::sqrt(vec.x * vec.x + vec.y * vec.y);
                                        float angle = (180.f / 3.141592f) * std::atan2(vec.y, vec.x);
                                        currentConnection.setSize(sf::Vector2f(magnitude, 3.f));
                                        currentConnection.setRotation(angle);

                                        port.setState(prevPort->getState());

                                        prevPort->childPorts.push_back(&port);
                                    */

                                    Connection::connections.push_back(new Connection(&port, prevPort));

                                    //
                                    // port.isConnected = true;
                                    // port.parentPort = prevPort;
                                    //

                                    std::cout << "port: " << &port << " parent: " << port.parentPort << " prevPort: " << &prevPort << std::endl;

                                    // prevPort = nullptr;

                                    escape = true;

                                    break;
                                }
                            }
                            if (escape)
                                break;
                        }
                        isConnecting = false;
                        prevPort = nullptr;
                    }
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                for (auto gate : Gate::gates)
                {
                    gate->hoverAction(window);
                }

                if (selectedGate != nullptr)
                {
                    selectedGate->setPosition(getMousePos(window));
                    // duplicate = false;
                }
            }

            if (isConnecting)
            {
                sf::Vector2f mousePos = getMousePos(window);
                sf::Vector2f vec = mousePos - startPoint;
                float magnitude = std::sqrt(vec.x * vec.x + vec.y * vec.y);
                float angle = (180.f / 3.141592f) * std::atan2(vec.y, vec.x);
                currentConnection.setSize(sf::Vector2f(magnitude, 3.f));
                currentConnection.setRotation(angle);
            }
        }

        status.setString("gate count: " + std::to_string(Gate::gates.size()));

        window.clear(sf::Color::Black);

        if (isConnecting)
        {
            window.draw(currentConnection);
        }

        for (auto connection : Connection::connections)
        {
            connection->drawTo(window);
        }

        for (auto gate : Gate::gates)
        {
            gate->logicOperation();
            // gate->oPort.setChildrenState();
            gate->drawTo(window);
        }

        status.drawTo(window);

        window.display();
    }

    for (auto gate : Gate::gates)
    {
        delete gate;
    }
    Gate::gates.clear();

    for (auto connection : Connection::connections)
    {
        delete connection;
    }
    Connection::connections.clear();
}

sf::Vector2f getMousePos(sf::RenderWindow &window)
{
    return (static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
}

void displayChildren(OutputPort &oPort)
{
    for (auto &port : oPort.childPorts)
    {
        std::cout << "input: " << &port << " output: " << &oPort << std::endl;
    }
}

int main()
{
    int width = 700;
    int height = 500;
    std::string title = "Logic CKT Simulator";

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(width, height), title, sf::Style::Fullscreen, settings);
    window.setFramerateLimit(60);

    FontManager::loadAssets(window);

    mainLoop(window);

    std::cout << "exited successfully" << std::endl;

    return 0;
}