#include "ColliderComponent.h"

#include "GameObject.h"

ColliderComponent::ColliderComponent(GameObject* parent) :
	m_parent{ parent }
{
	;
}

void ColliderComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < m_vertices.size(); i++)
	{
		target.draw(m_vertices[i]);
	}
}

void ColliderComponent::update(float dt)
{
	m_color = sf::Color::Green;
	for (int i = 0; i < m_polygons.size(); i++)
	{
		for (int j = 0; j < m_polygons[i].size(); j++)
		{
			m_polygons[i][j] += (m_parent->m_position - m_position);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		{
			std::cout << "breakpoint!";
		}
	}
	m_position = m_parent->m_position;
}

void ColliderComponent::render()
{
	m_vertices.clear();
	for (int i = 0; i < m_polygons.size(); i++)
	{
		sf::VertexArray va;
		va.setPrimitiveType(sf::PrimitiveType::LineStrip);
		for (int j = 0; j < m_polygons[i].size(); j++)
		{
			va.append(sf::Vertex(m_polygons[i][j], m_color));
		}
		va.append(sf::Vertex(m_polygons[i][0], m_color));

		m_vertices.push_back(va);
	}
}

void ColliderComponent::rotate(float angle)
{
	for (int i = 0; i < m_polygons.size(); i++)
	{
		for (int j = 0; j < m_polygons[i].size(); j++)
		{
			m_polygons[i][j] = m_position + rotateVectorByAngle(m_polygons[i][j] - m_position, angle);
		}
	}
}