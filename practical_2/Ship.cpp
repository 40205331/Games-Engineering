#include "ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[3] = {
	Keyboard::Left,     // Player1 UP
	Keyboard::Right,     // Player1 Down
	Keyboard::Space    // Player2 UP
};

bool Invader::direction;
float Invader::speed;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

//Define the ship deconstructor
// Although we set this to pure virtual, we still have to define it
Ship::~Ship() = default;

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i) {
			ships[i]->move(0, 24);
			}
	}
}

Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * 0.5f, gameHeight - 32.0f });
}

void Player::Update(const float &dt) {
	Ship::Update(dt);
	// Move left
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction--;
	}
	// Move right
	if (Keyboard::isKeyPressed(controls[1])) {
		direction++;
	}
	// Bullet
	static vector<Bullet*> bullets;
	if (Keyboard::isKeyPressed(controls[2])) {
		bullets.push_back(new Bullet(getPosition(), false));
	}
	for (const auto s : bullets) {
		s->Update(dt);
	}
}