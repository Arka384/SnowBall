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
	sf::Clock clk;
	sf::Time time;
	sf::Texture bgtex, title_tex;
	sf::Sprite bg, title;
	float dt = 0;
	int game_state = 0;

	snowball.loadTex();
	rock.loadItems();
	snowflakes.loadSnowFlakes(snowball.windowSize);
	if (!bgtex.loadFromFile("textures/bg.png") || !title_tex.loadFromFile("textures/titlescreen.png")) {
		std::cout << "Resource loading failed";
		exit(1);
	}
	bg.setTexture(bgtex);
	bg.setScale(1.25, 1.25);
	title.setTexture(title_tex);


	srand(static_cast<unsigned>(std::time(0)));

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
			rock.updateItems(dt, snowball.windowSize);
			snowball.updateSnowball(dt, rock.items, rock.snowtex, rock.rockTex, game_state);
			snowflakes.updateSnowFlakes(dt);
		}		

		window.clear();
		
		if (game_state == 0)
			window.draw(title);
		else {
			window.draw(bg);
			snowflakes.renderSnowFlakes(window);
			window.draw(snowball.ball);
			rock.renderItems(window);
		}

		window.display();
	}
}