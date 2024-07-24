#pragma once
#include "includes.hpp"
#include "button.hpp"
#include "gate.hpp"
#include "inputSignal.hpp"
#include "outputSignal.hpp"

class Component
{
    float posx;
    float posy;
    float offsetX;
    float offsetY;

public:
    Component(sf::RenderWindow &window);
    static std::vector<Button> components;
    static int newComponent(Button comp, sf::Vector2f pos);
    void setPosition();
    static void drawTo(sf::RenderWindow &);
};
