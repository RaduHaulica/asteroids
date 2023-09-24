#pragma once

#include "GameObject.h"

#include "MessageQueue.h"

class Boulder : public GameObject
{
public:
	float m_rotationSpeed{ 0.f };

	Boulder(sf::Vector2f origin);

	void update(float dt);
	void collide();
};