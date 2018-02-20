#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

#define ls LevelSystem

class LevelSystem {
public:
	enum TILE { EMPTY, START, END, WALL, ENEMY, WAYPOINT };

	static void loadLevelFile(const std::string&, float tileSize = 100.0f);
	static void render(sf::RenderWindow &window);
	static sf::Color getColor(TILE t);
	static void setColor(TILE t, sf::Color c);
	// get tile at grid coordinate
	static TILE getTile(sf::Vector2f);
	// Get Screenspace coordinates of tile
	static sf::Vector2f getTilePosition(sf::Vector2f);
	// Get the tile at screenspace position
	static TILE getTileAt(sf::Vector2f);
	static size_t getHeight();
	static size_t getWidth();

protected:
	static std::unique_ptr<TILE[]> _tiles; // internal array of tiles
	static size_t _width; // how many tiles wide is level
	static size_t _height; // how many tiles high is level
	static sf::Vector2f _offset; // Screenspace offset of level, when rendered
	static float _tileSize; // Screenspace size of eachtile, when rendered 
	static std::map<TILE, sf::Color> _colours;

	// array of sfml sprites of each tile
	static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
	// generate the _sprites array
	static void buildSprites();

private:
	LevelSystem() = delete;
	~LevelSystem() = delete;
};