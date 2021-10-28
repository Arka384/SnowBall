#include "Snowball.hpp"

void Snowball::loadTex(void)
{
	if (!balltex.loadFromFile("textures/snowball_sprite.png")) {
		std::cout << "Resource loading failed";
		exit(1);
	}
	ball.setTexture(balltex);
	ball.setTextureRect(sf::IntRect(0, 0, 40, 40));
	ball.setScale(scallingFactor);
	pos = sf::Vector2f(windowSize.x / 2 - ball.getGlobalBounds().width / 2, windowSize.y - ball.getGlobalBounds().width - 100);

	line.setSize(sf::Vector2f(windowSize.x, 20));
	line.setPosition(0, windowSize.y - 100);
}

void Snowball::move(float dt, int key)
{
	if (key == 0) {	//left
		pos.x -= speed * dt;

		if (rectX == 0)
			rectX = 120;
		else rectX -= 40;
		ball.setTextureRect(sf::IntRect(rectX, 0, 40, 40));
	}
	else if (key == 1) {	//right
		pos.x += speed * dt;

		if (rectX == 120)
			rectX = 0;
		else rectX += 40;
		ball.setTextureRect(sf::IntRect(rectX, 0, 40, 40));
	}

	if (pos.x < 0)
		pos.x = 0;
	if (pos.x + ball.getGlobalBounds().width > windowSize.x)
		pos.x = windowSize.x - ball.getGlobalBounds().width;

	ball.setPosition(pos.x, pos.y);
}

void Snowball::resetSnowball(void)
{
	scallingFactor = sf::Vector2f(1.4, 1.4);
	ball.setScale(scallingFactor);
	rectX = 0;
	pos = sf::Vector2f(windowSize.x / 2 - ball.getGlobalBounds().width / 2, windowSize.y - ball.getGlobalBounds().width - 100);
	ball.setPosition(pos.x, pos.y);
}

void Snowball::updateSnowball(float dt, std::list<item> &items, sf::Texture &snowTex, sf::Texture &rockTex, int &gameState)
{
	//input events
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		move(dt, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		move(dt, 1);

	scallingFactor.x = scallingFactor.x - scaleDecr;
	scallingFactor.y = scallingFactor.y - scaleDecr;
	if (scallingFactor.x <= 0.2) {
		gameState = 0;
		return;
	}
	ball.setScale(scallingFactor);
	pos.y = windowSize.y - ball.getGlobalBounds().width - 100;
	ball.setPosition(pos.x, pos.y);

	for (auto i = items.begin(); i != items.end(); i++) {
		if (i->sprite.getTexture() == &snowTex) {
			if (i->sprite.getGlobalBounds().intersects(ball.getGlobalBounds()) && !i->collided ) {
				i->collided = true;
				scallingFactor = sf::Vector2f(1.4, 1.4);
				ball.setScale(scallingFactor);
				pos.y = windowSize.y - ball.getGlobalBounds().width - 100;
				ball.setPosition(pos.x, pos.y);
			}
		}
		else if (i->sprite.getTexture() == &rockTex) {
			if (i->sprite.getGlobalBounds().intersects(ball.getGlobalBounds()) && !i->collided) {
				i->collided = true;
				scallingFactor = sf::Vector2f(0, 0);
				gameState = 0;
				return;
			}
		}
	}
}
