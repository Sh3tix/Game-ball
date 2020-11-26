#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

// Prototype
void updateBall(Sprite& ballSprite, RenderWindow& window, bool& isShot);
void updateHoop(CircleShape& hoop, RenderWindow& window, int& dir, float& hoopSpeed);
void collisionBall(Sprite& ballSprite, CircleShape& hoop, RenderWindow& window, bool& isShot, int& points, Text& textPoints);
void changeDifficulty(int& points, float& hoopSpeed);

int main()
{
	// Some variables
	bool isShot{ false };
	float hoopSpeed{ 5.f };
	int dir{ 0 };
	int points{ 0 };

	// Creation of the window
    RenderWindow window(sf::VideoMode(640, 480), "Simple Square Game");
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);

	// Creation of the hoop
	CircleShape hoop;
	hoop.setRadius(50.f);
	hoop.setFillColor(Color::Black);
	hoop.setOutlineThickness(2.f);
	hoop.setOutlineColor(Color::Blue);
	hoop.setPosition(Vector2f(0, 10.f));

	// Loading of the front
	Font font;
	if (!font.loadFromFile("Fonts/Almond Nougat.ttf"))
		throw("Impossible de charger la police.");

	// Creation of the "textPoints"
	Text textPoints;
	textPoints.setFont(font);
	textPoints.setCharacterSize(24);
	textPoints.setFillColor(Color::Blue);
	textPoints.setStyle(Text::Bold);
	textPoints.setPosition(5.f, 0.f);
	textPoints.setString("Points : " + std::to_string(points));

	// Creation of the "ballTexture"
	Texture ballTexture;
	if (!ballTexture.loadFromFile("Images/basketball.png"))
		throw("Erreur: impossible de charger l'image.");

	ballTexture.setSmooth(true);

	// Creation of the "ballSprite"
	Sprite ballSprite;
	ballSprite.setTexture(ballTexture);
	ballSprite.setPosition(Vector2f(0, window.getSize().y - 80));


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
		updateBall(ballSprite, window, isShot);

		// Collision ball
		collisionBall(ballSprite, hoop, window, isShot, points, textPoints);

		// Change difficulty
		changeDifficulty(points, hoopSpeed);

		// Draw
		window.clear(Color::White);

		window.draw(ballSprite);
		window.draw(hoop);
		// window.draw(ball);
		window.draw(textPoints);

		window.display();
		
	}
	
    return 0;
}


void updateBall(Sprite& ballSprite, RenderWindow& window, bool& isShot)
{
	if (Mouse::isButtonPressed(Mouse::Left))
		isShot = true;

	if (!isShot)
		ballSprite.setPosition(Mouse::getPosition(window).x, ballSprite.getPosition().y);
	else
		ballSprite.move(0, -5.f);
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

void collisionBall(Sprite& ballSprite, CircleShape& hoop, RenderWindow& window, bool& isShot, int& points, Text& textPoints)
{

	if (ballSprite.getGlobalBounds().intersects(hoop.getGlobalBounds()) || ballSprite.getPosition().y < -10)
	{

		// Si la condition est respecté on ajoute un point.
		if (ballSprite.getGlobalBounds().intersects(hoop.getGlobalBounds()))
		{
			points++;
			textPoints.setString("Points : " + std::to_string(points));
		}

		isShot = false;	
		ballSprite.setPosition(ballSprite.getPosition().x, window.getSize().y - 80);

	}
}

void changeDifficulty(int& points, float& hoopSpeed)
{
	if (points >= 5)
		hoopSpeed = 7.5f;

	if (points >= 10)
		hoopSpeed = 10.0f;

}