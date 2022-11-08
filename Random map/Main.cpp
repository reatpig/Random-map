#include <SFML/Graphics.hpp>

#include "Map.h"
void render(Map& map, sf::RenderWindow& window, unsigned int mode);
int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y,32),"Random map");
	window.setFramerateLimit(30);
	srand(time(0));

	Map map(WINDOW_X / SCALE, WINDOW_Y/ SCALE);
	map.generateMap();

	sf::Font font;
	font.loadFromFile("ARIALN.TTF");
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(1);
	text.setCharacterSize(20);
	
	unsigned int mode=0;
	while (window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				map.saveInFile("Map.jpg");
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					mode=(mode+1)%4;
			}
			if (event.type == sf::Event::MouseMoved) {
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				if(!(mousePos.x<0||mousePos.y<0||mousePos.x>=WINDOW_X  || mousePos.y>=WINDOW_Y ))
				text.setString( map.getNormalInformation(mousePos));
				text.setPosition(mousePos+sf::Vector2f(0,-20));	
			}
			window.clear();
			render(map, window, mode);
			window.draw(text);
			window.display();
		}
	}
	return 0;
}


void render(Map&map, sf::RenderWindow& window, unsigned int mode) {
	switch (mode)
	{
	case 0:
		map.renderBioms(window);
		break;
	case 1:
		map.renderTemperature(window);
		break;
	case 2:
		map.renderWet(window);
		break;
	case 3:
		map.renderLand(window);
	default:
		break;
	}
}