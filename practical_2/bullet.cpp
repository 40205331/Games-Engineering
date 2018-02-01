#include "bullet.h"
#include "game.h"
#include "ship.h"

using namespace sf;
using namespace std;

// create definition for the constructor
//...

void Bullet::_Update(const float &dt) {
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32)
	{
		// off screen - do nothing
		return;
	}
	else {
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s == player) {
				// player bullets dont collide with player
				continue;
			}
			if (_mode && s != player) {
				// inbader bullets dont collide with other invaders
				continue;
			}
			if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox)) {
				// Explode the ship 
				s->Explode();
				// warp the bullets off screen
				setPosition(-100, -100);
				return;
			}
		}
	}
};

void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}