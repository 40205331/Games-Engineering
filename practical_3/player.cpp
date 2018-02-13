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
	
	// Move Left
	if (Keyboard::isKeyPressed(controls[0])) {
		Player::_position.x -= Player::_speed * (float)dt;
	}

	// Move right
	if (Keyboard::isKeyPressed(controls[1])) {
		Player::_position.x += Player::_speed * (float)dt;
	}
	
	// Move up
	if (Keyboard::isKeyPressed(controls[2])) {
		Player::_position.y -= Player::_speed * (float)dt;
	}
	// Move down
	if (Keyboard::isKeyPressed(controls[3])) {
		Player::_position.y += Player::_speed * (float)dt;
	}

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
