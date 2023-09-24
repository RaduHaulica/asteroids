#include "GraphicsComponent.h"

#include "GameObject.h"

GraphicsComponent::GraphicsComponent(GameObject* parent):
	m_parent{ parent }
{
	;
}

void GraphicsComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
	for (int i = 0; i < m_vertices.size(); i++)
	{
		target.draw(m_vertices[i]);
	}
}

void GraphicsComponent::update(float dt)
{
	m_vertices.clear();
	for (int i = 0; i < m_polygons.size(); i++)
	{
		sf::VertexArray va;
		va.setPrimitiveType(sf::PrimitiveType::LineStrip);
		for (int j = 0; j < m_polygons[i].size(); j++)
		{
			m_polygons[i][j] += (m_parent->m_position - m_position);
			va.append(sf::Vertex(m_polygons[i][j], m_color));
		}
		va.append(sf::Vertex(m_polygons[i][0], m_color));
		m_vertices.push_back(va);
	}
	m_position = m_parent->m_position;
}

void GraphicsComponent::rotate(float angle)
{
	for (int i = 0; i < m_polygons.size(); i++)
	{
		for (int j = 0; j < m_polygons[i].size(); j++)
		{
			m_polygons[i][j] = m_position + rotateVectorByAngle(m_polygons[i][j] - m_position, angle);
		}
	}
}