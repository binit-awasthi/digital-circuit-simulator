#ifndef PORT
#define PORT

#include "../header_files/includes.hpp"

class Port
{
    sf::CircleShape port;
    float radius;
    bool state;

    sf::Color colorTrue;
    sf::Color colorFalse;

public:
    static std::vector<Port> ports;
    static float portRadius;

    Port();

    void setState(bool);
    void updateColor();
    void setRadius(float);
    void setPosition(sf::Vector2f);
    void setOutlineColor(sf::Color);
    void setOutlineThickness(float);
    void toggleState();

    bool getState();
    float getRadius();
    sf::Vector2f getPosition();
    void drawTo(sf::RenderWindow &);

    bool isHovered(sf::RenderWindow &window);
    bool isClicked(sf::RenderWindow &window);
    bool contains(sf::Vector2f pos);

    void hoverAction(sf::RenderWindow &window);
    void clickAction(sf::RenderWindow &window);
    void duplicate();
};

#endif