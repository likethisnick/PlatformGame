#include <SFML/Graphics.hpp>

//6.47

class PLAYER
{
	public:
		float dx, dy;
		sf::IntRect rect;
		bool onGround;
		sf::Sprite sprite;
		float currentRunningFrame;
		float currentStayingFrame;
		float currentJumpingFrame;
		bool LeftRight;

		// высота "земли"
		int ground = 500;


		PLAYER(sf::Texture &image)
		{

			sprite.setTexture(image);
			rect = sf::IntRect(0, 0, 131, 140);
			sprite.setTextureRect(sf::IntRect(0, 0, 131, 140));

			dx = dy = 0;
			currentRunningFrame = 0;
			currentStayingFrame = 0;
			currentJumpingFrame = 0;
			LeftRight = true; // right
		}

		void update(float time)
		{
			rect.left += dx * time;
			if (!onGround) dy = dy + 0.0008*time;
			rect.top += dy * time;
			if (rect.top > ground)
			{
				rect.top = ground;
				dy = 0;
				onGround = true;
			}

			currentRunningFrame += 0.02*time;
			currentStayingFrame += 0.01*time;
			currentJumpingFrame += 0.005*time;
			if (currentRunningFrame > 26) currentRunningFrame -= 26;
			if (currentStayingFrame > 21) currentStayingFrame -= 21;
			if (currentJumpingFrame > 15) currentJumpingFrame -= 15;

			if ((int)dx == 0 && (int)dy == 0)
			{
				if(LeftRight)
					sprite.setTextureRect(sf::IntRect(85*int(currentStayingFrame), 420, 85, 140));
				else
					sprite.setTextureRect(sf::IntRect(85 * int(currentStayingFrame)+85, 420, -85, 140));
			}

			if (dx > 0)
			{
				if (int(currentRunningFrame)<9)
					sprite.setTextureRect(sf::IntRect(131 * int(currentRunningFrame), 0, 131, 140));
				else if (int(currentRunningFrame) >= 9 && int(currentRunningFrame) < 17)
					sprite.setTextureRect(sf::IntRect(131 * (int(currentRunningFrame) - 9), 140, 131, 140));
				else if (int(currentRunningFrame) >= 17)
					sprite.setTextureRect(sf::IntRect(131 * (int(currentRunningFrame) - 17), 280, 131, 140));
				LeftRight = true;
			}

			if (dx < 0)
			{
				if (int(currentRunningFrame) < 9)
					sprite.setTextureRect(sf::IntRect(131 * int(currentRunningFrame) + 131, 0, -131, 140));
				else if (int(currentRunningFrame) >= 9 && int(currentRunningFrame) < 17)
					sprite.setTextureRect(sf::IntRect(131 * (int(currentRunningFrame) - 9) + 131, 140, -131, 140));
				else if (int(currentRunningFrame) >= 17)
					sprite.setTextureRect(sf::IntRect(131 * (int(currentRunningFrame) - 17) + 131, 280, -131, 140));
				LeftRight = false;
			}

			if (!onGround)
			{
				if (LeftRight)
					sprite.setTextureRect(sf::IntRect(120 * int(currentJumpingFrame), 560, 120, 140));
				else
					sprite.setTextureRect(sf::IntRect(120 * int(currentJumpingFrame)+120, 560, -120, 140));
			}
			else
				currentJumpingFrame = 0;


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
				p.dy = -0.8;
				p.onGround = false;
			}
		}

		p.update(time);

		window.clear();
		window.draw(p.sprite);
		window.display();

	}
}