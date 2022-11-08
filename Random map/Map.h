#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define WINDOW_X 1920
#define WINDOW_Y 1080
#define SCALE 4

#define MOUNTAIN 0.43f
#define WATER 0.f

class Map
{
private:
	int width, height;
	double** land;
	double** temperature;
	double** wet;
	bool** line;
	int howRiver;
	std::vector <sf::Vector2f>* rivers;
	sf::Image bioms;
	sf::Image map;
	int sideLength;
	void makeRiver(std::vector<sf::Vector2f>* rivers, int& myRiver, int direction, int x, int y);
	bool  bit(int x, int y);
	void noiseGenerator(int octave, double persistence, double frequency, double startAmplitude, float multiFreq, double** array_);
	void gradientNoise(int start, int end, double** array_);
	void generateLand();
	void generateTemperature();
	void generateWet();
	void generateBioms();
	void generateRiver();
	Map(const Map& map);
public:
	std::string getInformation(sf::Vector2f position);
	std::string getNormalInformation(sf::Vector2f position);
	void saveInFile(const char* path);
	void generateMap();
	void renderBioms(sf::RenderWindow& window);
	void renderLand(sf::RenderWindow& window);
	void renderWet(sf::RenderWindow& window);
	void renderRiver(sf::RenderWindow& window);
	void renderTemperature(sf::RenderWindow& window);
	Map(int width, int height);
	~Map();
};

