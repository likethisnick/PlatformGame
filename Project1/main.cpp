#include <SFML/Graphics.hpp>

//6.47

class PLAYER
{
	public:
		float dx, dy;
		sf::IntRect rect;
		bool onGround;
		sf::Sprite sprite;
		float currentFrame;

		// высота "земли"
		int ground = 150;


		PLAYER(sf::Texture &image)
		{

			sprite.setTexture(image);
			rect = sf::IntRect(0, 0, 131, 140);
			sprite.setTextureRect(sf::IntRect(0, 0, 131, 140));

			dy = dy = 0;
			currentFrame = 0;
		}

		void update(float time)
		{
			rect.left += dx * time;
			if (!onGround) dy = dy + 0.0005*time;
			rect.top += dy * time;
			if (rect.top > ground)
			{
				rect.top = ground;
				dy = 0;
				onGround = true;
			}

			currentFrame += 0.02*time;
			if (currentFrame > 26) currentFrame -= 26;

			if (dx > 0)
			{
				if (int(currentFrame)<9)
					sprite.setTextureRect(sf::IntRect(131 * int(currentFrame), 0, 131, 140));
				else if (int(currentFrame) >= 9 && int(currentFrame) < 17)
					sprite.setTextureRect(sf::IntRect(131 * (int(currentFrame) - 9), 140, 131, 140));
				else if (int(currentFrame) >= 17)
					sprite.setTextureRect(sf::IntRect(131 * (int(currentFrame) - 17), 280, 131, 140));
			}

			if (dx < 0)
			{
				if (int(currentFrame) < 9)
					sprite.setTextureRect(sf::IntRect(131 * int(currentFrame) + 131, 0, -131, 140));
				else if (int(currentFrame) >= 9 && int(currentFrame) < 17)
					sprite.setTextureRect(sf::IntRect(131 * (int(currentFrame) - 9) + 131, 140, -131, 140));
				else if (int(currentFrame) >= 17)
					sprite.setTextureRect(sf::IntRect(131 * (int(currentFrame) - 17) + 131, 280, -131, 140));
			}
			sprite.setPosition(rect.left, rect.top);
			dx = 0;
		}

};



int main() {



	// Окно программы
	sf::RenderWindow window({ 1024, 770 }, "Hello World");

	// Предел fps
	window.setFramerateLimit(60);

	// Проверочный объект (зеленый круг, уже не нужен)
	sf::CircleShape MyCircle(100.f);
	MyCircle.setFillColor(sf::Color::Green);
	
	// Текстура для бега
	sf::Texture tRunning;
	tRunning.loadFromFile("tim2.png");

	PLAYER p(tRunning);

	// Определяем первый кадр (нулевой)
	float currentFrame = 0;


	sf::Clock clock;

	while (window.isOpen())
	{
		// time = получить прошедшее время в микросекундах и засекает новое время
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 800;

		// объявляем событие для закрытия окна (если событие - закрытие окна, окно закрывается)
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Нажата кнопка "влево"
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// Скорость движения
			p.dx = -0.3;

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// Скорость движения
			p.dx = 0.3;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (p.onGround)
			{
				p.dy = -0.4;
				p.onGround = false;
			}
		}

		p.update(time);

		window.clear();
		window.draw(p.sprite);
		window.display();

	}
}