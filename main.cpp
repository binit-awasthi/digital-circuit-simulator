#include "./header_files/includes.hpp"
#include "./header_files/fontManager.hpp"
#include "./header_files/gate.hpp"

#include "./header_files/inputPort.hpp"
#include "./header_files/outputPort.hpp"
#include "./header_files/statusBar.hpp"
#include "./header_files/connection.hpp"
#include "./header_files/inputSignal.hpp"
#include "./header_files/outputSignal.hpp"

sf::Vector2f getMousePos(sf::RenderWindow &);

void mainLoop(sf::RenderWindow &window)
{

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
                OutputSignal::removeAll();
                InputSignal::removeAll();

                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::C)
                {
                    for (auto &gate : Gate::gates)
                    {
                        gate->deleteConnections();
                        std::cout << "deleted connection" << std::endl;
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::X)
                {
                    Gate::removeAll();
                    OutputSignal::removeAll();
                    InputSignal::removeAll();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    sf::Vector2f mousePos = getMousePos(window);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    {
                        for (auto gate : Gate::gates)
                        {
                            if (gate->contains(mousePos))
                            {
                                gate->deleteConnections();
                                break;
                            }
                        }
                        for (auto signal : OutputSignal::signals)
                        {
                            if (signal->contains(mousePos))
                            {
                                signal->deleteConnections();
                                break;
                            }
                        }
                        for (auto signal : InputSignal::signals)
                        {
                            if (signal->contains(mousePos))
                            {
                                signal->deleteConnections();
                                break;
                            }
                        }
                    }

                    else
                    {
                        Gate::removeAtPos(getMousePos(window));
                        OutputSignal::removeAtPos(getMousePos(window));
                        InputSignal::removeAtPos(getMousePos(window));
                    }
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
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
                    {
                        Gate::addGate(Gate::LOGIC_NOT, getMousePos(window));
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
                    {
                        OutputSignal::signals.push_back(new OutputSignal(getMousePos(window)));
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                    {
                        InputSignal::signals.push_back(new InputSignal(getMousePos(window)));
                    }

                    //

                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {

                        for (auto &gate : Gate::gates)
                        {
                            if (gate->contains(getMousePos(window)))
                            {
                                std::cout << "duplicate" << std::endl;
                                break;
                            }
                        }

                        for (auto signal : InputSignal::signals)
                        {
                            if (signal->contains(getMousePos(window)))
                            {
                                signal->toggleState();
                                break;
                            }
                        }
                    }

                    //

                    sf::Vector2f mousePos = getMousePos(window);

                    for (Gate *const gate : Gate::gates)
                    {
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

                    for (auto signal : InputSignal::signals)
                    {
                        if (signal->contains(mousePos))
                        {
                            isConnecting = true;
                            startPoint = signal->getPosition();

                            currentConnection.setSize(sf::Vector2f(0, 3.f));
                            currentConnection.setOrigin(0, currentConnection.getLocalBounds().height / 2);
                            currentConnection.setPosition(startPoint);
                            currentConnection.setFillColor(signal->getState() ? sf::Color::Green : sf::Color::White);
                            prevPort = signal;
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
                        for (auto gate : Gate::gates)
                        {
                            for (auto &port : gate->iPorts)
                            {
                                if (port.isConnected)
                                {
                                    continue;
                                }

                                if (port.contains(mousePos))
                                {
                                    Connection::connections.push_back(new Connection(&port, prevPort));
                                    escape = true;
                                    break;
                                }
                            }
                            if (escape)
                                break;
                        }
                        //
                        for (auto signal : OutputSignal::signals)
                        {
                            if (signal->isConnected)
                                continue;

                            if (signal->contains(mousePos))
                            {
                                Connection::connections.push_back(new Connection(signal, prevPort));
                                break;
                            }
                        }
                        //
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
            gate->drawTo(window);
        }

        for (auto signal : OutputSignal::signals)
        {
            signal->drawTo(window);
        }
        for (auto signal : InputSignal::signals)
        {
            signal->drawTo(window);
        }

        status.drawTo(window);

        window.display();
    }
}

sf::Vector2f getMousePos(sf::RenderWindow &window)
{
    return (static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
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