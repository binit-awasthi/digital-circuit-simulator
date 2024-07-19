#ifndef WINDOW_SETTINGS
#define WINDOW_SETTINGS

#include "includes.hpp"

class FontManager
{
public:
    // int width = 700;
    // int height = 500;
    // sf::Color color = sf::Color::Black;
    // std::string title = "Logic CKT Simulator";

    // sf::ContextSettings settings;
    // int antialiasingLevel = 8;

    static sf::Image icon;

    static sf::Font font;
    static void loadAssets(sf::RenderWindow &window);
};

#endif