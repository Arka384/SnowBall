#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

typedef struct item {
	sf::Sprite sprite;
	float velocityY;
	bool collided;
}item;

class GameItems
{
private:
	float timer = 0, spwanTime = 2.f;
	float fallSpeed = 300.f;
	int rockCount = 0;
public:
	sf::Texture rockTex, snowtex;
	sf::Sprite rock, snow;
	item temp;
	std::list <item>items;

	void loadItems(void);
	void spwanItems(float, sf::Vector2i);
	void updateItems(float, sf::Vector2i);
	void renderItems(sf::RenderWindow &);
};