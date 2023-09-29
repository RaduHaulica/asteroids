#pragma once

#include <SFML/Graphics.hpp>

struct GameParameters
{
	bool DEBUG_MODE{ false };
};

class GlobalConfig
{
	static GlobalConfig* m_instance;

	static float inputCooldownAccumulator;
	static float inputCooldownDuration;

	GlobalConfig();

public:
	enum class OBJECTS
	{
		START = 0,
		GENERIC = 0,
		BULLET = 1,
		BOULDER = 2,
		ROCK = 3,
		RUBBLE = 4,
		END = 4,
	};

	enum class PARTICLES
	{
		START = 0,
		PIXEL = 0,
		EXPLOSION_PIXEL = 1,
		DEBRIS_PIXEL = 2,
		SLOW_FADER = 3,
		END = 3,
	};

	static float BOUNDARY_MIN_X;
	static float BOUNDARY_MAX_X;
	static float BOUNDARY_MIN_Y;
	static float BOUNDARY_MAX_Y;
	static bool DEBUG_MODE;
	static sf::Font DEFAULT_FONT;
	static sf::Text DEBUG_TEXT;

	~GlobalConfig();
	static GlobalConfig* getInstance();

	static void update(float dt);
};