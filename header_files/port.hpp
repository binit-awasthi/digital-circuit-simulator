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
    // static Port *prevPort;
    // static sf::RectangleShape currentConnection;
    // static sf::Vector2f startPoint;
    // static bool isConnecting;
    // static Port *selected;
    static float portRadius;

    // bool moving;

    Port();

    void setState(bool);
    // void setBgColor(sf::Color);
    void updateColor();
    void setRadius(float);
    void setPosition(sf::Vector2f);
    void toggleState();

    bool getState();
    // sf::Color getBgColor();
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