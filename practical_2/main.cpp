#include <SFML/Graphics.hpp>
#include "ship.h"
#include "game.h"
#include <iostream>

using namespace sf;
using namespace std;

std::vector<Ship *> ships;

void Load() {
	Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100, 100 });
	ships.push_back(inv);

	for (int r = 0; r < invaders_rows; ++r) {
		auto rect = IntRect(r * 32, r* 32, 32, 32);
		for (int c = 0; c < invaders_columns; ++c) {
			Vector2f position = {c*50+10, r*50+10};
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}
}

void Update(double dt) {
	for (auto &s : ships) {
		s->Update(dt);
	};
}

void Render(RenderWindow &window ) {
	for (const auto s : ships) {
		window.draw(*s);
	}
}