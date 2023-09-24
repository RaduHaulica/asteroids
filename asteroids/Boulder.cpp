#include "Boulder.h"

Boulder::Boulder(sf::Vector2f origin):
	GameObject(origin)
{
	m_type = GlobalConfig::OBJECTS::BOULDER;
	//std::vector<sf::Vector2f> square;
	//square.push_back(m_position + sf::Vector2f( -25.f, -25.f ));
	//square.push_back(m_position + sf::Vector2f( 25.f, -25.f ));
	//square.push_back(m_position + sf::Vector2f( 25.f, 25.f ));
	//square.push_back(m_position + sf::Vector2f( -25.f, 25.f ));
	//m_graphicsComponent.m_polygons.push_back(square);

	//for (int i = 0; i < m_graphicsComponent.m_polygons.size(); i++)
	//{
	//	sf::VertexArray boulderVA;
	//	boulderVA.setPrimitiveType(sf::PrimitiveType::LineStrip);
	//	for (int j = 0; j < m_graphicsComponent.m_polygons[i].size(); j++)
	//	{
	//		boulderVA.append(sf::Vertex(m_graphicsComponent.m_polygons[i][j], sf::Color::White));

	//	}
	//	m_graphicsComponent.m_vertices.push_back(boulderVA);
	//}
}

void Boulder::update(float dt)
{
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

	m_graphicsComponent.rotate(m_rotationSpeed * dt);
	m_colliderComponent.rotate(m_rotationSpeed * dt);

	GameObject::update(dt);
}

void Boulder::collide()
{
	GameObject::collide();
}