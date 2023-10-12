#include "PlayerShip.h"

PlayerShip::PlayerShip()
{
	//this one is called for now

	m_position = { 0.f, 0.f };
	m_orientation = { 0.f, -1.f };

	std::vector<sf::Vector2f> triangle;
	triangle.push_back({ m_position.x, m_position.y - 25.f });
	triangle.push_back({ m_position.x - 15.f, m_position.y + 15.f });
	triangle.push_back({ m_position.x + 15.f, m_position.y + 15.f });
	m_graphicsComponent.m_polygons.push_back(triangle);
	m_colliderComponent.m_polygons.push_back(triangle);

	float minx = triangle[0].x;
	float maxx = triangle[0].x;
	float miny = triangle[0].y;
	float maxy = triangle[0].y;

	for (int i = 1; i < triangle.size(); i++)
	{
		minx = std::min(minx, triangle[i].x);
		maxx = std::max(maxx, triangle[i].x);
		miny = std::min(miny, triangle[i].y);
		maxy = std::max(maxy, triangle[i].y);
	}

	m_radius = distanceBetweenPoints({ minx, miny }, { maxx, maxy });
	m_graphicsComponent.m_color = sf::Color::Cyan;
}

//
//PlayerShip::PlayerShip(sf::Vector2f origin)
//{
//	m_position = origin;
//	m_orientation = {0.f, -1.f};
//
//	std::vector<sf::Vector2f> triangle;
//	triangle.push_back({ m_position.x, m_position.y - 25.f });
//	triangle.push_back({ m_position.x - 15.f, m_position.y + 15.f });
//	triangle.push_back({ m_position.x + 15.f, m_position.y + 15.f });
//	m_graphicsComponent.m_polygons.push_back(triangle);
//}


void PlayerShip::update(float dt)
{
	laserCooldownAccumulator = std::fmax(0.f, laserCooldownAccumulator - dt);

	sf::Vector2f movementVector{ 0.f, 0.f };

	// controls

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_acceleration = m_orientation * m_maxVelocity;
	}
	else
	{
		m_acceleration = { 0.f, 0.f };
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_acceleration = -m_velocity;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rotate(- dt * m_maxRotationSpeed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rotate(dt * m_maxRotationSpeed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (laserCooldownAccumulator == 0.f)
		{
			MessageQueue::Message m;
			m.type = MessageQueue::MessageType::SHOTS_FIRED;
			m.payload.position = m_position;
			m.payload.direction = m_orientation;
			MessageQueue::getInstance()->pushMessage(m);
			laserCooldownAccumulator = laserCooldown;
		}
	}

	// meat potatoes

	if (m_position.x < GlobalConfig::BOUNDARY_MIN_X)
	{
		m_position.x = GlobalConfig::BOUNDARY_MAX_X;
	}
	if (m_position.x > GlobalConfig::BOUNDARY_MAX_X)
	{
		m_position.x = GlobalConfig::BOUNDARY_MIN_X;
	}
	if (m_position.y < GlobalConfig::BOUNDARY_MIN_Y)
	{
		m_position.y = GlobalConfig::BOUNDARY_MAX_Y;
	}
	if (m_position.y > GlobalConfig::BOUNDARY_MAX_Y)
	{
		m_position.y = GlobalConfig::BOUNDARY_MIN_Y;
	}

	GameObject::update(dt);
}

void PlayerShip::fire()
{
	;
}