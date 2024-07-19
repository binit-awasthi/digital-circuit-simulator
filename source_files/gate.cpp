#include "../header_files/gate.hpp"

std::string Gate::LOGIC_AND = "AND";
std::string Gate::LOGIC_OR = "OR";
std::string Gate::LOGIC_XOR = "XOR";
std::string Gate::LOGIC_NOT = "NOT";
std::vector<Gate> Gate::gates;

Gate::Gate(std::string type, float width, float height, sf::Vector2f pos)
{
    this->type = type;

    // Port p1;
    // Port p2;
    // p2.setState(true);

    iPorts.emplace_back(InputPort());
    iPorts.emplace_back(InputPort());

    setColor();

    padding = 20.f;

    portOffset = Port::portRadius * 4;

    setSize(width, height);
    setText(type);

    gate.setOrigin(gate.getLocalBounds().width / 2, gate.getLocalBounds().height / 2);
    label.setOrigin(label.getLocalBounds().width / 2, label.getLocalBounds().height / 2);

    setPosition(pos);

    setBgColor(bgColor);
    setTextColor(textColor);
}

void Gate::setPosition(sf::Vector2f pos)
{
    this->pos = pos;

    gate.setPosition(pos);
    label.setPosition(sf::Vector2f(pos.x - 1, pos.y - 2));

    iPorts[0].setPosition(sf::Vector2f(pos.x - width / 2, pos.y - (height / 2) + Port::portRadius * 2));
    for (int i = 1; i < iPorts.size(); i++)
    {
        iPorts[i].setPosition(sf::Vector2f(pos.x - width / 2, iPorts[i - 1].getPosition().y + portOffset));
    }

    oPort.setPosition(sf::Vector2f((pos.x + width / 2), pos.y - (height / 2) + Port::portRadius * 2));
}

void Gate::setSize(float width, float height)
{
    this->width = width;
    this->height = height;
    gate.setSize(sf::Vector2f(width, height));
}

void Gate::setText(std::string str)
{

    // if (!font.loadFromFile("./assets/fonts/Hack-Regular.ttf"))
    // {
    //     std::cout << "Failed to load font" << std::endl;
    // }

    label.setFont(FontManager::font);
    // label.setFont(font);
    label.setCharacterSize(15);
    label.setString(str);
}

void Gate::setColor()
{
    // initial
    bgColor = sf::Color(255, 255, 255, 100);
    textColor = sf::Color::Black;

    // hovered
    bgHoverColor = sf::Color(255, 255, 255, 120);
    textHoverColor = sf::Color::Green;

    // clicked
    bgClickColor = sf::Color::Blue;
    textClickColor = sf::Color::Green;
}

void Gate::drawTo(sf::RenderWindow &window)
{
    window.draw(gate);
    window.draw(label);

    for (auto &port : iPorts)
    {
        port.drawTo(window);
    }
    oPort.drawTo(window);
}

void Gate::setLabel(std::string str)
{
    label.setString(str);
    // setSize();
}

void Gate::setBgColor(sf::Color color)
{
    bgColor = color;
    gate.setFillColor(bgColor);
}
void Gate::setTextColor(sf::Color color)
{
    textColor = color;
    label.setFillColor(textColor);
}

void Gate::setFont(sf::Font &font)
{
    label.setFont(font);
}

sf::Vector2f Gate::getPosition()
{
    return pos;
}

void Gate::setPadding(float padding)
{
    this->padding = padding;
    setSize(width, height);
}

void Gate::setScale(float scaleX, float scaleY)
{
    gate.setScale(scaleX, scaleY);
    label.setScale(scaleX, scaleY);
}

sf::Color Gate::getBgColor()
{
    return bgColor;
}
sf::Color Gate::getTextColor()
{
    return textColor;
}

bool Gate::isHovered(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    hoverStatus = gate.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

    return hoverStatus;
}

void Gate::hoverAction(sf::RenderWindow &window)
{
    if (isHovered(window))
    {
        gate.setOutlineColor(sf::Color::White);
        gate.setOutlineThickness(1);
        // std::cout << "gate: hovered" << std::endl;
    }
    else
    {
        gate.setOutlineThickness(0);
        // std::cout << "gate: not hovered" << std::endl;
    }
}

bool Gate::isClicked(sf::RenderWindow &window)
{
    if (!isHovered(window))
        return false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return true;

    return false;
}

void Gate::clickAction(sf::RenderWindow &window)
{
    // gateClickAction();
    portClickAction(window);
}

void Gate::portClickAction(sf::RenderWindow &window)
{

    if (type == LOGIC_AND)
        oPort.setState(logicAnd());

    else if (type == LOGIC_OR)
        oPort.setState(logicOr());

    else if (type == LOGIC_XOR)
        oPort.setState(logicXor());

    else if (type == LOGIC_NOT)
        oPort.setState(logicNot());
}

void Gate::gateClickAction(sf::RenderWindow &window)
{
    if (isClicked(window))
    {
        toggleState();
        std::cout << "state: " << state << std::endl;
        toggleColor();
    }
}

void Gate::toggleState()
{
    // !clickStatus;
    state = !state;
}

void Gate::toggleColor()
{
    if (state)
    {
        setBgColor(sf::Color::Green);
    }
    else
    {
        setBgColor(sf::Color::Red);
    }
}

bool Gate::logicAnd()
{
    bool state = true;
    for (auto &port : iPorts)
    {
        state = state && port.getState();
    }

    return state;
}

bool Gate::logicOr()
{
    bool state = false;
    for (auto &port : iPorts)
    {
        state = state || port.getState();
    }

    return state;
}

bool Gate::logicXor()
{
    bool state = false;
    for (auto &port : iPorts)
    {
        state = state != port.getState();
    }

    return state;
}

bool Gate::logicNot()
{
    if (!iPorts.empty())
    {
        return !iPorts[0].getState();
    }
    return false;
}

bool Gate::contains(sf::Vector2f pos)
{
    return (gate.getGlobalBounds().contains(pos)) ? true : false;
}

Gate Gate::duplicate()
{
    return *this;
}

sf::FloatRect Gate::getGlobalBounds()
{
    return gate.getGlobalBounds();
}
sf::FloatRect Gate::getLocalBounds()
{
    return gate.getLocalBounds();
}