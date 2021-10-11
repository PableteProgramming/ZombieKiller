#include "Render.h"

void DrawMap(std::vector<std::string> map, std::vector<std::pair<std::string, int*>> colors,int cellsize,sf::RenderWindow& window) {
	for (int i = 0; i < map.size(); i++) {
		for (int k = 0; k < map[i].size(); k++) {
			for (int z = 0; z < colors.size(); z++) {
				if (colors[z].first == std::string(1, map[i][k])) {
					sf::RectangleShape rect;
					rect.setOrigin(k*cellsize,i*cellsize);
					std::cout << "origin: x("<<k*cellsize<<");y("<<i*cellsize<<")" << std::endl;
					sf::Color color((colors[z].second)[0], (colors[z].second)[1],(colors[z].second)[2]);
					rect.setFillColor(color);
					rect.setSize(sf::Vector2f(cellsize,cellsize));
					window.draw(rect);
					break;
				}
			}
		}
	}
}