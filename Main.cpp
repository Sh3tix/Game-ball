#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;

void updateBall(CircleShape& ball, RenderWindow& window, bool& isShot);
void updateHoop(CircleShape& hoop, RenderWindow& window, int& dir, float& hoopSpeed);
void collisionBall(CircleShape& ball, CircleShape& hoop, RenderWindow& window, bool& isShot, int& points, Text& textPoints);
void changeDifficulty(int& points, float& hoopSpeed);

int main()
{
	bool isShot{ false };
	float hoopSpeed{ 5.f };
	int dir{ 0 };
	int points{ 0 };

    RenderWindow window(sf::VideoMode(640, 480), "Simple Square Game");
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);

	CircleShape hoop;
	hoop.setRadius(50.f);
	hoop.setFillColor(Color::Black);
	hoop.setOutlineThickness(2.f);
	hoop.setOutlineColor(Color::Blue);
	hoop.setPosition(Vector2f(0, 10.f));

	CircleShape ball;
	ball.setRadius(20.f);
	ball.setFillColor(Color::Red);
	ball.setPosition(Vector2f(0, window.getSize().y - ball.getRadius()*3));

	Font font;
	if (!font.loadFromFile("Fonts/Almond Nougat.ttf"))
		throw("Impossible de charger la police.");

	Text textPoints;
	textPoints.setFont(font);
	textPoints.setCharacterSize(24);
	textPoints.setFillColor(Color::Blue);
	textPoints.setStyle(Text::Bold);
	textPoints.setPosition(5.f, 0.f);
	textPoints.setString("Points : " + std::to_string(points));


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		// Update hoop
		updateHoop(hoop, window, dir, hoopSpeed);

		// Update ball
		updateBall(ball, window, isShot);

		// Collision ball
		collisionBall(ball, hoop, window, isShot, points, textPoints);

		// Change difficulty
		changeDifficulty(points, hoopSpeed);

		// Draw
		window.clear(Color::White);

		window.draw(hoop);
		window.draw(ball);
		window.draw(textPoints);

		window.display();
		
	}
	
    return 0;
}

void updateBall(CircleShape& ball, RenderWindow& window, bool& isShot)
{
	if (Mouse::isButtonPressed(Mouse::Left))
		isShot = true;

	if (!isShot)
		ball.setPosition(Mouse::getPosition(window).x, ball.getPosition().y);
	else
		ball.move(0, -5.f);
}

void updateHoop(CircleShape& hoop, RenderWindow& window, int& dir, float& hoopSpeed)
{

	if (hoop.getPosition().x <= 0)
		dir = 1;

	else if (hoop.getPosition().x + hoop.getRadius() >= window.getSize().x)
		dir = 0;

	if (dir == 0)
	{
		hoop.move(-hoopSpeed, 0);
	}
	else
	{
		hoop.move(hoopSpeed, 0);
	}
}

void collisionBall(CircleShape& ball, CircleShape& hoop, RenderWindow& window, bool& isShot, int& points, Text& textPoints)
{

	if (ball.getGlobalBounds().intersects(hoop.getGlobalBounds()) || ball.getPosition().y < 0)
	{
		if (ball.getGlobalBounds().intersects(hoop.getGlobalBounds()))
		{
			points++;
			textPoints.setString("Points : " + std::to_string(points));
		}

		isShot = false;	
		ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getRadius() * 3);

	}
}

void changeDifficulty(int& points, float& hoopSpeed)
{
	if (points >= 5)
		hoopSpeed = 7.5f;

	if (points >= 10)
		hoopSpeed = 10.0f;

}