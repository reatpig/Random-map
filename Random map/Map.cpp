#include "Map.h"
#include <math.h>
#include <random>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
std::string Map::getInformation(sf::Vector2f position)
{
	std::string s;
	sf::Color c = bioms.getPixel(position.x / sideLength, position.y / sideLength);
	if (c == sf::Color(50, 50, 50))//Горы
		s.assign("Mountain");
	else if (c == sf::Color(0, 117, 100))//Дождевой тропический лес
		s.assign("Tropical rainforest");
	else if (c== sf::Color(0, 117, 67)) //Тропический лес
		s.assign("Tropical forest");
	else if (c== sf::Color(172, 167, 25))//Саванны
		s.assign("Savannah");
	else if (c== sf::Color(222, 184, 135))//Пустыня
		s.assign("Desert");
	else if (c== sf::Color(164, 218, 140))//Дождевой лес умеренной зоны
		s.assign("Temperate rainforest");
	else if (c == sf::Color(164, 218, 68)) //Лес умеренной зоны
		s.assign("Temperate forest");
	else if (c == sf::Color(175, 242, 6))//Равнина
		s.assign("Plain");
	else if (c== sf::Color(0, 109, 100))//Тайга
		s.assign("Taiga");
	else if (c== sf::Color(255, 255, 255))//Тундра
		s.assign("Tundra");
	else s.assign("Water");

	s += ' ';
	s.append(std::to_string(land[(int)position.x / sideLength][(int)position.y / sideLength]));
	s += ' ';
	s.append(std::to_string(temperature[(int)position.x / sideLength][(int)position.y / sideLength]));
	s += ' ';
	s.append(std::to_string(wet[(int)position.x / sideLength][(int)position.y / sideLength]));
	return s;

}
std::string Map::getNormalInformation(sf::Vector2f position)
{
	std::string s;
	sf::Color c =bioms.getPixel(position.x / sideLength, position.y / sideLength);
	if (c == sf::Color(50, 50, 50))//Горы
		s.assign("Mountain");
	else if (c== sf::Color(0, 117, 85))//Дождевой тропический лес
		s.assign("Tropical rainforest");
	else if (c== sf::Color(0, 117, 67)) //Тропический лес
		s.assign("Tropical forest");
	else if (c == sf::Color(172, 167, 25))//Саванны
		s.assign("Savannah");
	else if (c== sf::Color(222, 184, 135))//Пустыня
		s.assign("Desert");
	else if (c== sf::Color(164, 218, 140))//Дождевой лес умеренной зоны
		s.assign("Temperate rainforest");
	else if (c == sf::Color(164, 218, 68)) //Лес умеренной зоны
		s.assign("Temperate forest");
	else if (c == sf::Color(175, 242, 6))//Равнина
		s.assign("Plain");
	else if (c== sf::Color(0, 109, 120))//Тайга
		s.assign("Taiga");
	else if (c== sf::Color(255, 255, 255))//Тундра
		s.assign("Tundra");
	else if (c== sf::Color(60, 80, 120))//Кустарники
		s.assign("Shrubs");
	else s.assign("Water");

	s += " h=";
	s.append(std::to_string((land[(int)position.x / sideLength][(int)position.y / sideLength])*8500));
	s += " t=";
	s.append(std::to_string(temperature[(int)position.x / sideLength][(int)position.y / sideLength]*66.6f-10.f));
	s += " w=";
	s.append(std::to_string(wet[(int)position.x / sideLength][(int)position.y / sideLength]*3500));
	return s;

}

void Map::renderBioms(sf::RenderWindow& window)
{
	sf::Sprite s;
	sf::Texture t;
	map = bioms;
	for (int i = 0; i < width; ++i)
		for (int r = 0; r < height; ++r)
			if (line[i][r])
				map.setPixel(i, r, sf::Color::Black);
	t.loadFromImage(map);
	s.setTexture(t);
	s.scale(sf::Vector2f(SCALE, SCALE));
	window.draw(s);
}
void Map::renderLand(sf::RenderWindow& window)
{
	for (int i = 0; i < width; ++i)
		for (int r = 0; r < height; ++r) {
			if (line[i][r])
				map.setPixel(i, r, sf::Color::Black);
			 else if(land[i][r]<WATER)
				map.setPixel(i, r, sf::Color(0,0,255*(land[i][r]+1)/2));
			else if (land[i][r] < 0.08f)
				map.setPixel(i, r, sf::Color::Yellow);
			else if (land[i][r] < 0.225f)
				map.setPixel(i, r, sf::Color::Green);
			else if (land[i][r] < MOUNTAIN)
				map.setPixel(i, r, sf::Color(0, 95, 55));
			else if (land[i][r] < 0.55f)
				map.setPixel(i, r, sf::Color(101, 94, 93));
			else 
				map.setPixel(i, r, sf::Color::White);
		}
	sf::Sprite s;
	sf::Texture t;
	t.loadFromImage(map);
	s.setTexture(t);
	s.scale(sf::Vector2f(SCALE, SCALE));
	window.draw(s);
}
void Map::renderRiver(sf::RenderWindow & window)
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Blue);
	rect.setSize(sf::Vector2f(sideLength, sideLength));
	for (int i = 0; i < howRiver; ++i)
		for (auto coor:rivers[i]) {	
			rect.setPosition(coor.x*sideLength, coor.y*sideLength);
			window.draw(rect);
		}
}
void Map::renderTemperature(sf::RenderWindow& window)
{
	for (int i = 0; i < width; ++i)
		for (int r = 0; r < height; ++r) {
			if (line[i][r])
				map.setPixel(i, r, sf::Color::Black);
			else
			map.setPixel(i,r,sf::Color(255 * (temperature[i][r]), 10., 10.));
		}
	sf::Sprite s;
	sf::Texture t;
	t.loadFromImage(map);
	s.setTexture(t);
	s.scale(sf::Vector2f(SCALE, SCALE));
	window.draw(s);
}
void Map::renderWet(sf::RenderWindow& window)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(sideLength, sideLength));
	for (int i = 0; i < width; ++i)
		for (int r = 0; r < height; ++r) {
			if (line[i][r])
				map.setPixel(i, r, sf::Color::Black);
			else map.setPixel(i,r,sf::Color(0, 0, 255 * wet[i][r]));
		}
	sf::Sprite s;
	sf::Texture t;
	t.loadFromImage(map);
	s.setTexture(t);
	s.scale(sf::Vector2f(SCALE, SCALE));
	window.draw(s);
}

int type(double value) 
{
	if (value < WATER)
		return 0;
	if (value < 0.08f)
		return 1;
	if (value < 0.225f)
		return 2;
	if (value < MOUNTAIN)
		return 3;
	if (value < 0.55f)
		return 4;
	else return 5;
}
bool  Map::bit(int x, int y) 
{
	double right;
	if (x + 1 < width)
		right = land[x + 1][y];
	else right = land[x][y];
	double left;
	if (x - 1 >= 0)
		left = land[x - 1][y];
	else left = land[x][y];
	double down;
	if (y + 1 < height)
		down = land[x][y + 1];
	else down = land[x][y];
	double up;
	if (y - 1 >= 0)
		up = land[x][y - 1];
	else up = land[x][y];

	int count = 0;
	if (type(up) == type(up) || land[x][y] < up)
		count += 1;
	if (type(right) == type(up) || land[x][y] < right)
		count += 2;
	if (type(down) == type(up) || land[x][y] < down)
		count += 4;
	if (type(left) == type(up) || land[x][y] < left)
		count += 8;

	return count == 15;

}
double Dot(sf::Vector2f a, double  b)
{
	return a.x * cos(b) + a.y * sin(b);
}
static double QunticCurve(double t)
{
	 return t * t * t * (t * (t * 6 - 15) + 10);
}
double Lerp(double a, double b, double t) {
	 return a + (b - a) * t;
}

double PerliNoise(sf::Vector2<double> point, double** vectors, int width, int height)
{
	 int howX = point.x / width;
	 point.x -= width * howX;

	 int howY = point.y / height;
	 point.y -= height * howY;

	 int left = (int)point.x;
	 int top = (int)point.y;
	 int nextLeft = left + 1;
	 if (nextLeft >= width)
		 nextLeft = 0;

	 sf::Vector2f pointInQuad(point.x - left, point.y - top);

	 sf::Vector2f distanceToTopLeft(pointInQuad.x, pointInQuad.y);
	 sf::Vector2f distanceToTopRight(pointInQuad.x - 1, pointInQuad.y);
	 sf::Vector2f distanceToBottomLeft(pointInQuad.x, pointInQuad.y - 1);
	 sf::Vector2f distanceToBottomRight(pointInQuad.x - 1, pointInQuad.y - 1);
	 /*
		  tx1--tx2
		   |    |
		  bx1--bx2
		 */

	 double tx1 = Dot(distanceToTopLeft, vectors[left][top]);
	 double tx2 = Dot(distanceToTopRight, vectors[nextLeft][top]);
	 double bx1 = Dot(distanceToBottomLeft, vectors[left][top + 1]);
	 double bx2 = Dot(distanceToBottomRight, vectors[nextLeft][top + 1]);

	 pointInQuad.x = QunticCurve(pointInQuad.x);
	 pointInQuad.y = QunticCurve(pointInQuad.y);
	 double tx = Lerp(tx1, tx2, pointInQuad.x);
	 double bx = Lerp(bx1, bx2, pointInQuad.x);
	 double tb = Lerp(tx, bx, pointInQuad.y);

	 return tb;
}

bool findTitle(std::vector<sf::Vector2f>* rivers, int& myRiver,int x, int y) {
	 for (int i = 0; i < myRiver; ++i)
		 for (auto iter = rivers[i].begin(); iter != rivers[i].end(); ++iter)
			 if (*iter == sf::Vector2f(x, y)) {
				 rivers[i].insert(rivers[i].end(), rivers[myRiver].begin(), rivers[myRiver].end());
				 rivers[myRiver].clear();
				 myRiver--;
				 return true;
			 }
	 return false;
}
void Map::makeRiver(std::vector<sf::Vector2f>* rivers, int& myRiver, int direction, int x, int y)
{
	 if (land[x][y] < 0 || findTitle(rivers, myRiver, x, y))
		 return;

	 rivers[myRiver].push_back(sf::Vector2f(x, y));
	 bioms.setPixel(x, y, sf::Color::Cyan);
	 if (rivers[myRiver].size() > width * height / 1000)
		 return;

	 double right;
	 if (x + 1 < width)
		 right = land[x + 1][y];
	 else right = std::numeric_limits<double>::max();
	 double left;
	 if (x - 1 >= 0)
		 left = land[x - 1][y];
	 else left = std::numeric_limits<double>::max();
	 double down;
	 if (y + 1 < height)
		 down = land[x][y + 1];
	 else down = std::numeric_limits<double>::max();
	 double up;
	 if (y - 1 >= 0)
		 up = land[x][y - 1];
	 else up = std::numeric_limits<double>::max();

	 switch (direction)
	 {
	 case 0:
		 right = std::numeric_limits<double>::max();
		 break;
	 case 1:
		 left = std::numeric_limits<double>::max();
		 break;
	 case 2:
		 down = std::numeric_limits<double>::max();
		 break;
	 case 3:
		 up = std::numeric_limits<double>::max();
		 break;
	 }

	 std::vector<double> v;
	 v.push_back(left);
	 v.push_back(right);
	 v.push_back(up);
	 v.push_back(down);

	 double min = v[0];
	 int minI = 0;
	 for (int iter = 1; iter < v.size(); ++iter)
		 if (v[iter] < min) {
			 min = v[iter];
			 minI = iter;
		 }

	 if ((v[direction] - v[minI]) > 0.00625f)
		 direction = minI;

	 switch (direction)
	 {
	 case 0:
		 makeRiver(rivers, myRiver, direction, x - 1, y);
		 break;
	 case 1:
		 makeRiver(rivers, myRiver, direction, x + 1, y);
		 break;
	 case 2:
		 makeRiver(rivers, myRiver, direction, x, y - 1);
		 break;
	 case 3:
		 makeRiver(rivers, myRiver, direction, x, y + 1);
		 break;
	 }
}
void Map::noiseGenerator(int octave, double persistence, double frequency, double startAmplitude, float multiFreq, double** array_)
{
	 for (int i = 0; i < width; ++i)
		 for (int r = 0; r < height; ++r)
			 array_[i][r] = 0;

	 int vectorWidth = width;//int(width / octave *100)+2;
	 int vectorHeight = height + 1;//int(height / octave*100 )+2;
	 double** vectors = new double* [vectorWidth];
	 for (int i = 0; i < vectorWidth; ++i)
		 vectors[i] = new double[vectorHeight];

	 for (int i = 0; i < vectorWidth; ++i)
		 for (int r = 0; r < vectorHeight; ++r)
			 vectors[i][r] = ((double)rand() / (double)RAND_MAX * 2 * std::_Pi);

	 double maxValue = std::numeric_limits<double>::max();
	 double minvValue = -std::numeric_limits<double>::max();;
	 for (int i = 0; i < width; ++i)
		 for (int r = 0; r < height; ++r) {
			 double amplitude = startAmplitude;//1
			 double freq = frequency;// 0.025;
			 for (int f = 0; f < octave; ++f) {
				 array_[i][r] += PerliNoise(sf::Vector2<double>(i, r) * freq / (double)octave, vectors, width, height) * amplitude;
				 amplitude *= persistence;
				 freq *= multiFreq;//3;
			 }

			 if (array_[i][r] > maxValue)
				 maxValue = array_[i][r];
			 if (array_[i][r] < minvValue)
				 minvValue = array_[i][r];

			 if (array_[i][r] > 1)
				 array_[i][r] = 1;
			 if (array_[i][r] < -1)
				 array_[i][r] = -1;
		 }
	 for (int i = 0; i < vectorWidth; ++i)
		 delete[] vectors[i];
	 delete	vectors;
}
void Map::gradientNoise(int start, int end, double** array_)
{
	 double dx = (double)1 / (end - start);
	 for (int r = 0; r < height / 2; ++r) {
		 double d = dx * (r - start);
		 if (d > 1)
			 d = 1;
		 else if (d < 0)
			 d = 0;
		 for (int i = 0; i < width; ++i) {
			 array_[i][r] = d;
			 array_[i][height - r - 1] = d;
		 }
	 }
}

void Map::generateLand()
{
	 noiseGenerator(6, 0.5, 0.06, 1, 3, land);//Default (6, 0.5, 0.08, 1, 3,land)
	 for (int i = 0; i < width; ++i)
		 for (int r = 0; r < height; ++r)
			 line[i][r] = !bit(i, r);
}

void Map::generateTemperature()
{
	 double** gradient = new double* [width];
	 for (int i = 0; i < width; ++i)
		 gradient[i] = new double[height];

	 gradientNoise(0, height / 1.2, gradient);
	 noiseGenerator(6, 0.5, 0.3, 1, 2, temperature);

	 for (int i = 0; i < width; ++i)
		 for (int r = 0; r < height; ++r) {
			 double d = (temperature[i][r] / 3 + gradient[i][r] * 3) / 2.5;
			 d -= land[i][r] / 5;
			 d += 0.06;
			 if (d < 0) d = 0;
			 else if (d > 1) d = 1;
			 temperature[i][r] = d;
		 }

	 for (int i = 0; i < width; ++i)
		 delete[] gradient[i];
	 delete[] gradient;
}
void Map::generateWet()
{
	noiseGenerator(6, 0.2, 0.12, 1, 3, wet);
	for (int i = 0; i < width; ++i)
		for (int r = 0; r < height; ++r) {
			double d = (wet[i][r] * 2 + 1) / 2;
			double x = temperature[i][r];
			d += -2. * x * x + 2. * 1. * x - 0.4;
			if (d < 0) d = 0;
			if (d > 1) d = 1;
			wet[i][r] = d;
		}
}
void Map::saveInFile(const char* path)
{
	 map.saveToFile(path);
}
void Map::generateBioms()
{
	 for (int i = 0; i < width; ++i)
		 for (int r = 0; r < height; ++r) {
			 if (land[i][r] > 0.6)
				 bioms.setPixel(i, r, sf::Color(255, 255, 255));//Снег
			 else if (land[i][r] > MOUNTAIN)
				 bioms.setPixel(i, r, sf::Color(50, 50, 50));//Горы	 
			 else if (land[i][r] < WATER)
				 bioms.setPixel(i, r, sf::Color(0, 0, 255 * (land[i][r] + 1) / 2));//Вода
			 else if (temperature[i][r] > 0.55f) {
				 if (wet[i][r] > 0.675f) bioms.setPixel(i, r, sf::Color(0, 117, 85));//Дождевой тропический лес
				 else if (wet[i][r] > 0.47f)  bioms.setPixel(i, r, sf::Color(0, 117, 67)); //Тропический лес
				 else  if (wet[i][r] > 0.3f) bioms.setPixel(i, r, sf::Color(172, 167, 25));//Саванны
				 else bioms.setPixel(i, r, sf::Color(222, 184, 135));//Пустыня
			 }
			 else if (temperature[i][r] > 0.50f) {
				 if (wet[i][r] > 0.625f) bioms.setPixel(i, r, sf::Color(0, 117, 85));//Дождевой тропический лес
				 else if (wet[i][r] > 0.38f) bioms.setPixel(i, r, sf::Color(0, 117, 67)); //Тропический лес
				 else  if (wet[i][r] > 0.25f) bioms.setPixel(i, r, sf::Color(172, 167, 25));//Саванны
				 else bioms.setPixel(i, r, sf::Color(222, 184, 135));//Пустыня
			 }
			 else if (temperature[i][r] > 0.23f) {
				 if (wet[i][r] > 0.525f)bioms.setPixel(i, r, sf::Color(164, 218, 140));//Дождевой лес умеренной зоны
				 else if (wet[i][r] > 0.395f) bioms.setPixel(i, r, sf::Color(164, 218, 68)); //Лес умеренной зоны
				 else if (wet[i][r] > 0.005f)  bioms.setPixel(i, r, sf::Color(175, 242, 6));//Равнина
				 else bioms.setPixel(i, r, sf::Color(222, 184, 135));//Пустыня
			 }
			 else if (temperature[i][r] > 0.1f) {
				 if (wet[i][r] > 0.02f)  bioms.setPixel(i, r, sf::Color(0, 109, 120)); //Тайга
				 else bioms.setPixel(i, r, sf::Color(60, 80, 120));//Кустарники 
			 }
			 else
				 bioms.setPixel(i, r, sf::Color(255, 255, 255));//Тундра
		 }
}

void Map::generateMap()
{
	 generateLand();
	 generateTemperature();
	 generateWet();
	 generateBioms();
	 map = bioms;
	 for (int i = 0; i < width; ++i)
		 for (int r = 0; r < height; ++r)
			 if (line[i][r])
				 map.setPixel(i, r, sf::Color::Black);
}

void Map::generateRiver()
{
	howRiver = 5+rand() % ( width*height / 500);
	rivers = new std::vector<sf::Vector2f>[howRiver];
	int i=0;
	while ( i<howRiver){
		int x = rand() % width, y = rand() % height;
		if (land[x][y]>0.15&&rand() / RAND_MAX > (1 - wet[x][y])) {
			makeRiver(rivers,i,rand()%4, x,y);
			i++;

		}
	}

}

Map::Map(int width, int height)
{
	this->width = width;
	this->height = height;

	sideLength = std::min(WINDOW_X / width, WINDOW_Y / height);
	land = new double* [width];
	for (int i = 0; i < width; ++i)
		land[i] = new double[height];

	temperature = new double* [width];
	for (int i = 0; i < width; ++i)
		temperature[i] = new double[height];

	wet = new double* [width];
	for (int i = 0; i < width; ++i)
		wet[i] = new double[height];

	bioms.create(width, height);

	line = new bool* [width];
	for (int i = 0; i < width; ++i)
		line[i] = new bool[height];
}

Map::Map(const Map & mapData)
{
	width = mapData.width;
	 height= mapData.height;
	 bioms = mapData.bioms;
	
	 sideLength=mapData.sideLength;
	for (int i = 0; i < width; ++i)
		for (int r = 0; r < height; ++r)
			land[i][r] = mapData.land[i][r];

	for (int i = 0; i < width; ++i)
		for (int r = 0; r < height; ++r)
			temperature[i][r] = mapData.temperature[i][r];

	for (int i = 0; i < width; ++i)
		for (int r = 0; r < height; ++r)
			wet[i][r] = mapData.wet[i][r];

	for (int i = 0; i < width; ++i)
		for (int r = 0; r < height; ++r)
			line[i][r] = mapData.line[i][r];

	for (int i = 0; i < howRiver; ++i)
		rivers[i] = mapData.rivers[i];
}

Map::~Map()
{
	for (int i = 0; i < width; ++i)
		delete[] temperature[i];
	delete[] temperature;

	for (int i = 0; i < width; ++i)
			delete[] land[i];
	delete[] land;

	for (int i = 0; i < width; ++i)
		delete[] wet[i];
	delete[] wet;

	for (int i = 0; i < width; ++i)
		delete[] line[i];
	delete[] line;

	delete[] rivers;
}