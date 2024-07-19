#include "./header_files/includes.hpp"
#include "./header_files/fontManager.hpp"
#include "./header_files/gate.hpp"
// #include "./header_files/port.hpp"

#include "./header_files/inputPort.hpp"
#include "./header_files/outputPort.hpp"

// void loadAssets(sf::RenderWindow &);
sf::Vector2f getMousePos(sf::RenderWindow &);

void mainLoop(sf::RenderWindow &window)
{

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
                        Gate::gates.emplace_back(Gate::LOGIC_AND, 100.f, 50.f, getMousePos(window));
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
                    {
                        Gate::gates.emplace_back(Gate::LOGIC_OR, 100.f, 50.f, getMousePos(window));
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        for (auto &gate : Gate::gates)
        {
            gate.drawTo(window);
        }
        window.display();
    }
}

sf::Vector2f getMousePos(sf::RenderWindow &window)
{
    return (static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
}

// void loadAssets(sf::RenderWindow &window)
// {
//     win::icon.loadFromFile("./assets/images/logicIcon.png");
//     window.setIcon(win::icon.getSize().x, win::icon.getSize().y, win::icon.getPixelsPtr());
//     win::font.loadFromFile("./assets/fonts/Hack-Regular.ttf");
// }

int main()
{
    int width = 700;
    int height = 500;
    sf::Color color = sf::Color::Black;
    std::string title = "Logic CKT Simulator";

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(width, height), title, sf::Style::Default, settings);
    window.setFramerateLimit(60);

    FontManager::loadAssets(window);

    mainLoop(window);

    return 0;
}