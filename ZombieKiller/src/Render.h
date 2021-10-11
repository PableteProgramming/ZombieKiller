#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

void DrawMap(std::vector<std::string>, std::vector<std::pair<std::string, int*>>,int,sf::RenderWindow&);