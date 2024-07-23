#include "../header_files/gate.hpp"

std::string Gate::LOGIC_AND = "AND";
std::string Gate::LOGIC_OR = "OR";
std::string Gate::LOGIC_XOR = "XOR";
std::string Gate::LOGIC_NOT = "NOT";
std::vector<Gate *> Gate::gates;
int Gate::count;

Gate::Gate(std::string type, sf::Vector2f pos)
{
    width = 100.f;
    height = 50.f;
    this->type = type;

    iPorts.push_back(InputPort());
    iPorts.push_back(InputPort());

    iPorts.front().setState(true);

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

    // iPorts[0].setPosition(sf::Vector2f(pos.x - width / 2, pos.y - (height / 2) + Port::portRadius * 2));

    iPorts.front().setPosition(sf::Vector2f(pos.x - width / 2, pos.y - (height / 2) + Port::portRadius * 2));

    for (size_t i = 1; i < iPorts.size(); ++i)
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
    label.setFont(FontManager::font);
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

    for (auto &ip : iPorts)
    {
        ip.drawTo(window);
    }

    // oPort.setChildrenState();
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

void Gate::setFont(sf::Font font)
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
    logicOperation();
}

void Gate::logicOperation()
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
        state = (state && port.getState());
    }

    return state;
}

bool Gate::logicOr()
{
    bool state = false;
    for (auto &port : iPorts)
    {
        state = (state || port.getState());
    }

    return state;
}

bool Gate::logicXor()
{
    bool state = false;
    for (auto &port : iPorts)
    {
        state = (state != port.getState());
    }

    return state;
}

bool Gate::logicNot()
{
    if (!iPorts.empty())
    {
        return !(iPorts[0].getState());
    }
    return false;
}

bool Gate::contains(sf::Vector2f pos)
{
    return (gate.getGlobalBounds().contains(pos)) ? true : false;
}

std::string Gate::getType()
{
    return type;
}

// void Gate::duplicate()
// {
//     addGate(this->getType(), this->getPosition());
//     // gates.push_back(new Gate(this->type, this->getPosition()));
//     // return dup;
// }

sf::FloatRect Gate::getGlobalBounds()
{
    return gate.getGlobalBounds();
}

sf::FloatRect Gate::getLocalBounds()
{
    return gate.getLocalBounds();
}

void Gate::addGate(std::string type, sf::Vector2f pos)
{
    gates.push_back(new Gate(type, pos));
    count++;
}

Gate::~Gate()
{
    delete this;
    count--;
    std::cout << "deleted: gate" << std::endl
              << "gate count: " << Gate::getCount() << std::endl
              << std::endl;
}

int Gate::getCount()
{
    return gates.size();
    // return count;
}

void Gate::removeGate(Gate *gateToRemove)
{
    for (auto gateIt = gates.begin(); gateIt != gates.end();)
    {
        if (*gateIt == gateToRemove)
        {
            // deleteConnections(window, connections, gate);

            // delete *gateIt;
            gateIt = gates.erase(gateIt);
            // std::cout << "Deleted: gate" << std::endl;
            break;
        }
        else
        {
            ++gateIt;
        }
    }
}

void Gate::removeAtPos(sf::Vector2f pos)
{

    for (auto gateIt = gates.begin(); gateIt != gates.end();)
    {

        auto gate = *gateIt;

        if (gate->contains(pos))
        {
            gate->deleteConnections();
            // delete *gateIt;
            gateIt = gates.erase(gateIt);
            // std::cout << "gate deleted successfully" << std::endl;
            break;
        }
        else
        {
            ++gateIt;
        }
    }
}

void Gate::removeAll()
{
    for (Gate *gate : gates)
    {
        gate->deleteConnections();
        // delete gate;
    }
    gates.clear();
    std::cout << "all gates deleted successfully and cleared" << std::endl;
}

void Gate::clearState()
{
    for (auto &port : iPorts)
    {
        port.setState(false);
    }

    // oPort.setState(false);
    logicOperation();
}

void Gate::deleteConnections()
{
    try
    {
        // First remove connections related to the output port
        for (auto conIt = Connection::connections.begin(); conIt != Connection::connections.end();)
        {
            auto con = *conIt;
            if (con->op == &this->oPort)
            {
                // delete con;
                conIt = Connection::connections.erase(conIt);
                // std::cout << "deleted: connection" << std::endl;
            }
            else
            {
                ++conIt;
            }
        }

        // Then remove connections related to the input ports
        for (auto conIt = Connection::connections.begin(); conIt != Connection::connections.end();)
        {
            auto con = *conIt;
            bool found = false;
            for (auto &port : this->iPorts)
            {
                if (con->ip == &port)
                {
                    found = true;
                    // con =nullptr;
                    // delete con;
                    conIt = Connection::connections.erase(conIt);
                    std::cout << "deleted: connection" << std::endl;
                    port.isConnected = false;
                    port.parentPort = nullptr;
                    port.setState(false);
                    break;
                }
            }
            if (!found)
            {
                ++conIt;
            }
        }

        logicOperation();

        // Clear child ports of the output port
        for (auto port : this->oPort.childPorts)
        {
            port->parentPort = nullptr;
            port->setState(false);
            port->isConnected = false;
        }

        this->oPort.childPorts.clear();
    }
    catch (...)
    {
        std::cout << "error occurred" << std::endl;
    }
}
