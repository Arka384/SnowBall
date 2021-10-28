#pragma once
#include "GameItems.hpp"

class Snowball
{
private:
	sf::Vector2f pos;
	float speed = 400.f, scaleDecr = 0.00008;
	sf::Vector2f scallingFactor = sf::Vector2f(1.4, 1.4);
	int rectX = 0;

public:
	sf::Vector2i windowSize = sf::Vector2i(900, 600);
	sf::Texture balltex;
	sf::Sprite ball;
	sf::RectangleShape line;

	void loadTex(void);
	void move(float , int );
	void resetSnowball(void);
	void updateSnowball(float dt, std::list<item> &, sf::Texture &, sf::Texture &, int &);
};

