#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

typedef struct flakes {
	sf::Sprite sprite;
	float velocityY;
};

class SnowFlakes
{
private:
	float spawnTime = 0.2;
	float timer = 0;
	sf::Vector2i windowSize;
public:
	sf::Texture flakesTex;
	sf::Sprite snowFlakeSprite;
	std::list<flakes> snowflakes;
	flakes temp;

	void loadSnowFlakes(sf::Vector2i);
	void spawnSnowFlakes(float);
	void updateSnowFlakes(float );
	void resetSnowFlakes(void);
	void renderSnowFlakes(sf::RenderWindow &);
};

