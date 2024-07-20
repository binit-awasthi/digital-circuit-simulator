#pragma once

#include "includes.hpp"

#include "fontManager.hpp"
// #include "port.hpp"
#include "inputPort.hpp"
#include "outputPort.hpp"

class Gate
{
    sf::RectangleShape gate;

    float width;
    float height;
    sf::Color bgColor;
    sf::Color textColor;
    sf::Color bgHoverColor;
    sf::Color textHoverColor;
    sf::Color bgClickColor;
    sf::Color textClickColor;
    sf::Font font;
    sf::Vector2f pos;
    float padding;

    // status

    bool hoverStatus = false;
    bool clickStatus = false;
    bool state = false;
    bool active = false;

    sf::Text label;
    std::string type;

    sf::FloatRect bounds;

    void setText(std::string str);
    void setColor();

    // click actions
    //
    //
    // void portClickAction(sf::RenderWindow &window);
    void gateClickAction(sf::RenderWindow &window);

    // port
    float portOffset;

    // logic operations
    bool logicAnd();
    bool logicOr();
    bool logicXor();
    bool logicNot();

public:
    // gates vector
    static std::vector<Gate *> gates;

    // ports
    std::vector<InputPort> iPorts;
    OutputPort oPort;

    // statics

    // gate types
    static std::string LOGIC_AND;
    static std::string LOGIC_OR;
    static std::string LOGIC_XOR;
    static std::string LOGIC_NOT;

    // Gate(std::string type = LOGIC_AND, float width = 100.f, float height = 80.f, sf::Vector2f pos = sf::Vector2f(100, 100));
    Gate(std::string type = LOGIC_AND, sf::Vector2f pos = sf::Vector2f(100, 100));
    ~Gate();

    // setters
    void setLabel(std::string str);
    void setBgColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setFont(sf::Font font);
    void setSize(float width, float height);
    void setPosition(sf::Vector2f pos);
    void setScale(float scaleX, float scaleY);
    void setPadding(float padding);

    // getters
    sf::Color getBgColor();
    sf::Color getTextColor();
    sf::Vector2f getPosition();
    sf::FloatRect getLocalBounds();
    sf::FloatRect getGlobalBounds();

    bool isHovered(sf::RenderWindow &window);
    bool isClicked(sf::RenderWindow &window);
    bool contains(sf::Vector2f pos);

    // actions
    void logicOperation();
    //
    void hoverAction(sf::RenderWindow &window);
    void clickAction(sf::RenderWindow &window);
    void toggleState();
    void toggleColor();

    static void addGate(std::string type, sf::Vector2f pos);
    Gate duplicate();
    void drawTo(sf::RenderWindow &window);
};