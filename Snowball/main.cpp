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
	sf::Texture bgtex;
	sf::Sprite bg;
	float dt = 0;

	snowball.loadTex();
	rock.loadItems();
	snowflakes.loadSnowFlakes(snowball.windowSize);
	bgtex.loadFromFile("textures/bg.png");
	bg.setTexture(bgtex);
	bg.setScale(1.25, 1.25);

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
					if (e.key.code == sf::Keyboard::Left)
						snowball.move(dt, 0);
					if (e.key.code == sf::Keyboard::Right)
						snowball.move(dt, 1);
				break;
			default:
				break;
			}
		}

		rock.updateItems(dt, snowball.windowSize);
		snowball.updateSnowball(dt, rock.items, rock.snowtex, rock.rockTex);
		snowflakes.updateSnowFlakes(dt);

		window.clear();
		
		window.draw(bg);
		snowflakes.renderSnowFlakes(window);
		window.draw(snowball.ball);
		rock.renderItems(window);

		window.display();
	}
}