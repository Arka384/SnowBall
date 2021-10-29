#pragma once
#include "GameItems.hpp"

class Snowball
{
private:
	sf::Vector2f pos;
	float speed = 400.f, scaleDecr = 0.09;
	sf::Vector2f scallingFactor = sf::Vector2f(1.4, 1.4);
	int rectX = 0;
	sf::SoundBuffer snowhitbuf, gameoverbuf, snowballcollectbuf;
	sf::Sound snow_hit, game_over, snowballcollect;
	//float dy = 0, gravity = 3000.f, jumpforce = 2000.f;


public:
	sf::Vector2i windowSize = sf::Vector2i(900, 600);
	sf::Texture balltex;
	sf::Sprite ball;

	void loadTex(void);
	void move(float , int );
	void resetSnowball(void);
	void updateSnowball(float dt, std::list<item> &, sf::Texture &, sf::Texture &, int &);
};

