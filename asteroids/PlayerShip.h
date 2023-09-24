#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Config.h"
#include "MessageQueue.h"

class PlayerShip : public GameObject
{
public:
	float laserCooldown{ 0.1f };
	float laserCooldownAccumulator{ 0.f };

	PlayerShip();
	//PlayerShip(sf::Vector2f origin);
	void update(float dt);

	void fire();
};