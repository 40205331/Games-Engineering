#include "player.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::Left,  // Player Left
	Keyboard::Right, // Player Right
	Keyboard::Up,    // Player UP
	Keyboard::Down   // Player Down
};

void Player::update(double dt) {
	// Move in four directions based on keys
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction--;
	}
	// Move right
	if (Keyboard::isKeyPressed(controls[1])) {
		direction++;
	}

	/*
	if (Keyboard::isKeyPressed(controls[2])) {
		direction--;
	}
	// Move right
	if (Keyboard::isKeyPressed(controls[3])) {
		direction++;
	}
	*/
	Entity::update(dt);
}

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}
