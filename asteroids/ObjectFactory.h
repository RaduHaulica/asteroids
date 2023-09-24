#pragma once

#include <stdlib.h>
#include <time.h>

#include "Config.h"
#include "GameObject.h"
#include "Boulder.h"

#include "convex_hull.h"

class ObjectFactory
{
public:
	std::unique_ptr<GameObject> createObject(GlobalConfig::OBJECTS objectType, sf::Vector2f origin, sf::Vector2f orientation = { 0.f, 0.f });
};