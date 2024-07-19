#include "./header_files/includes.hpp"
#include "./header_files/fontManager.hpp"
#include "./header_files/gate.hpp"

#include "./header_files/inputPort.hpp"
#include "./header_files/outputPort.hpp"

sf::Vector2f getMousePos(sf::RenderWindow &);

void mainLoop(sf::RenderWindow &window)
{
    bool isConnecting = false;
    sf::Vector2f startPoint;

    // std::vector<std::tuple<sf::RectangleShape, Port *, Port *>> connections;

    sf::RectangleShape currentConnection;

    OutputPort *prevPort = nullptr;

    // Gate *selectedGate = nullptr;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    {
                        Gate::gates.push_back(Gate(Gate::LOGIC_AND, 100.f, 50.f, getMousePos(window)));
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
                    {
                        Gate::gates.push_back(Gate(Gate::LOGIC_OR, 100.f, 50.f, getMousePos(window)));
                    }
                }

                sf::Vector2f mousePos = getMousePos(window);

                for (auto &gate : Gate::gates)
                {
                    if (gate.oPort.contains(mousePos))
                    {
                        isConnecting = true;
                        startPoint = gate.oPort.getPosition();

                        currentConnection.setSize(sf::Vector2f(0, 3.f));
                        currentConnection.setOrigin(0, currentConnection.getLocalBounds().height / 2);
                        currentConnection.setPosition(startPoint);
                        currentConnection.setFillColor(sf::Color::White);
                        prevPort = &gate.oPort;
                        break;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // selectedGate = nullptr;

                    if (isConnecting)
                    {
                        sf::Vector2f mousePos = getMousePos(window);
                        bool escape = false;
                        for (auto &gate : Gate::gates)
                        {
                            for (auto &port : gate.iPorts)
                            {
                                if (port.parentPort != nullptr)
                                {
                                    std::cout << "already connected to " << port.parentPort << std::endl;
                                    continue;
                                }

                                if (port.contains(mousePos))
                                {

                                    sf::Vector2f endPoint = port.getPosition();
                                    sf::Vector2f vec = endPoint - startPoint;
                                    float magnitude = std::sqrt(vec.x * vec.x + vec.y * vec.y);
                                    float angle = (180.f / 3.141592f) * std::atan2(vec.y, vec.x);
                                    currentConnection.setSize(sf::Vector2f(magnitude, 3.f));
                                    currentConnection.setRotation(angle);

                                    port.setState(prevPort->getState());

                                    prevPort->childPorts.push_back(&port);
                                    port.parentPort = prevPort;

                                    std::cout << "connected to " << port.parentPort << std::endl;

                                    prevPort = nullptr;

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

        window.clear(sf::Color::Black);

        if (isConnecting)
        {
            window.draw(currentConnection);
        }

        for (auto &gate : Gate::gates)
        {
            gate.logicOperation();
            gate.drawTo(window);
        }

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

    sf::RenderWindow window(sf::VideoMode(width, height), title, sf::Style::Default, settings);
    window.setFramerateLimit(60);

    FontManager::loadAssets(window);

    mainLoop(window);

    return 0;
}