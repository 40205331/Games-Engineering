/*#include "ghost.h"

using namespace sf;
using namespace std;

void Ghost::update(float dt) {
	// Movement
	// ...

	Entity::update(dt);
}

Ghost::Ghost()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Ghost::render(sf::RenderWindow &window) const{
	window.draw(*_shape);
}*/