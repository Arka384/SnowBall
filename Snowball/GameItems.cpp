#include "GameItems.hpp"

void GameItems::loadItems(void)
{
	if (!rockTex.loadFromFile("res/textures/rock.png") || !snowtex.loadFromFile("res/textures/snowball.png")
		|| !(rockbuf.loadFromFile("res/sounds/rock_hit.wav")) || (!font.loadFromFile("res/flappy.ttf")) ) {
		std::cout << "Resource loading failed";
		exit(1);
	}
	rock.setTexture(rockTex);
	snow.setTexture(snowtex);
	snow.setPosition(0, -snow.getGlobalBounds().height);
	rock_hit.setBuffer(rockbuf);
	rock_hit.setVolume(60.f);

	Scoretext.setFont(font);
	score.setFont(font);
	Scoretext.setCharacterSize(30.f);
	score.setCharacterSize(30.f);
	Scoretext.setFillColor(sf::Color::Black);
	score.setFillColor(sf::Color::Black);
	Scoretext.setString("Score:");
	Scoretext.setPosition(5, 5);
	score.setPosition(120, 5);
}

void GameItems::spwanItems(float dt, sf::Vector2i windowSize)
{
	timer += dt;
	if (timer > spwanTime) {
		if (rockCount < 3) {
			float x = rand() % (int)(windowSize.x - rock.getGlobalBounds().width);
			float scale = 0.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.8 - 0.5)));
			rock.setPosition(x, -rock.getGlobalBounds().height);
			rock.setScale(scale, scale);
			temp.sprite = rock;
			temp.collided = false;
			temp.velocityY = rand() % 350 + 50;
			items.push_back(temp);
			rockCount++;
		}
		else {
			float x = rand() % (int)(windowSize.x - snow.getGlobalBounds().width);
			float scale = 0.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.8 - 0.5)));
			snow.setPosition(x, -snow.getGlobalBounds().height);
			temp.sprite = snow;
			temp.collided = false;
			temp.velocityY = rand() % 200 + 100;
			items.push_back(temp);
			rockCount = 0;
		}
		timer = 0;
		if (spwanTime > 0.45)
			spwanTime -= dt * 2.5;
	}
}

void GameItems::updateItems(float dt, sf::Vector2i windowSize, int &last_score)
{
	std::stringstream score_stream;
	score_stream << CurrentScore;
	score.setString(score_stream.str());

	auto i = items.begin();
	while (i != items.end()) {
		float y = i->sprite.getPosition().y + i->velocityY * dt;
		i->sprite.setPosition(i->sprite.getPosition().x, y);
		if (i->sprite.getPosition().y + i->sprite.getGlobalBounds().width > windowSize.y - 100) {
			i = items.erase(i);
			CurrentScore++;
			last_score = CurrentScore;
			rock_hit.play();
		}
		else
			i++;
	}

	spwanItems(dt, windowSize);
}

void GameItems::resetItems(void)
{
	items.clear();
	rockCount = 0;
	timer = 0;
	CurrentScore = 0;
	spwanTime = 2.f;
}

void GameItems::renderItems(sf::RenderWindow &window)
{
	for (auto i = items.begin(); i != items.end(); i++) {
		if(!i->collided)
			window.draw(i->sprite);
	}
	window.draw(Scoretext);
	window.draw(score);
}
