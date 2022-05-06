#include <SFML/Graphics.hpp>
#include "C:/Users/Timofey/source/repos/Bmp/Bmp/Image.h"
#include "Map.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y,32),"Random map");
	
	window.setFramerateLimit(30);
	Map map(WINDOW_X / SCALE, WINDOW_Y/ SCALE);
	//srand(time(0));
	map.generateLand();  
	
	map.generateTemperature();
	map.generateWet();
	//map.generateRiver();
	map.generateBioms();
//	map.generateRiver();

	sf::Font font;
	font.loadFromFile("ARIALN.TTF");
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(1);
	text.setCharacterSize(20);
	
	sf::Vector2f start;
	
	while (window.isOpen())
	{
		
		sf::Event event;
		window.pollEvent(event);
		{

			if (event.type == sf::Event::Closed) {
				Image image(WINDOW_X / SCALE, WINDOW_Y / SCALE);
			
				map.setImage(image);

				image.Export("Map.bmp");

				window.close();
			}
			window.clear();


			//if (event.key.shift)
		    map.renderBioms(window);
			//map.renderRiver(window);
			//map.renderTemperature(window);
			//map.renderWet(window);
			//map.renderLand(window);
			
			if (event.type == sf::Event::MouseMoved) {
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				if(mousePos.x<0||mousePos.y<0||mousePos.x>=WINDOW_X / SCALE || mousePos.y>=WINDOW_Y / SCALE)
				text.setString( map.getNormalInformation(mousePos));
				text.setPosition(mousePos+sf::Vector2f(0,-20));
				window.draw(text);

			}
			else if (event.type == sf::Event::MouseLeft) {

			}
			else if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
					start = window.mapPixelToCoords(sf::Mouse::getPosition(window));

				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
					sf::Vector2f end = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					map.setFrame(start, end);
				}
			}
			
			window.display();
		}
	}
	return 0;
}