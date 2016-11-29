#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <sstream>

extern std::string debug_string;

std::string toString(int);
std::string toString(sf::Vector2i);
void debugString(std::string, sf::RenderWindow &, sf::Font &);
