#include "Config.h"

GlobalConfig::GlobalConfig()
{
	DEFAULT_FONT.loadFromFile("Roboto-Bold.ttf");
	DEBUG_TEXT.setFont(DEFAULT_FONT);
	DEBUG_TEXT.setFillColor(sf::Color::White);
	DEBUG_TEXT.setCharacterSize(14);
}

GlobalConfig* GlobalConfig::getInstance()
{
	if (!m_instance)
	{
		m_instance = new GlobalConfig();
	}
	return m_instance;
}

void GlobalConfig::update(float dt)
{
	if (inputCooldownAccumulator == 0.f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		{
			GlobalConfig::DEBUG_MODE = !GlobalConfig::DEBUG_MODE;
			inputCooldownAccumulator = inputCooldownDuration;
		}
	}
	else
	{
		inputCooldownAccumulator = std::fmax(0.f, inputCooldownAccumulator - dt);
	}
}

GlobalConfig::~GlobalConfig()
{
	if (m_instance)
	{
		delete m_instance;
	}
}

bool GlobalConfig::DEBUG_MODE = false;;
sf::Font GlobalConfig::DEFAULT_FONT;
GlobalConfig* GlobalConfig::m_instance;
sf::Text GlobalConfig::DEBUG_TEXT;

float GlobalConfig::inputCooldownAccumulator{ 0.f };
float GlobalConfig::inputCooldownDuration{ 0.1 };

float GlobalConfig::BOUNDARY_MIN_X = 0.f;
float GlobalConfig::BOUNDARY_MAX_X = 1000.f;
float GlobalConfig::BOUNDARY_MIN_Y = 0.f;
float GlobalConfig::BOUNDARY_MAX_Y = 1000.f;