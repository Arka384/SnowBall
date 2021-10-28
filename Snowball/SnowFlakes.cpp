#include "SnowFlakes.hpp"

void SnowFlakes::loadSnowFlakes(sf::Vector2i size)
{
	if (!flakesTex.loadFromFile("res/textures/flakes.png")) {
		std::cout << "Resource loading failed";
		exit(1);
	}
	snowFlakeSprite.setTexture(flakesTex);
	windowSize = size;
}

void SnowFlakes::spawnSnowFlakes(float dt)
{
	timer += dt;
	if (timer > spawnTime) {
		float x = rand() % (int)(windowSize.x - snowFlakeSprite.getGlobalBounds().width);
		float scale = 0.2 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.8 - 0.2)));
		snowFlakeSprite.setPosition(x, -snowFlakeSprite.getGlobalBounds().height);
		snowFlakeSprite.setScale(scale, scale);
		temp.sprite = snowFlakeSprite;
		temp.velocityY = rand() % 40 + 10;
		snowflakes.push_back(temp);
		timer = 0;
	}
}

void SnowFlakes::updateSnowFlakes(float dt)
{
	spawnSnowFlakes(dt);
	auto i = snowflakes.begin();
	while (i != snowflakes.end()) {
		float y = i->sprite.getPosition().y + i->velocityY *dt;
		i->sprite.setPosition(i->sprite.getPosition().x, y);
		if (i->sprite.getPosition().y > windowSize.y - 100)
			i = snowflakes.erase(i);
		else
			i++;
	}
}

void SnowFlakes::resetSnowFlakes(void)
{
	snowflakes.clear();
	timer = 0;
}

void SnowFlakes::renderSnowFlakes(sf::RenderWindow &window)
{
	for (auto i = snowflakes.begin(); i != snowflakes.end(); i++)
		window.draw(i->sprite);
}
