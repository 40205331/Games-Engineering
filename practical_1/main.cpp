#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A,     // Player1 UP
	Keyboard::Z,     // Player1 Down
	Keyboard::Up,    // Player2 UP
	Keyboard::Down   // Player 2 Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];

void reset()
{
	// reset paddle position 
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - paddleSize.x - 10, gameHeight / 2);
	// reset Ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2);

	ballVelocity = { server ? 100.0f : -100.0f, 60.0f };
}

void Load() {
	// Set size and origin of paddles
	for (auto &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	
	reset();
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via ESC key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	// handle paddle movement 
	float leftdirection = 0.0f;
	float rightdirection = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		leftdirection--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		leftdirection++;
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		rightdirection--;
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		rightdirection++;
	}
	paddles[0].move(0, leftdirection * paddleSpeed * dt);
	paddles[1].move(0, rightdirection * paddleSpeed * dt);

	ball.move(ballVelocity * dt);

	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

	if (by > gameHeight) {
		// bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) {
		// top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth) {
		// right wall
		reset();
	}
	else if (bx < 0) {
		// left wall
		reset();
	}
	else if (
		// ball is inline or behind paddle
		bx < paddles[0].getPosition().x &&
		// AND ball is below top edge of paddle 
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		// AND ball is above bottom edge of paddle 
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) {
		// bounce of left paddle 
		ballVelocity.x *= -1.1f;
		ball.move(1, 0);
	}
	else if (
		// ball is inline or behind paddle
		bx > paddles[1].getPosition().x &&
		// AND ball is below top edge of paddle 
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		// AND ball is above bottom edge of paddle 
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		) {
		// bounce of right paddle 
		ballVelocity.x *= -1.1f;
		ball.move(-1, 0);
	}
			
	

}
void Render(RenderWindow &window) {
	// Draw Everthing
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}