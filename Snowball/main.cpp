#include "Snowball.hpp"
#include "SnowFlakes.hpp"
#include <ctime>
#include <cstdlib>

int main()
{
	Snowball snowball;
	GameItems rock;
	SnowFlakes snowflakes;
	sf::RenderWindow window(sf::VideoMode(snowball.windowSize.x, snowball.windowSize.y), "Snow", sf::Style::Close);
	sf::Clock clk, clock;
	sf::Time time;
	sf::Texture bgtex, title_tex;
	sf::Sprite bg, title;
	sf::SoundBuffer themeSoundbuf;
	sf::Sound theme_sound;
	sf::Text lastScore;
	float dt = 0;
	int game_state = 0, last_score = 0;

	snowball.loadTex();
	rock.loadItems();
	snowflakes.loadSnowFlakes(snowball.windowSize);
	if ((!bgtex.loadFromFile("res/textures/bg.png")) || (!title_tex.loadFromFile("res/textures/titlescreen.png"))
		|| (!themeSoundbuf.loadFromFile("res/sounds/theme_song.wav"))) {
		std::cout << "Resource loading failed";
		exit(1);
	}
	bg.setTexture(bgtex);
	bg.setScale(1.25, 1.25);

	lastScore.setFont(rock.font);
	lastScore.setFillColor(sf::Color::Black);
	lastScore.setCharacterSize(22.f);
	lastScore.setPosition(842, 53);

	title.setTexture(title_tex);
	theme_sound.setBuffer(themeSoundbuf);
	theme_sound.setLoop(true);
	theme_sound.play();

	srand(static_cast<unsigned>(std::time(0)));
	window.setVerticalSyncEnabled(true); //as per refresh rate

	while (window.isOpen())
	{
		time = clk.restart();
		dt = time.asSeconds();

		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Enter)
					if (game_state == 0) {
						game_state = 1;
						snowball.resetSnowball();
						rock.resetItems();
						snowflakes.resetSnowFlakes();
					}
				break;
			default:
				break;
			}
		}

		if (game_state == 1) {
			rock.updateItems(dt, snowball.windowSize, last_score);
			snowball.updateSnowball(dt, rock.items, rock.snowtex, rock.rockTex, game_state);
			snowflakes.updateSnowFlakes(dt);
		}		

		window.clear();
		
		if (game_state == 0) {
			std::stringstream ss;
			ss << last_score;
			lastScore.setString(ss.str());
			window.draw(title);
			window.draw(lastScore);
		}
		else {
			window.draw(bg);
			snowflakes.renderSnowFlakes(window);
			window.draw(snowball.ball);
			rock.renderItems(window);
		}

		window.display();
	}
}