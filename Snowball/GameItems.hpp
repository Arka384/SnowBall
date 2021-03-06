#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
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
	int rockCount = 0;
	item temp;
	sf::SoundBuffer rockbuf;
	sf::Sound rock_hit;
	sf::Text Scoretext, score;

public:
	sf::Texture rockTex, snowtex;
	sf::Sprite rock, snow;
	std::list <item>items;
	sf::Font font;
	int CurrentScore = 0;

	void loadItems(void);
	void spwanItems(float, sf::Vector2i);
	void updateItems(float, sf::Vector2i, int &);
	void resetItems(void);
	void renderItems(sf::RenderWindow &);
};